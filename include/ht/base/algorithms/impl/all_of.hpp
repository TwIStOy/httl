// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include <concepts>
#include <type_traits>

#include <range/v3/algorithm/all_of.hpp>

#include <ht/core/cpp_feature.h>

namespace ht {

inline bool all_of(ranges::range auto&& range, auto&& pred)
  requires std::predicate<std::remove_cvref_t<decltype(pred)>,
                          ranges::range_value_t<decltype(range)>>
{
  auto first = ranges::begin(range);
  auto last  = ranges::end(range);
  for (; first != last; ++first) {
    if (!pred(*first)) {
      return false;
    }
  }
  return true;
}

}  // namespace ht

// vim: et sw=2 ts=2
