// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

namespace ht::ce {

/**
 * Return absolute value in compile-time
 */
template<typename T>
constexpr T abs(const T v) noexcept {
  if (v == T(0)) {
    return T(0);
  } else if (v < T(0)) {
    return -v;
  } else {
    return v;
  }
}

}  // namespace ht::ce

// vim: et sw=2 ts=2
