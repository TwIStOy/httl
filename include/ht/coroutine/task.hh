// Copyright (c) 2020 - present, Hawtian Wang (twistoy.wang@gmail.com)
//

#pragma once  // NOLINT(build/header_guard)

#include <concepts>
#include <coroutine>
#include <exception>
#include <memory>
#include <optional>
#include <stdexcept>
#include <type_traits>
#include <utility>

namespace ht::coro {

template<typename T>
class task;

namespace __details {

struct __task_promise_base {  // {{{
  std::coroutine_handle<> coro_;

  struct final_awaiter {  // {{{
    [[nodiscard]] inline constexpr bool await_ready() const noexcept {
      return false;
    }

    template<std::derived_from<__task_promise_base> P>
    inline std::coroutine_handle<> await_suspend(
        std::coroutine_handle<P> coro) noexcept {
      return coro.promise().coro_;
    }

    inline constexpr void await_resume() noexcept {
    }
  };  // }}}

  __task_promise_base() = default;

  [[nodiscard]] inline constexpr auto initial_suspend() const noexcept {
    return std::suspend_always{};
  }

  [[nodiscard]] inline constexpr auto final_suspend() const noexcept {
    return final_awaiter{};
  }

  inline void set_coro(std::coroutine_handle<> coro) noexcept {
    coro_ = coro;
  }
};  // }}}

template<typename T>
class task_promise final : public __task_promise_base {  // {{{
 public:
  task_promise() noexcept = default;

  task<T> get_return_object() noexcept;

  void unhandled_exception() noexcept {
    exception_ = std::current_exception();
  }

  template<typename U>
    requires std::convertible_to<U &&, T>
  void return_value(U &&value) noexcept(
      std::is_nothrow_convertible_v<U &&, T>) {
    data_ = T(std::forward<U &&>(value));
  }

  T &result() & {
    if (exception_) {
      std::rethrow_exception(exception_);
    }
    return data_.value();
  }

  T &&result() && {
    if (exception_) {
      std::rethrow_exception(exception_);
    }

    return std::move(data_.value());
  }

 private:
  std::exception_ptr exception_;
  std::optional<T> data_;
};  // }}}

template<>
class task_promise<void> final : public __task_promise_base {  // {{{
 public:
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

 private:
  std::exception_ptr exception_;
};  // }}}

template<typename T>
class task_promise<T &> final : public __task_promise_base {  // {{{
 public:
  task_promise() noexcept = default;

  task<T &> get_return_object() noexcept;

  void unhandled_exception() noexcept {
    exception_ = std::current_exception();
  }

  inline void return_value(T &value) noexcept {
    value_ = std::addressof(value);
  }

  T &result() {
    if (exception_) {
      std::rethrow_exception(exception_);
    }
    return *value_;
  }

 private:
  T *value_{nullptr};
  std::exception_ptr exception_;
};  // }}}

}  // namespace __details

template<typename T = void>
class [[nodiscard]] task {
 public:
  using promise_type = __details::task_promise<T>;
  using value_type   = T;

 private:
  struct awaiter_base {  // {{{
    std::coroutine_handle<promise_type> coro;
    awaiter_base() = default;

    explicit awaiter_base(std::coroutine_handle<promise_type> coro)
        : coro(coro) {
    }

    [[nodiscard]] inline bool await_ready() const noexcept {
      return !coro || coro.done();
    }

    std::coroutine_handle<> await_suspend(std::coroutine_handle<> h) noexcept {
      coro.promise().set_coro(h);
      return coro;
    }
  };  // }}}

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

template<typename T>
task<T &> task_promise<T &>::get_return_object() noexcept {
  return task<T &>{std::coroutine_handle<task_promise>::from_promise(*this)};
}
}  // namespace __details

}  // namespace ht::coro

// vim: fdm=marker
