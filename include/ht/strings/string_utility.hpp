// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include <cstring>
#include <functional>
#include <iterator>
#include <ranges>
#include <sstream>
#include <string>
#include <string_view>
#include <type_traits>

#include "ht/core/cpp_feature.h"
#include "ht/strings/stringify.hpp"

namespace ht {

inline std::string_view remove_leading_spaces(std::string_view str) {
  if (str.length() && std::isspace(str[0])) {
    uint32_t first_nonwhitespace_index = 0;
    for (char c : str) {
      if (!std::isspace(c)) {
        first_nonwhitespace_index = 1;
        break;
      }
    }
    return str.substr(first_nonwhitespace_index);
  }
  return str;
}

template<typename C>
std::string str_join(const C &container, std::string_view sep) {
  auto end = std::ranges::end(container);
  std::ostringstream oss;
  bool first = true;
  for (auto it = std::ranges::begin(container); it != end; ++it) {
    if (first) {
      first = false;
    } else {
      oss << sep;
    }
    oss << stringify(*it);
  }
  return oss.str();
}

template<typename C, typename F>
std::string str_join(const C &container, std::string_view sep, F &&f) {
  auto end = std::ranges::end(container);
  std::ostringstream oss;
  bool first = true;
  for (auto it = std::ranges::begin(container); it != end; ++it) {
    if (first) {
      first = false;
    } else {
      oss << sep;
    }
    oss << f(*it);
  }
  return oss.str();
}

}  // namespace ht

// vim: et sw=2 ts=2
