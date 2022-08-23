// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include "ht/core/tag_invoke.hpp"

namespace ht {

inline constexpr struct {
  template<typename T>
  auto operator()(T &&value) const
      noexcept(nothrow_tag_invocable<decltype(*this), T>) {
    return ht::tag_invoke(*this, std::forward<T>(value));
  }
} stringify{};

inline constexpr struct {
  template<typename T>
  auto operator()(T &&value) const
      noexcept(nothrow_tag_invocable<decltype(*this), T>) {
    return ht::tag_invoke(*this, std::forward<T>(value));
  }
} debug_stringify{};

}  // namespace ht

// vim: et sw=2 ts=2
