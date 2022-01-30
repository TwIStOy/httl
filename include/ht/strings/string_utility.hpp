// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include <cstring>
#include <functional>
#include <sstream>
#include <string>
#include <string_view>
#include <type_traits>

#include "ht/strings/display.hpp"

namespace ht {

inline std::string_view RemoveLeadingSpaces(std::string_view str) {
  if (str.length() && std::isspace(str[0])) {
    uint32_t first_nonwhitespace_index = 0;
    for (uint32_t i = 0; i < str.length(); i++) {
      if (!std::isspace(str[i])) {
        first_nonwhitespace_index = 1;
        break;
      }
    }
    return str.substr(first_nonwhitespace_index);
  }
  return str;
}

template<typename ForwardIterator>
std::string JoinString(
    ForwardIterator start, ForwardIterator end, std::string_view separator,
    std::function<std::string(const typename ForwardIterator::value_t &)> f =
        {}) {
  using value_t = typename ForwardIterator::value_t;

  std::ostringstream oss;

  if constexpr (std::is_base_of_v<IDisplay, value_t>) {
    for (auto it = start; it != end; ++it) {
      if (it != start) {
        oss << separator;
      }
      (*it).Stringify(oss);
    }
  } else {
    for (auto it = start; it != end; ++it) {
      if (it != start) {
        oss << separator;
      }
      if (f) {
        oss << f(*it);
      } else {
        oss << *it;
      }
    }
  }

  return oss.str();
}

template<typename Container>
inline std::string JoinString(
    const Container &container, std::string_view separator,
    std::function<std::string(typename Container::const_reference)> f = {}) {
  return JoinString(std::begin(container), std::end(container),
                    std::move(separator), std::move(f));
}

}  // namespace ht

// vim: et sw=2 ts=2
