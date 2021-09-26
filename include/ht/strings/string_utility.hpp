// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include <cstring>
#include <string>
#include <string_view>

namespace ht {

inline std::string_view RemoveLeadingSpaces(std::string_view str) {
  if (str.length() && std::isspace(str[0])) {
    int first_nonwhitespace_index = 0;
    for (int i = 0; i < str.length(); i++) {
      if (!std::isspace(str[i])) {
        first_nonwhitespace_index = 1;
        break;
      }
    }
    return str.substr(first_nonwhitespace_index);
  }
  return str;
}

}  // namespace ht

// vim: et sw=2 ts=2
