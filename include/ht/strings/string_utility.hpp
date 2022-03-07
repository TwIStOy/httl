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
#include <sstream>
#include <string>
#include <string_view>
#include <type_traits>

#include "ht/core/cpp_feature.h"
#include "ht/strings/display.hpp"

namespace ht {

inline std::string_view RemoveLeadingSpaces(std::string_view str) {
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

template<typename ForwardIterator>
std::string JoinString(ForwardIterator start, ForwardIterator end,
                       std::string_view separator) {
  using value_t = typename std::iterator_traits<ForwardIterator>::value_type;

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
      oss << *it;
    }
  }

  return oss.str();
}

template<typename ForwardIterator, typename F>
std::string JoinString(ForwardIterator start, ForwardIterator end,
                       std::string_view separator, F f) {
  using value_t = typename std::iterator_traits<ForwardIterator>::value_type;

  std::ostringstream oss;

  for (auto it = start; it != end; ++it) {
    if (it != start) {
      oss << separator;
    }
    oss << f(*it);
  }

  return oss.str();
}

template<typename Container, typename F>
inline std::string JoinString(const Container &container,
                              std::string_view separator, F f) {
  return JoinString(std::begin(container), std::end(container), separator,
                    std::move(f));
}

template<typename Container>
inline std::string JoinString(const Container &container,
                              std::string_view separator) {
  return JoinString(std::begin(container), std::end(container), separator);
}

}  // namespace ht

// vim: et sw=2 ts=2
