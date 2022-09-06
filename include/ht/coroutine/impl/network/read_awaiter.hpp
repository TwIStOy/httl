// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include <event.h>

#include <cassert>
#include <coroutine>
#include <memory>
#include <optional>
#include <span>
#include <utility>

#include "ht/core/platform/libevent_utils.hpp"
#include "ht/network/socket.hpp"

namespace ht {

namespace _network_socket_impl {

template<typename T, std::size_t E>
struct socket_read_awaiter {
  using span_t = std::span<T, E>;

  socket_read_awaiter(int fd, ::event_base *base, span_t data)
      : fd_(fd), base_(base), data_(data) {
  }

  [[nodiscard]] bool await_ready() const noexcept {
    return try_to_read();
  }

  void await_suspend(std::coroutine_handle<> handle) {
    handle_ = handle;

    // TODO(hawtian): olny impl libevent version now, impl for both libevent and
    // libuv later

    event_.reset(::event_new(base_, fd_, EV_READ,
                             &socket_read_awaiter::on_readable, this));
    if (event_.get() == nullptr) {
      throw std::runtime_error("can not allocate new event");
    }

    if (::event_add(event_.get(), nullptr) != 0) {
      throw std::runtime_error("can not add event into loop");
    }
  }

  std::pair<int32_t, int32_t> await_resume() {
    return {rc_, errno_};
  }

 private:
  bool try_to_read() {
    rc_ = ::read(fd_, data_.data(), data_.size_bytes());
    if (rc_ == 0) {
      // eof arrived
      return true;
    }
    if (rc_ == -1) {
      errno_ = errno;
      if (errno != EAGAIN) {
        return true;
      }
      return false;
    }
    return true;
  }

  // NOLINTNEXTLINE
  static void on_readable(int fd, short what, void *context) {
    (void)what;
    assert((what & EV_READ) > 0);

    auto self = reinterpret_cast<socket_read_awaiter *>(context);

    auto r = self->try_to_read();
    assert(r);
    self->handle_.resume();
  }

 private:
  std::coroutine_handle<> handle_;

  int fd_;
  ::event_base *base_;

  span_t data_;
  int32_t rc_{0};
  int32_t errno_{0};

  platform::libevent::EventPtr event_;
};

}  // namespace _network_socket_impl

template<typename T, std::size_t E>
auto async_read(const socket &skt, std::span<T, E> span) {
  return _network_socket_impl::socket_read_awaiter<T, E>{
      skt.fd(), skt.io_context(), span};
}

}  // namespace ht

// vim: et sw=2 ts=2
