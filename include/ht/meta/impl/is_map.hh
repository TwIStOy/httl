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
struct is_map : std::false_type {};

template<typename T>
struct is_map<T, std::void_t<typename T::key_type, typename T::mapped_type>>
    : std::true_type {};

template<typename T>
static constexpr bool is_map_v = is_map<T>::value;

}  // namespace ht

// vim: et sw=2 ts=2
