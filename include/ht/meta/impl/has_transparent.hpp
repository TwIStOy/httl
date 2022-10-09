// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include <type_traits>

namespace ht {

template<typename T, typename = void>
struct has_transparent : std::false_type {};

template<typename T>
struct has_transparent<T, std::void_t<typename T::is_transparent>>
    : std::true_type {};

template<typename T>
static constexpr bool has_transparent_v = has_transparent<T>::value;

}  // namespace ht

// vim: et sw=2 ts=2
