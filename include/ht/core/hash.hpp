// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include <functional>
#include <string_view>

namespace ht {

struct string_hash {
  using hash_type      = std::hash<std::string_view>;
  using is_transparent = void;

  std::size_t operator()(const char *str) const {
    return hash_type{}(str);
  }

  std::size_t operator()(std::string_view str) const {
    return hash_type{}(str);
  }

  std::size_t operator()(const std::string& str) const {
    return hash_type{}(str);
  }
};

}  // namespace ht

// vim: et sw=2 ts=2
