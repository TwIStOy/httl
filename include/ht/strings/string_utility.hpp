// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include <ht/core/cpp_feature.h>

#include <concepts>
#include <cstring>
#include <functional>
#include <ht/strings/stringify.hpp>
#include <iterator>
#include <ranges>
#include <sstream>
#include <string>
#include <string_view>
#include <type_traits>
#include <vector>

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
 * Joins elements of a range with separator into a single string.
 */
template<std::ranges::sized_range Rng>
std::string str_join(const Rng& container, std::string_view sep) {
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

/**
 * Joins elements of a range with separator into a single string.
 */
template<std::ranges::sized_range C, typename F>
  requires std::invocable<F, std::ranges::range_value_t<C>>
std::string str_join(const C& container, std::string_view sep, F&& f) {
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
