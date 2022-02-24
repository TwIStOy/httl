// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include <atomic>
#include <condition_variable>
#include <coroutine>
#include <exception>
#include <memory>
#include <mutex>
#include <type_traits>
#include <utility>

#include "ht/coroutine/type_traits.hpp"

namespace ht {

template<typename T>
struct block_wait_task;

template<typename D>
struct block_wait_task_promise_base {
  using coroutine_handle_t = std::coroutine_handle<D>;

  block_wait_task_promise_base() = default;

  auto get_return_object() noexcept {
    return coroutine_handle_t::from_promise(*static_cast<D *>(this));
  }

  auto initial_suspend() const noexcept {
    return std::suspend_always();
  }

  void unhandled_exception() noexcept {
    exception_ = std::current_exception();
  }

  auto final_suspend() noexcept {
    struct awaiter {
      bool await_ready() const noexcept {
        return false;
      }

      void await_suspend(coroutine_handle_t co) const noexcept {
        auto &self = co.promise();
        {
          std::unique_lock<std::mutex> lk(self.mutex_);
          self.is_set_ = true;
          self.cv_.notify_all();
        }
      }

      void await_resume() noexcept {
      }
    };

    return awaiter{};
  }

  void return_void() noexcept {
  }

  void start() {
    get_return_object().resume();
  }

  void wait() {
    std::unique_lock<std::mutex> lk(mutex_);
    cv_.wait(lk, [this]() {
      return is_set_;
    });
  }

  std::exception_ptr exception_;
  bool is_set_{false};
  std::condition_variable cv_;
  std::mutex mutex_;
};

template<typename T>
struct block_wait_task_promise
    : public block_wait_task_promise_base<block_wait_task_promise<T>> {
  block_wait_task_promise() = default;

  T &&result() {
    if (this->exception_) {
      std::rethrow_exception(this->exception_);
    }
    return static_cast<T &&>(*result_);
  }

  auto yield_value(T &&r) noexcept {
    result_ = std::addressof(r);
    return this->final_suspend();
  }

  std::remove_reference_t<T> *result_{nullptr};
};

template<>
struct block_wait_task_promise<void>
    : public block_wait_task_promise_base<block_wait_task_promise<void>> {
  block_wait_task_promise() = default;

  void result() {
    if (exception_) {
      std::rethrow_exception(exception_);
    }
  }
};

template<typename T>
struct block_wait_task {
  using promise_type       = block_wait_task_promise<T>;
  using coroutine_handle_t = std::coroutine_handle<promise_type>;

  block_wait_task(coroutine_handle_t coro) noexcept : coro_(coro) {
  }

  block_wait_task(block_wait_task &&rhs) noexcept
      : coro_(std::exchange(rhs.coro_, coroutine_handle_t{})) {
  }

  block_wait_task(const block_wait_task &)            = delete;
  block_wait_task &operator=(const block_wait_task &) = delete;

  void start() {
    coro_.promise().start();
  }

  decltype(auto) result() {
    return coro_.promise().result();
  }

  void wait() {
    coro_.promise().wait();
  }

  coroutine_handle_t coro_;
};

// clang-format off
template<typename T, typename U>
concept not_same_as = !std::same_as<T, U>;
// clang-format on

template<typename T, typename R = awaiter_result_t<T>>
  requires not_same_as<R, void>
block_wait_task<R> make_block_wait_task(T &&t) {
  co_yield co_await std::forward<T>(t);
}

template<typename T, typename R = awaiter_result_t<T>>
  requires std::same_as<R, void>
block_wait_task<void> make_block_wait_task(T &&t) {
  co_await std::forward<T>(t);
}

template<typename T>
auto block_wait(T &&t) {
  auto task = make_block_wait_task(std::forward<T>(t));
  task.start();
  task.wait();
  return task.result();
}

}  // namespace ht
