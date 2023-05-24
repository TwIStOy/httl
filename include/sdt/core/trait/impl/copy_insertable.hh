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

// Specifies that an instance of the type can be copy-constructed in-place by a
// given allocator.
template<typename T, typename X>
concept CopyInsertable = requires(std::allocator<T>& m, T *p, const T v) {
  std::allocator_traits<std::allocator<T>>::construct(m, p, v);
};

}  // namespace sdt::core::trait
