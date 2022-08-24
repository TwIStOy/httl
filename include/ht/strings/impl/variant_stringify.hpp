// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include <sstream>
#include <variant>

#include "ht/core/type_utils.hpp"
#include "ht/strings/impl/stringify.hpp"

namespace ht::_tag_impl {

template<typename... Args>
auto tag_invoke(stringify_fn, const std::variant<Args...> &value,
                uint16_t level, int16_t indent) {
  (void)level;
  (void)indent;

  return std::visit(
      [&](const auto &r) {
        return ht::stringify(r, level, indent);
      },
      value);
}

/*
 * template<typename... Args>
 * auto tag_invoke(debug_stringify_fn, const std::variant<Args...> &value) {
 *   return std::visit(
 *       [](const auto &r) {
 *         std::ostringstream oss;
 *         oss << demangle<std::variant<Args...>>();
 *         oss << "{" << stringify(r) << "}";
 *         return oss.str();
 *       },
 *       value);
 * }
 */

}  // namespace ht::_tag_impl

// vim: et sw=2 ts=2
