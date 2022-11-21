// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include <concepts>
#include <type_traits>

namespace ht {

namespace _same_types_impl {

template<typename T, typename... Args>
inline constexpr bool same_types_impl = (std::is_same_v<T, Args> && ...);

template<typename T>
inline constexpr bool same_types_impl<T> = true;

}  // namespace _same_types_impl

template<typename... Args>
inline constexpr bool same_types = _same_types_impl::same_types_impl<Args...>;

template<>
inline constexpr bool same_types<> = true;

}  // namespace ht

// vim: et sw=2 ts=2
