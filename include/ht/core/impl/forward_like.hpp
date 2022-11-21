// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include <type_traits>
#include <utility>

namespace ht {

#if __cpp_lib_forward_like
using std::forward_like;
#else
template<class T, class U>
[[nodiscard]] constexpr auto&& forward_like(U&& x) noexcept {
  constexpr bool is_adding_const = std::is_const_v<std::remove_reference_t<T> >;

  if constexpr (std::is_lvalue_reference_v<T&&>) {
    if constexpr (is_adding_const) {
      return std::as_const(x);
    } else {
      return static_cast<U&>(x);
    }
  } else {
    if constexpr (is_adding_const) {
      return std::move(std::as_const(x));
    } else {
      return std::move(x);  // NOLINT(bugprone-move-forwarding-reference)
    }
  }
}
#endif

template<typename T, typename U>
using forward_like_t = decltype(forward_like<T>(std::declval<U>()));

}  // namespace ht

// vim: et sw=2 ts=2
