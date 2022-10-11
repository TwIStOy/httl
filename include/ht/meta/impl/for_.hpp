// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include <cstddef>
#include <cstdint>
#include <type_traits>
#include <utility>

namespace ht {

template<typename F, std::size_t... Is>
inline void for_in(std::index_sequence<Is...>, F&& func) {
  (std::forward<F>(func)(std::integral_constant<std::size_t, Is>{}), ...);
}

template<std::size_t N, typename Func>
inline void for_(Func&& func) {
  for_in(std::make_index_sequence<N>{}, std::forward<Func>(func));
}

}  // namespace ht

// vim: et sw=2 ts=2
