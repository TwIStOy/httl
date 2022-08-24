// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include <coroutine>
#include <exception>

#include "ht/core/result.hpp"

namespace ht::coro::__impl {

template<typename T>
struct _task {
  struct [[nodiscard]] type;
};

struct task_promise_base {
  std::coroutine_handle<> handle_;

  task_promise_base() = default;

  struct final_awaiter {
    [[nodiscard]] static inline constexpr bool await_ready() noexcept {
      return false;
    }

    template<std::derived_from<task_promise_base> P>
    inline std::coroutine_handle<> await_suspend(
        std::coroutine_handle<P> handle) noexcept {
      return handle.promise().handle_;
    }

    inline constexpr void await_resume() noexcept {
    }
  };

  [[nodiscard]] static inline constexpr auto initial_suspend() noexcept {
    return std::suspend_always{};
  }

  [[nodiscard]] static inline constexpr auto final_suspend() noexcept {
    return final_awaiter{};
  }

  inline void set_handle(std::coroutine_handle<> handle) noexcept {
    handle_ = handle;
  }
};

template<typename T>
class task_promise final : public task_promise_base {
 public:
  task_promise() noexcept = default;

  typename _task<T>::type get_return_object() noexcept;

  void unhandled_exception() noexcept {
    result_.set_error(std::current_exception());
  }

  template<typename U>
    requires std::convertible_to<U &&, T>
  void return_value(U &&value) noexcept(
      std::is_nothrow_convertible_v<U &&, T>) {
    result_.set_value(std::forward<U &&>(value));
  }

  T &result() & {
    if (result_.is_err()) {
      std::rethrow_exception(result_.unwrap_err());
    }
    return result_.unwrap();
  }

  T &&result() && {
    if (result_.is_err()) {
      std::rethrow_exception(result_.unwrap_err());
    }
    return std::move(result_).unwrap();
  }

 private:
  ::ht::result<T, std::exception_ptr> result_;
};

template<>
class task_promise<void> final : public task_promise_base {
 public:
  task_promise() noexcept = default;

  typename _task<void>::type get_return_object() noexcept;

  void unhandled_exception() noexcept {
    exception_ = std::current_exception();
  }

  inline void return_void() {
  }

  void result() {
    if (exception_) {
      std::rethrow_exception(exception_);
    }
  }

 private:
  std::exception_ptr exception_;
};

}  // namespace ht::coro::__impl

// vim: et sw=2 ts=2
