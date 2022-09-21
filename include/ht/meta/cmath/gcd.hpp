// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include <type_traits>

namespace ht::ce {

namespace __ce_gcd_impl {

template<typename T>
constexpr auto _gcd(const T a, const T b) noexcept {
  if (b == 0) {
    return a;
  }
  return _gcd(b, a % b);
}

}  // namespace __ce_gcd_impl

/**
 * Return greatest common divisor (GCD) in compile-time
 */
template<typename T, typename U>
  requires std::is_integral_v<T> && std::is_integral_v<U>
constexpr std::common_type_t<T, U> gcd(const T a, const U b) noexcept {
  using common_t = std::common_type_t<T, U>;
  return __ce_gcd_impl::_gcd(static_cast<common_t>(a),
                             static_cast<common_t>(b));
}

}  // namespace ht::ce

// vim: et sw=2 ts=2
