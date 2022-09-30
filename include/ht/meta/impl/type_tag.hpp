// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

namespace ht {

// Utility template struct for represent a specify type in parameters for
// overloading to avoid any object overhead
template<typename T>
struct type_tag {
  using type = T;
};

}  // namespace ht

// vim: et sw=2 ts=2
