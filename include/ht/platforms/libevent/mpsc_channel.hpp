// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include <event.h>
#include <event2/event.h>

#include <algorithm>
#include <atomic>
#include <condition_variable>
#include <coroutine>
#include <list>
#include <mutex>
#include <optional>
#include <utility>

#include "ht/platforms/libevent/event_deleter.hpp"

namespace ht::platform::libevent {

using std::swap;

template<typename E>
class mpsc_channel {
 public:
  using value_type = E;
  using size_type  = int32_t;

  explicit mpsc_channel(::event_base *base, size_type max_size = -1)
      : base_(base), max_size_(max_size) {
    event_.reset(
        ::event_new(base_, -1, EV_READ, &mpsc_channel::event_callback, this));
  }

  ~mpsc_channel() = default;

  template<typename... Args>
  auto emplace(Args&&...args) {
    std::unique_lock lk(mutex_);
    while (max_size_ > 0 && values_.size() > max_size_) {
      cond_.wait(lk);
    }
    values_.emplace_back(std::forward<Args>(args)...);
    ::event_active(event_.get(), EV_READ, 0);
  }

  auto get_one() {
    struct awaiter {
      [[nodiscard]] bool await_ready() const noexcept {
        return !self_->values_.empty();
      }

      void await_suspend(std::coroutine_handle<> co) const noexcept {
        self_->coro_ = co;
      }

      auto await_resume() noexcept {
        std::unique_lock lk(self_->mutex_);
        auto v = std::move(self_->values_.front());
        self_->values_.pop_front();
        if (self_->max_size_ > 0) {
          self_->cond_.notify_one();
        }
        self_->count_--;
        return v;
      }

      mpsc_channel *self_;
    };

    return awaiter{this};
  }

  auto get_all() {
    struct awaiter {
      [[nodiscard]] bool await_ready() const noexcept {
        return !self_->values_.empty();
      }

      void await_suspend(std::coroutine_handle<> co) const noexcept {
        self_->coro_ = co;
      }

      auto await_resume() noexcept {
        std::unique_lock lk(self_->mutex_);
        std::list<E> empty;
        swap(empty, self_->values_);
        if (self_->max_size_ > 0) {
          self_->cond_.notify_one();
        }
        self_->count_ = 0;
        return empty;
      }

      mpsc_channel *self_;
    };

    return awaiter{this};
  }

 private:
  static void event_callback(int, short, void *data) {
    auto self = static_cast<mpsc_channel *>(data);
    self->coro_.resume();
  }

 private:
  ::event_base *base_;
  EventPtr event_;
  const size_type max_size_;
  size_type count_{0};

  std::mutex mutex_;
  std::condition_variable cond_;
  std::list<E> values_;

  std::coroutine_handle<> coro_;
};

}  // namespace ht::platform::libevent

// vim: et sw=2 ts=2
