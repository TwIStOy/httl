// Copyright (c) 2020 - present, Hawtian Wang (twistoy.wang@gmail.com)
//

#pragma once  // NOLINT(build/header_guard)

#include "ht/coroutine/traits/awaiter_type.hpp"

namespace ht::coro::__details {

template<typename T>
auto __get_awaiter_impl(T &&value, int) noexcept(
    noexcept(static_cast<T &&>(value).operator co_await())) {
  return static_cast<T &&>(value).operator co_await();
}

template<typename T>
auto __get_awaiter_impl(T &&value, long) noexcept(
    noexcept(operator co_await(static_cast<T &&>(value)))) {
  return operator co_await(static_cast<T &&>(value));
}

template<awaiter_type T>
T &&__get_awaiter_impl(T &&value, long long) noexcept {
  return static_cast<T &&>(value);
}

template<typename T>
auto get_awaiter(T &&value) noexcept(
    noexcept(__get_awaiter_impl(static_cast<T &&>(value), 0))) {
  return __get_awaiter_impl(static_cast<T &&>(value), 0);
}

}  // namespace ht::coro::__details
