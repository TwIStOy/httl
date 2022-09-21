// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include <concepts>
#include <tuple>
#include <type_traits>
#include <utility>

namespace ht {

template<typename T, typename... Args>
struct is_any_of : std::disjunction<std::is_same<T, Args>...> {};

template<typename T, typename... Args>
concept any_of = (std::same_as<T, Args> || ...);

}  // namespace ht

// vim: et sw=2 ts=2
