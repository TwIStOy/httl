// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include <memory>
#include <type_traits>
#include <vector>

namespace sdt::core::trait {

/// Specifies that an object of the type can be destroyed by a given Allocator.
template<typename T, typename X>
concept Erasable = requires(std::allocator<T>& m, T *p) {
  std::allocator_traits<std::allocator<T>>::destroy(m, p);
};

}  // namespace sdt::core::trait
