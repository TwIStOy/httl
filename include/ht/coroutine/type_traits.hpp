// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include <concepts>
#include <coroutine>
#include <type_traits>

namespace ht {

template<typename T>
struct is_coroutine_handle : std::false_type {};

template<typename P>
struct is_coroutine_handle<std::coroutine_handle<P>> : std::true_type {};

template<typename T>
constexpr bool is_coroutine_handle_v = is_coroutine_handle<T>::value;

template<typename T>
concept std_coroutine_handle = is_coroutine_handle_v<T>;

namespace __details {
template<typename T>
constexpr bool is_valid_await_suspend_return_value_type_v =
    std::is_void_v<T> || std::is_same_v<bool, T> || is_coroutine_handle_v<T>;

template<typename T>
concept is_valid_await_suspend_return_value_type =
    is_valid_await_suspend_return_value_type_v<T>;
}  // namespace __details

// clang-format off
template<typename T>
concept is_awaiter = requires(T v) {
  { v.await_ready() } -> std::convertible_to<bool>;
  { v.await_resume() } -> std::same_as<void>;
  { v.await_suspend() } -> __details::is_valid_await_suspend_return_value_type;
};
// clang-format on

// clang-format off
template<typename T>
concept awaitable = requires(T v) {
  { v.operator co_await() };
} || requires(T v) {
  { operator co_await(v) };
};
// clang-format on

namespace __details {

template<typename T>
auto get_awaiter_impl(T &&value, int) noexcept(
    noexcept(static_cast<T &&>(value).operator co_await())) {
  return static_cast<T &&>(value).operator co_await();
}

template<typename T>
auto get_awaiter_impl(T &&value, long) noexcept(
    noexcept(operator co_await(static_cast<T &&>(value)))) {
  return operator co_await(static_cast<T &&>(value));
}

struct _any {
  template<typename T>
  _any(T &&) {
  }
};

template<typename T>
  requires is_awaiter<T &&>
T &&get_awaiter_impl(T &&value, _any) noexcept {
  return static_cast<T &&>(value);
}

template<typename T>
auto get_awaiter(T &&value) noexcept(
    noexcept(get_awaiter_impl(static_cast<T &&>(value), 0))) {
  return get_awaiter_impl(static_cast<T &&>(value), 0);
}
}  // namespace __details

template<typename T>
using awaiter_t = decltype(__details::get_awaiter(std::declval<T>()));

template<typename T>
using awaiter_result_t = decltype(std::declval<awaiter_t<T>>().await_resume());

}  // namespace ht

// vim: et sw=2 ts=2
