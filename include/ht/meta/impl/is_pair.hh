// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include <tuple>
#include <type_traits>
#include <utility>

namespace ht {

template<typename T, typename = void>
struct is_pair : std::false_type {};

template<typename T>
struct is_pair<T, std::void_t<typename T::first_type, typename T::second_type>>
    : std::true_type {};

template<typename T>
static constexpr auto is_pair_v = is_pair<T>::value;

}  // namespace ht

// vim: et sw=2 ts=2
