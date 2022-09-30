// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include <event.h>

#include <coroutine>
#include <functional>
#include <list>
#include <memory>
#include <span>

#include "ht/network/socket.hpp"
#include "ht/platforms/libevent/alarm.hpp"
#include "ht/platforms/libevent/event_deleter.hpp"

namespace ht::platform::libevent {

class buffered_writer {
 private:
  struct __write_awaiter;

 public:
  static constexpr std::size_t kDefaultMaxBufferSize = 8 * 1024;
  static constexpr std::size_t kSlicePerCommit       = 128;

  inline buffered_writer(void *io_context, int fd,
                         std::size_t max_buffer_size = kDefaultMaxBufferSize)
      : base_(static_cast<::event_base *>(io_context)),
        fd_(fd),
        alarm_(base_,
               [this] {
                 send_internal();
               }),
        max_buffer_size_(max_buffer_size) {
  }

  HT_ALWAYS_INLINE __write_awaiter write(std::span<char> buffer) {
    return __write_awaiter{this, buffer};
  }

  /* async */
  void flush();

 private:
  HT_ALWAYS_INLINE void setup_event() {
    if (event_ == nullptr) {
      event_.reset(::event_new(base_, fd_, EV_WRITE | EV_PERSIST,
                               &buffered_writer::event_callback, this));
    }
  }

  static void event_callback(int fd, short events, void *context) {
    (void)fd;
    static_cast<buffered_writer *>(context)->handle_events(events);
  }

  void handle_events(short events) {
    event_.reset();
  }

  HT_ALWAYS_INLINE void send_internal() {
    alarm_.cancel();

    while (current_buffer_size_ > 0) {
      std::size_t flushed_bytes = 0;
      if (!flush_internal(&flushed_bytes)) {
        if (!write_error_) {
          setup_event();
        }

        // shrink buffer

        break;
      }
    }

    /*
     * flush_alarm_->Cancel();
     *
     * while (buffers_to_send_.UsedSize()) {
     *   int sent_bytes = 0;
     *   if (!FlushBufferInternal(&sent_bytes)) {
     *     if (!underlying_writer_error_) {
     *       EnableFdWriteEvent();
     *     }
     *     break;
     *   }
     *   LLOG(Debug, "Send {} bytes", sent_bytes);
     *
     *   OnBytesSent(static_cast<uint32_t>(sent_bytes));
     * }
     *
     * if (underlying_writer_error_) {
     *   buffers_to_send_.Clear();
     *
     *   DisableFdWriteEvent();
     *
     *   LLOG(Info,
     *        "Error occured when flushing buffers in AsyncTcpConnection: {},
     * this " "connection is unrecoverable",
     *        std::get<0>(remote_addr_).ToDebugString());
     * }
     *
     * if (buffers_to_send_.Empty()) {
     *   if (closed_) {
     *     CloseFD();
     *   } else if (writer_shut_down_) {
     *     shutdown(fd_, SHUT_WR);
     *
     *     DisableFdWriteEvent();
     *   }
     * }
     *
     * LLOG(Debug,
     *      "writable_: {}, BufferBelowLowWatermark(): {}, "
     *      "underlying_writer_error_: {}, destroyed_: {}, writer_shut_down_:
     * {}, " "closed_: {}", writable_, BufferBelowLowWatermark(),
     * underlying_writer_error_, destroyed_, writer_shut_down_, closed_); if
     * (!writable_ && (BufferBelowLowWatermark() || underlying_writer_error_)) {
     *   writable_ = true;
     *   if (writer_callback_ && !destroyed_ && !writer_shut_down_ && !closed_
     * && do_callback) { LLOG(Debug, "Call OnWritable"); emitting_ = true;
     *     writer_callback_->OnWritable(this);
     *     emitting_ = false;
     *   }
     * }
     *
     * if (destroyed_) {
     *   TryToDestroy();
     *   return;
     * }
     *
     * return;
     */
  }

  HT_ALWAYS_INLINE bool flush_internal(std::size_t *flushed_bytes) {
    uint32_t index = 0;
    iovec iovecs_to_send[kSlicePerCommit];
    msghdr headers_to_send     = {};
    headers_to_send.msg_iov    = iovecs_to_send;
    headers_to_send.msg_iovlen = 0;

    for (auto block = buffers_to_send_.begin();
         block != buffers_to_send_.end() && index < kSlicePerCommit;
         block++, index++) {
      iovec &io = iovecs_to_send[index];

      io.iov_base = const_cast<void *>(static_cast<void *>(block->data()));
      io.iov_len  = block->size();

      ++headers_to_send.msg_iovlen;
    }
    if ((*flushed_bytes = sendmsg(fd_, &headers_to_send, 0)) == -1) {
      write_error_ = false;
      int error    = errno;
      if (error != EAGAIN && error != EWOULDBLOCK) {
        write_error_ = true;
      }
      return false;
    }
    return true;
  }

  HT_ALWAYS_INLINE void notify_one() {
    if (!pending_op_.empty()) {
      auto co = pending_op_.front();
      pending_op_.pop_front();

      co.resume();
    }
  }

  HT_ALWAYS_INLINE void notify_all() {
    while (!pending_op_.empty()) {
      auto co = pending_op_.front();
      pending_op_.pop_front();

      co.resume();
    }
  }

 private:
  ::event_base *base_;
  int fd_;

  std::unique_ptr<::event, EventDeleter> event_;
  alarm<std::function<void()>> alarm_;

  bool write_error_{false};
  std::size_t max_buffer_size_;
  std::size_t current_buffer_size_{0};
  std::list<std::span<char>> buffers_to_send_;
  std::list<std::coroutine_handle<>> pending_op_;

 private:
  struct __write_awaiter {
    buffered_writer *writer;
    std::span<char> pending;

    [[nodiscard]] HT_ALWAYS_INLINE bool await_ready() const noexcept {
      return writer->current_buffer_size_ < writer->max_buffer_size_;
    }

    HT_ALWAYS_INLINE void await_suspend(
        std::coroutine_handle<> co) const noexcept {
      writer->pending_op_.push_back(co);
    }

    [[nodiscard]] HT_ALWAYS_INLINE bool await_resume() const {
      if (writer->write_error_) {
        return false;
      }
      writer->buffers_to_send_.push_back(pending);
      writer->current_buffer_size_ += pending.size();
      return true;
    }
  };
};

}  // namespace ht::platform::libevent

// vim: et sw=2 ts=2
