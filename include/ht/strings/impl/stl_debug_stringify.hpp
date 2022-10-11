// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include <concepts>
#include <ranges>
#include <sstream>
#include <string>
#include <string_view>
#include <tuple>
#include <type_traits>
#include <utility>

#include <ht/core/cpp_feature.h>
#include <ht/core/algorithm.hpp>
#include <ht/core/impl/tag_invoke.hpp>
#include <ht/meta/meta.hpp>
#include <ht/strings/impl/stringify.hpp>

namespace ht::_tag_impl {

inline auto tag_invoke(ht::tag_t<ht::debug_stringify>, auto&& value, uint16_t,
                       int16_t)
  requires std::is_integral_v<std::remove_cvref_t<decltype(value)>> ||
           std::is_floating_point_v<std::remove_cvref_t<decltype(value)>>
{
  return std::to_string(HT_FORWARD(value));
}

inline auto tag_invoke(ht::tag_t<ht::debug_stringify>, auto&& str, uint16_t,
                       int16_t)
  requires std::same_as<std::remove_cvref_t<decltype(str)>, std::string> ||
           std::same_as<std::remove_cvref_t<decltype(str)>, std::string_view>
{
  std::ostringstream oss;
  oss << '"' << str << '"';
  return oss.str();
}

template<typename T, typename U>
inline auto tag_invoke(ht::tag_t<ht::debug_stringify>,
                       const std::pair<T, U>& value, uint16_t level,
                       int16_t indent) {
  std::ostringstream oss;

  oss << "(";
  if (indent >= 0) {
    oss << '\n';
  }
  oss << _stringify_impl::__indent{indent, static_cast<uint16_t>(level + 1)}
      << "first: " << pretty_typename<T>::value << " = "
      << ht::debug_stringify(value.first, level + 1, indent) << ",";
  if (indent >= 0) {
    oss << '\n';
  }
  oss << _stringify_impl::__indent{indent, static_cast<uint16_t>(level + 1)}
      << "second: " << pretty_typename<U>::value << " = "
      << ht::debug_stringify(value.first, level + 1, indent);
  if (indent >= 0) {
    oss << '\n';
  }

  oss << _stringify_impl::__indent{indent, level} << ")";

  return oss.str();
}

template<typename... Args>
inline auto tag_invoke(ht::tag_t<ht::debug_stringify>,
                       const std::tuple<Args...>& value, uint16_t level,
                       int16_t indent) {
  std::ostringstream oss;

  oss << "(";
  if (indent >= 0) {
    oss << '\n';
  }
  for_<sizeof...(Args)>([&](auto _i) {
    using i = decltype(_i);
    oss << _stringify_impl::__indent{indent, static_cast<uint16_t>(level + 1)}
        << "[" << i::value << "]: "
        << pretty_typename<
               std::tuple_element_t<i::value, std::tuple<Args...>>>::value
        << " = "
        << ht::debug_stringify(std::get<i::value>(value), level + 1, indent)
        << ",";
    if (indent >= 0) {
      oss << '\n';
    }
  });
  oss << ")";

  return oss.str();
}

inline std::string tag_invoke(ht::tag_t<ht::debug_stringify>, auto&& value,
                              uint16_t level, int16_t indent)
  requires std::ranges::sized_range<HT_TYPE(value)> &&
           (!is_map_v<HT_TYPE(value)>) &&
           (!std::same_as<HT_TYPE(value), std::string>) &&
           (!std::same_as<HT_TYPE(value), std::string_view>)
{
  std::string_view marker = "[]";
  if constexpr (requires { typename HT_TYPE(value)::key_type; }) {
    marker = "{}";
  }

  if (std::ranges::size(value) == 0) [[unlikely]] {
    return marker.data();
  } else {
    std::ostringstream oss;
    auto end = std::ranges::end(value);
    oss << marker[0];
    if (indent >= 0) {
      oss << '\n';
    }
    uint32_t index = 0;
    for (auto it = std::ranges::begin(value); it != end; ++it) {
      oss << _stringify_impl::__indent{indent, static_cast<uint16_t>(level + 1)}
          << "[" << index++
          << "] = " << ht::debug_stringify(*it, level + 1, indent) << ',';
      if (indent >= 0) {
        oss << '\n';
      }
    }
    oss << marker[1];
    return oss.str();
  }
}

std::string tag_invoke(ht::tag_t<ht::debug_stringify>, auto&& value,
                       uint16_t level, int16_t indent)
  requires std::ranges::sized_range<HT_TYPE(value)> && is_map_v<HT_TYPE(value)>
{
  using key_type    = typename HT_TYPE(value)::key_type;
  using mapped_type = typename HT_TYPE(value)::mapped_type;

  if (std::ranges::size(value) == 0) [[unlikely]] {
    return "{}";
  } else {
    std::ostringstream oss;
    auto end = std::ranges::end(value);
    oss << "{";
    if (indent >= 0) {
      oss << '\n';
    }
    for (auto it = std::ranges::begin(value); it != end; ++it) {
      oss << _stringify_impl::__indent{indent, static_cast<uint16_t>(level + 1)}
          << ht::debug_stringify(it->first, level + 1, indent) << " = "
          << ht::debug_stringify(it->second, level + 1, indent) << ',';
      if (indent >= 0) {
        oss << '\n';
      }
    }
    oss << "}";
    return oss.str();
  }
}

}  // namespace ht::_tag_impl

// vim: et sw=2 ts=2
