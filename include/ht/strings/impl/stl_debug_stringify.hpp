// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include <ht/core/algorithm.hpp>
#include <ht/core/impl/tag_invoke.hpp>
#include <ht/core/type_utils.hpp>
#include <ht/strings/impl/stringify.hpp>
#include <ranges>
#include <sstream>
#include <string>
#include <tuple>
#include <type_traits>
#include <utility>

namespace ht::_tag_impl {

template<typename T>
  requires std::is_integral_v<T>
inline auto tag_invoke(ht::tag_t<ht::debug_stringify>, const T &value, uint16_t,
                       int16_t) {
  std::ostringstream oss;
  oss << value;
  return oss.str();
}

inline auto tag_invoke(ht::tag_t<ht::debug_stringify>, const std::string &str,
                       uint16_t, int16_t) {
  std::ostringstream oss;
  oss << '"' << str << '"';
  return oss.str();
}

template<typename T, typename U>
inline auto tag_invoke(ht::tag_t<ht::debug_stringify>,
                       const std::pair<T, U> &value, uint16_t level,
                       int16_t indent) {
  std::ostringstream oss;

  oss << "(";
  if (indent >= 0) {
    oss << std::endl;
  }
  oss << _stringify_impl::__indent{indent, static_cast<uint16_t>(level + 1)}
      << "first: " << demangle<T>() << " = "
      << ht::debug_stringify(value.first, level + 1, indent) << ",";
  if (indent >= 0) {
    oss << std::endl;
  }
  oss << _stringify_impl::__indent{indent, static_cast<uint16_t>(level + 1)}
      << "second: " << demangle<U>() << " = "
      << ht::debug_stringify(value.first, level + 1, indent);
  if (indent >= 0) {
    oss << std::endl;
  }

  oss << _stringify_impl::__indent{indent, level} << ")";

  return oss.str();
}

template<typename... Args>
inline auto tag_invoke(ht::tag_t<ht::debug_stringify>,
                       const std::tuple<Args...> &value, uint16_t level,
                       int16_t indent) {
  std::ostringstream oss;

  oss << "(";
  if (indent >= 0) {
    oss << std::endl;
  }
  for_<sizeof...(Args)>([&](auto _i) {
    using i = decltype(_i);
    oss << _stringify_impl::__indent{indent, static_cast<uint16_t>(level + 1)}
        << "[" << i::value << "]: "
        << demangle<std::tuple_element_t<i::value, std::tuple<Args...>>>()
        << " = "
        << ht::debug_stringify(std::get<i::value>(value), level + 1, indent)
        << ",";
    if (indent >= 0) {
      oss << std::endl;
    }
  });
  oss << ")";

  return oss.str();
}

template<std::ranges::sized_range T>
inline std::string tag_invoke(ht::tag_t<ht::debug_stringify>, const T &value,
                              uint16_t level, int16_t indent) {
  if (std::ranges::size(value) == 0) {
    return "[]";
  } else {
    std::ostringstream oss;
    auto end = std::ranges::end(value);
    oss << "[";
    if (indent >= 0) {
      oss << std::endl;
    }
    uint32_t index = 0;
    for (auto it = std::ranges::begin(value); it != end; ++it) {
      oss << _stringify_impl::__indent{indent, static_cast<uint16_t>(level + 1)}
          << "[" << index++
          << "] = " << ht::debug_stringify(*it, level + 1, indent) << ',';
      if (indent >= 0) {
        oss << std::endl;
      }
    }
    oss << "]";
    return oss.str();
  }
}

}  // namespace ht::_tag_impl

// vim: et sw=2 ts=2
