// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include <array>
#include <concepts>
#include <cstring>
#include <functional>
#include <iterator>
#include <sstream>
#include <string>
#include <string_view>
#include <type_traits>
#include <vector>

#include <ht/core/cpp_feature.h>
#include <ht/strings/impl/str_join_impl.hpp>
#include <ht/strings/impl/stringify.hpp>
#include <range/v3/core.hpp>
#include <range/v3/range/concepts.hpp>

namespace ht {

/**
 * Remove leading spaces from given string.
 */
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

/**
 * Extract parts of strings that are separated by any of the characters in sep.
 */
template<template<typename> class C = std::vector>
C<std::string> str_split(std::string_view input, std::string_view sep) {
  C<std::string> tokens;
  std::string_view::size_type tokend = 0;

  do {
    auto tokstart = input.find_first_not_of(sep, tokend);
    if (tokstart == std::string_view::npos) {
      break;  // no more tokens
    }
    tokend = input.find_first_of(sep, tokstart);
    if (tokend == std::string_view::npos) {
      tokens.emplace_back(input.substr(tokstart));
    } else {
      tokens.emplace_back(input.substr(tokstart, tokend - tokstart));
    }
  } while (tokend != std::string_view::npos);

  if (tokens.empty()) {
    tokens.emplace_back();
  }
  return tokens;
}

}  // namespace ht

// vim: et sw=2 ts=2
