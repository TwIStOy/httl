// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include <concepts>
#include <coroutine>
#include <exception>
#include <memory>
#include <optional>
#include <stdexcept>
#include <stop_token>
#include <type_traits>
#include <utility>

// ---

#include <ht/concurrency/get_stop_token.hpp>
#include <ht/core/box.hpp>
#include <ht/core/result.hpp>
#include <ht/coroutine/impl/coro_handle.hpp>
#include <ht/coroutine/impl/exchange_corotine_handle.hpp>

namespace ht::coro {

template<typename T>
class task;

namespace __details {

struct __task_promise_base {
  struct _final_awaiter_base {
    [[nodiscard]] static inline constexpr bool await_ready() noexcept {
      return false;
    }

    inline constexpr void await_resume() noexcept {
    }
  };

  __task_promise_base() = default;

  virtual ~__task_promise_base() = default;

  [[nodiscard]] static inline constexpr auto initial_suspend() noexcept {
    return std::suspend_always{};
  }

  [[nodiscard]] inline std::coroutine_handle<> unhandled_done() const {
    return handle_.done();
  }

  HT_ALWAYS_INLINE friend auto tag_invoke(tag_t<get_stop_token>,
                                          const __task_promise_base &p) {
    return p.stoken_;
  }

  HT_ALWAYS_INLINE friend auto tag_invoke(tag_t<exchange_coroutine_handle>,
                                          __task_promise_base &p,
                                          coro_handle<> rhs) {
    return std::exchange(p.handle_, static_cast<coro_handle<> &&>(rhs));
  }

  coro_handle<> handle_;
  std::stop_token stoken_;
};

template<typename T>
class task_promise final : public __task_promise_base {
 public:
  using result_type = T;

  task_promise() noexcept = default;

  ~task_promise() override = default;

  task<T> get_return_object() noexcept;

  void unhandled_exception() noexcept {
    expected_.set_error(std::current_exception());
  }

  template<typename U>
    requires std::convertible_to<U &&, T>
  void return_value(U &&value) noexcept(
      std::is_nothrow_convertible_v<U &&, T>) {
    expected_.set_value(std::forward<U>(value));
  }

  T &result() & {
    if (expected_.is_err()) {
      std::rethrow_exception(expected_.unwrap_err());
    }
    return expected_.unwrap();
  }

  T &&result() && {
    if (expected_.is_err()) {
      std::rethrow_exception(expected_.unwrap_err());
    }
    return std::move(expected_).unwrap();
  }

  auto final_suspend() noexcept {
    struct awaiter : _final_awaiter_base {
      auto await_suspend(std::coroutine_handle<task_promise> p) noexcept {
        return p.promise().handle_.handle();
      }
    };
    return awaiter{};
  }

 private:
  ht::result<T, std::exception_ptr> expected_;
};

template<>
class task_promise<void> final : public __task_promise_base {
 public:
  using result_type = void;

  task_promise() noexcept = default;

  task<void> get_return_object() noexcept;

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

  static auto final_suspend() noexcept {
    struct awaiter : _final_awaiter_base {
      static auto await_suspend(
          std::coroutine_handle<task_promise> p) noexcept {
        return p.promise().handle_.handle();
      }
    };
    return awaiter{};
  }

 private:
  std::exception_ptr exception_;
};

}  // namespace __details

template<typename T = void>
class [[nodiscard]] task {
 public:
  using promise_type = __details::task_promise<T>;
  using value_type   = T;

 private:
  struct awaiter_base {
    std::coroutine_handle<promise_type> coro;
    awaiter_base() = default;

    explicit awaiter_base(std::coroutine_handle<promise_type> coro)
        : coro(coro) {
    }

    [[nodiscard]] inline bool await_ready() const noexcept {
      return !coro || coro.done();
    }

    std::coroutine_handle<> await_suspend(std::coroutine_handle<> h) noexcept {
      exchange_coroutine_handle(coro.promise(), h);
      return coro;
    }
  };

 public:
  task() noexcept = default;

  explicit task(std::coroutine_handle<promise_type> coro) : coro_(coro) {
  }

  ~task() {
    if (coro_) {
      coro_.destroy();
    }
  }

  task(const task &) = delete;
  task(task &&t) noexcept : coro_(t.coro_) {
    t.coro_ = nullptr;
  }

  task &operator=(const task &) = delete;
  task &operator=(task &&t) noexcept {
    if (std::addressof(t) != this) {
      if (coro_) {
        coro_.destroy();
      }

      coro_   = t.coro_;
      t.coro_ = nullptr;
    }

    return *this;
  }

  [[nodiscard]] inline bool await_ready() const noexcept {
    return !coro_ || coro_.done();
  }

  auto operator co_await() &noexcept {
    struct awaiter : awaiter_base {
      using awaiter_base::awaiter_base;

      decltype(auto) await_resume() {
        if (!this->coro) {
          throw std::runtime_error{"broken promise"};
        }
        return this->coro.promise().result();
      }
    };
    return awaiter{coro_};
  }

  auto operator co_await() &&noexcept {
    struct awaiter : awaiter_base {
      using awaiter_base::awaiter_base;

      decltype(auto) await_resume() {
        if (!this->coro) {
          throw std::runtime_error{"broken promise"};
        }
        return std::move(this->coro.promise()).result();
      }
    };
    return awaiter{coro_};
  }

 private:
  std::coroutine_handle<promise_type> coro_;
};

namespace __details {

template<typename T>
task<T> task_promise<T>::get_return_object() noexcept {
  return task<T>{std::coroutine_handle<task_promise>::from_promise(*this)};
}

inline task<> task_promise<void>::get_return_object() noexcept {
  return task<>{std::coroutine_handle<task_promise>::from_promise(*this)};
}

}  // namespace __details

}  // namespace ht::coro

// vim: fdm=marker
