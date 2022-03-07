// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include <coroutine>
#include <exception>
#include <stdexcept>
#include <variant>

#include "ht/core/cpp_feature.h"
#include "ht/coroutine/type_traits.hpp"

namespace ht {

struct task_promise_base {
  struct final_awaiter {
    [[nodiscard]] static constexpr bool await_ready() noexcept {
      return false;
    }

    template<typename P>
    std::coroutine_handle<> await_suspend(
        std::coroutine_handle<P> coro) noexcept {
      return coro.promise().coro_;
    }

    void await_resume() noexcept {
    }
  };

  task_promise_base() = default;

  [[nodiscard]] static auto initial_suspend() noexcept {
    return std::suspend_always{};
  }

  [[nodiscard]] static auto final_suspend() noexcept {
    return final_awaiter{};
  }

  std::coroutine_handle<> coro_;
};

template<typename R>
class task;

template<typename T>
struct task_promise final : task_promise_base {
 public:
  task_promise() noexcept = default;

  task<T> get_return_object() noexcept;

  void unhandled_exception() noexcept {
    data_ = std::current_exception();
  }

  template<typename U>
    requires std::convertible_to<U &&, T>
  void return_value(U &&value) noexcept(std::is_nothrow_constructible_v<T, U>) {
    data_ = T(std::forward<U>(value));
  }

  T &result() & {
    if (data_.index() == 2) {
      std::rethrow_exception(std::get<2>(data_));
    }
    assert(data_.index() == 1);
    return std::get<1>(data_);
  }

  T &&result() && {
    if (data_.index() == 2) {
      std::rethrow_exception(std::get<2>(data_));
    }
    assert(data_.index() == 1);
    return std::get<1>(std::move(data_));
  }

 private:
  struct Dummy {};
  std::variant<Dummy, T, std::exception_ptr> data_;
};

template<>
class task_promise<void> final : public task_promise_base {
 public:
  task_promise() noexcept = default;

  task<void> get_return_object() noexcept;

  void return_void() noexcept {
  }

  void unhandled_exception() noexcept {
    exception_ = std::current_exception();
  }

  void result() {
    if (exception_) {
      std::rethrow_exception(exception_);
    }
  }

 private:
  std::exception_ptr exception_;
  std::coroutine_handle<> previous_;
};

template<typename T>
class task_promise<T &> final : public task_promise_base {
 public:
  task_promise() noexcept = default;

  task<T &> get_return_object() noexcept;

  void return_value(T &value) noexcept {
    value_ = std::addressof(value);
  }

  void unhandled_exception() noexcept {
    exception_ = std::current_exception();
  }

  T &result() {
    if (exception_) {
      std::rethrow_exception(exception_);
    }

    return *value_;
  }

 private:
  std::exception_ptr exception_;
  std::coroutine_handle<> previous_;
  T *value_ = nullptr;
};

template<typename T = void>
class [[nodiscard]] task {
 public:
  using promise_type = task_promise<T>;

  using value_type = T;

 private:
  struct awaitable_base {
    std::coroutine_handle<promise_type> coro_;

    awaitable_base() = default;

    explicit awaitable_base(std::coroutine_handle<promise_type> coro)
        : coro_(coro) {
    }

    [[nodiscard]] bool await_ready() const noexcept {
      return !coro_ || coro_.done();
    }

    std::coroutine_handle<> await_suspend(std::coroutine_handle<> h) noexcept {
      coro_.promise().coro_ = h;
      return coro_;
    }
  };

 public:
  task() noexcept = default;

  explicit task(std::coroutine_handle<promise_type> coroutine)
      : coro_(coroutine) {
  }

  task(task &&t) noexcept : coro_(t.coro_) {
    t.coro_ = nullptr;
  }

  task(const task &)            = delete;
  task &operator=(const task &) = delete;

  ~task() {
    if (coro_) {
      coro_.destroy();
    }
  }

  task &operator=(task &&other) noexcept {
    if (std::addressof(other) != this) {
      if (coro_) {
        coro_.destroy();
      }

      coro_       = other.coro_;
      other.coro_ = nullptr;
    }

    return *this;
  }

  [[nodiscard]] bool await_ready() const noexcept {
    return !coro_ || coro_.done();
  }

  auto operator co_await() &noexcept {
    struct awaitable : awaitable_base {
      using awaitable_base::awaitable_base;

      decltype(auto) await_resume() {
        if (!this->coro_) {
          throw std::runtime_error{"broken promise"};
        }
        return this->coro_.promise().result();
      }
    };

    return awaitable{coro_};
  }

  auto operator co_await() &&noexcept {
    struct awaitable : awaitable_base {
      using awaitable_base::awaitable_base;

      decltype(auto) await_resume() {
        if (!this->coro_) {
          throw std::runtime_error{"broken promise"};
        }

        return std::move(this->coro_.promise()).result();
      }
    };

    return awaitable{coro_};
  }

 private:
  std::coroutine_handle<promise_type> coro_{nullptr};
};

template<typename T>
task<T> task_promise<T>::get_return_object() noexcept {
  return task<T>{std::coroutine_handle<task_promise>::from_promise(*this)};
}

inline task<void> task_promise<void>::get_return_object() noexcept {
  return task<void>{std::coroutine_handle<task_promise>::from_promise(*this)};
}

template<typename T>
task<T &> task_promise<T &>::get_return_object() noexcept {
  return task<T &>{std::coroutine_handle<task_promise>::from_promise(*this)};
}

}  // namespace ht

// vim: et sw=2 ts=2
