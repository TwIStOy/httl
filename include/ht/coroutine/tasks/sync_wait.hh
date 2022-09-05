// Copyright (c) 2020 - present, Hawtian Wang (twistoy.wang@gmail.com)
//

#pragma once  // NOLINT(build/header_guard)

#include <cassert>
#include <coroutine>
#include <exception>
#include <type_traits>

#include "ht/coroutine/detail/manual_event.hh"
#include "ht/coroutine/traits/awaitable_traits.hpp"

namespace ht::coro {

namespace detail {

template<typename T>
struct sync_wait_promise {
  using handle_t = std::coroutine_handle<sync_wait_promise>;

  sync_wait_promise() = default;

  void start(::ht::coro::detail::manual_event *event) {
    event_ = event;
    handle_t::from_promise(*this).resume();
  }

  auto get_return_object() noexcept {
    return handle_t::from_promise(*this);
  }

  auto initial_suspend() noexcept {
    return std::suspend_always{};
  }

  auto final_suspend() noexcept {
    struct awaiter {
      [[nodiscard]] bool await_ready() const noexcept {
        return false;
      }

      void await_suspend(handle_t co) const noexcept {
        co.promise().event_->set();
      }

      void await_resume() noexcept {
      }
    };
    return awaiter{};
  }

  auto yield_value(T &&result) noexcept {
    result_ = std::addressof(result);
    return final_suspend();
  }

  void return_void() noexcept {
    assert(false);
  }

  void unhandled_exception() {
    exception_ = std::current_exception();
  }

  T &&result() {
    if (exception_) {
      std::rethrow_exception(exception_);
    }
    return static_cast<T &&>(*result_);
  }

  ::ht::coro::detail::manual_event *event_{};
  std::remove_reference_t<T> *result_;
  std::exception_ptr exception_;
};

template<>
struct sync_wait_promise<void> {
  using handle_t = std::coroutine_handle<sync_wait_promise>;

  sync_wait_promise() = default;

  void start(::ht::coro::detail::manual_event *event) {
    event_ = event;
    handle_t::from_promise(*this).resume();
  }

  auto get_return_object() noexcept {
    return handle_t::from_promise(*this);
  }

  static auto initial_suspend() noexcept {
    return std::suspend_always{};
  }

  static auto final_suspend() noexcept {
    struct awaiter {
      [[nodiscard]] static bool await_ready() noexcept {
        return false;
      }

      static void await_suspend(handle_t co) noexcept {
        co.promise().event_->set();
      }

      void await_resume() noexcept {
      }
    };
    return awaiter{};
  }

  void return_void() noexcept {
  }

  void unhandled_exception() {
    exception_ = std::current_exception();
  }

  void result() const {
    if (exception_) {
      std::rethrow_exception(exception_);
    }
  }

  ::ht::coro::detail::manual_event *event_{};
  std::exception_ptr exception_;
};

}  // namespace detail

template<typename T>
struct sync_wait_task {
  using promise_type = detail::sync_wait_promise<T>;
  using handle_t     = std::coroutine_handle<promise_type>;

  explicit sync_wait_task(handle_t coro) noexcept : coro_(coro) {
  }

  sync_wait_task(sync_wait_task &&rhs) noexcept
      : coro_(std::exchange(rhs.coro_, handle_t{})) {
  }

  ~sync_wait_task() {
    if (coro_) {
      coro_.destroy();
    }
  }

  sync_wait_task(const sync_wait_task &)            = delete;
  sync_wait_task &operator=(const sync_wait_task &) = delete;

  void start(::ht::coro::detail::manual_event *event) noexcept {
    coro_.promise().start(event);
  }

  decltype(auto) result() {
    return coro_.promise().result();
  }

  handle_t coro_;
};

template<typename T,
         typename R = typename awaitable_traits<T>::awaiter_result_t>
sync_wait_task<R> make_sync_wait_task(T &&a) {
  if constexpr (std::same_as<R, void>) {
    co_await std::forward<T>(a);
  } else {
    co_yield co_await std::forward<T>(a);
  }
}

}  // namespace ht::coro

// vim: fdm=marker
