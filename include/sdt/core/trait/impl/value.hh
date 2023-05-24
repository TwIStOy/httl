// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include <type_traits>

namespace sdt::core::trait {

template<typename T>
struct Referenceable_t : std::true_type {};

template<>
struct Referenceable_t<void> : std::false_type {};

template<typename T>
concept Referenceable = Referenceable_t<T>::value;

}  // namespace sdt::core::trait
