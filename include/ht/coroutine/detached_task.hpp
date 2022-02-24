// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include <atomic>
#include <coroutine>
#include <exception>
#include <memory>

#include "ht/core/cpp_feature.h"

namespace ht {

class detached_task_promise;

class detached_task_handle {
 public:
  inline explicit detached_task_handle(
      std::coroutine_handle<> coroutine) noexcept
      : coroutine_(coroutine) {
  }

  inline bool finish() noexcept {
    if (finished_.exchange(true)) {
      return false;
    }
    coroutine_.destroy();
    return true;
  }

 private:
  std::atomic<bool> finished_{false};
  std::coroutine_handle<void> coroutine_;
};

class detached_task {
 public:
  using promise_type = detached_task_promise;

  HT_ALWAYS_INLINE explicit detached_task(
      std::shared_ptr<detached_task_handle> h)
      : h_(std::move(h)) {
  }

  HT_ALWAYS_INLINE bool cancel() noexcept {
    return h_->finish();
  }

 private:
  std::shared_ptr<detached_task_handle> h_;
};

class detached_task_promise {
 public:
  struct final_awaiter {
    HT_ALWAYS_INLINE explicit final_awaiter(
        std::shared_ptr<detached_task_handle> handle) noexcept
        : handle_(std::move(handle)) {
    }

    HT_ALWAYS_INLINE void await_resume() const noexcept {
    }

    HT_ALWAYS_INLINE bool await_ready() const noexcept {
      return false;
    }

    HT_ALWAYS_INLINE void await_suspend(std::coroutine_handle<>) noexcept {
      handle_->finish();
    }

    std::shared_ptr<detached_task_handle> handle_;
  };

  detached_task_promise()
      : handle_{std::make_shared<detached_task_handle>(
            std::coroutine_handle<detached_task_promise>::from_promise(
                *this))} {
  }

  HT_ALWAYS_INLINE detached_task get_return_object() {
    return detached_task{handle_};
  }

  HT_ALWAYS_INLINE auto initial_suspend() noexcept {
    return std::suspend_never{};
  }

  HT_ALWAYS_INLINE auto final_suspend() noexcept {
    return final_awaiter{handle_};
  }

  HT_ALWAYS_INLINE void return_void() const noexcept {
  }

  HT_ALWAYS_INLINE void unhandled_exception() const noexcept {
    std::terminate();
  }

 private:
  std::shared_ptr<detached_task_handle> handle_;
};

}  // namespace ht

// vim: et sw=2 ts=2
