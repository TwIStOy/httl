// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#include <concepts>
#include <coroutine>
#include <utility>

namespace ht::coro {

namespace __impl {

template<typename Awaiter>
concept has_member_operator_co_await = requires(Awaiter awaiter) {
                                         { awaiter.operator co_await() };
                                       };

template<typename Awaiter>
concept has_free_operator_co_await = requires(Awaiter awaiter) {
                                       { operator co_await(awaiter) };
                                     };

template<typename Awaiter>
  requires requires(Awaiter awaiter) {
             { awaiter.await_ready() } -> std::convertible_to<bool>;
             { awaiter.await_resume() };
           }
struct await_result_impl {
  using type = decltype(std::declval<Awaiter &>().await_resume());
};

template<typename Awaitable>
inline constexpr decltype(auto) get_awaiter(Awaitable &&awaitable) noexcept {
  if constexpr (has_member_operator_co_await<Awaitable>) {
    return std::forward<Awaitable>(awaitable).operator co_await();
  } else if constexpr (has_free_operator_co_await<Awaitable>) {
    return operator co_await(std::forward<Awaitable>(awaitable));
  } else {
    return std::forward<Awaitable>(awaitable);
  }
}

}  // namespace __impl

template<typename T>
  requires requires(T v) {
             { __impl::get_awaiter(v) };
           }
struct awaitable_traits {
  using awaiter_t      = decltype(__impl::get_awaiter(std::declval<T>()));
  using await_result_t = typename __impl::await_result_impl<awaiter_t>::type;
};

}  // namespace ht::coro
