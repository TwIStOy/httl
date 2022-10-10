// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include <array>
#include <string_view>

namespace ht {

/*
 * concatenate string_views at compile-time
 */
template<const std::string_view&...strs>
struct concat_sv {
  static constexpr auto impl() noexcept {
    constexpr auto len = (strs.size() + ... + 0);
    std::array<char, len + 1> arr;
    auto append = [i = 0, &arr](auto s) mutable {
      for (auto c : s) {
        arr[i++] = c;
      }
    };
    (append(strs), ...);
    arr[len] = 0;
    return arr;
  }
  static constexpr auto arr   = impl();
  static constexpr auto value = std::string_view{arr.data(), arr.size() - 1};
};

}  // namespace ht

// vim: et sw=2 ts=2
