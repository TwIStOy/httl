// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include <iostream>
#include <iterator>
#include <ranges>
#include <source_location>
#include <string_view>
#include <type_traits>
#include <utility>

namespace ht {

namespace __assert_impl {

[[gnu::cold]] inline auto runtime_assert_failed_cold(auto&& failed_fn)
    -> auto&& {
  return std::forward<decltype(failed_fn)>(failed_fn);
}

}  // namespace __assert_impl

inline void runtime_assert(bool condition, auto&& failed_fn) {
  if (!condition) [[unlikely]] {
    __assert_impl::runtime_assert_failed_cold(
        std::forward<decltype(failed_fn)>(failed_fn));
  }
}

// clang-format off
[[nodiscard]] auto assert_in_bound(
    auto&& obj, auto&& arg,
    std::source_location where = std::source_location::current()) -> auto&&
  requires ((std::is_integral_v<std::remove_cvref_t<decltype(arg)>>) &&
      requires { std::ssize(obj); obj[arg]; }) {
  runtime_assert(arg >= 0 && arg < std::ssize(obj), [where]() {
    std::cerr << where.file_name() << ":" << where.line() << "] "
              << where.function_name() << ": "
              << "out of bounds access detected";
  });
  return std::forward<decltype(obj)>(obj)[ std::forward<decltype(arg)>(arg) ];
}

[[nodiscard]] auto assert_in_bound(
    auto&& obj, auto&& arg,
    std::source_location where = std::source_location::current()) -> auto&&
  requires((!std::is_integral_v<std::remove_cvref_t<decltype(arg)>>) &&
      requires { std::ssize(obj); obj[arg]; }) {
  return std::forward<decltype(obj)>(obj)[ std::forward<decltype(arg)>(arg) ];
}
// clang-format on

}  // namespace ht

// vim: et sw=2 ts=2
