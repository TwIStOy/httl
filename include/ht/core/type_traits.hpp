// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include <tuple>
namespace ht {

template<typename T>
inline constexpr bool is_tuple_v = false;

template<typename... Args>
inline constexpr bool is_tuple_v<std::tuple<Args...>> = true;

}  // namespace ht

// vim: et sw=2 ts=2
