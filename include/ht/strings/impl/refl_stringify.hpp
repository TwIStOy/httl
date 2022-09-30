// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include <ht/core/algorithm.hpp>
#include <ht/core/impl/tag_invoke.hpp>
#include <ht/core/reflect/helpers.hpp>
#include <ht/core/type_utils.hpp>
#include <ht/strings/impl/stringify.hpp>
#include <ostream>
#include <sstream>

namespace ht::_tag_impl {

template<typename T>
  requires has_refl_v<T>
auto tag_invoke(ht::tag_t<ht::stringify>, const T& value, uint16_t level,
                int16_t indent) {
  std::ostringstream oss;
  using info_t = refl_info<T>;

  if constexpr (info_t::num_properties() > 0) {
    oss << '{';
    if (indent >= 0) {
      oss << std::endl;
    }
    for_<info_t::num_properties()>([&](auto _i) {
      using i = decltype(_i);
      oss << _stringify_impl::__indent{indent,
                                       static_cast<uint16_t>(level + 1u)}
          << info_t::property_name().at(i::value) << " = ";
      oss << ht::stringify(refl_ref<i::value>(value), level + 1, indent);
      oss << ',';
      if (indent >= 0) {
        oss << std::endl;
      }
    });
    oss << _stringify_impl::__indent{indent, level} << '}';
  } else {
    oss << "{}";
    if (indent >= 0) {
      oss << std::endl;
    }
  }
  return oss.str();
}

template<typename T>
  requires has_refl_v<T>
auto tag_invoke(ht::tag_t<ht::debug_stringify>, const T& value, uint16_t level,
                int16_t indent) {
  std::ostringstream oss;
  using info_t = refl_info<T>;

  if constexpr (info_t::num_properties() > 0) {
    oss << "{";
    if (indent >= 0) {
      oss << std::endl;
    }
    for_<info_t::num_properties()>([&](auto _i) {
      using i = decltype(_i);
      oss << _stringify_impl::__indent{indent,
                                       static_cast<uint16_t>(level + 1u)}
          << info_t::property_name().at(i::value) << ": "
          << demangle<property_type_at<T, i::value>>() << " = ";
      oss << ht::debug_stringify(refl_ref<i::value>(value), level + 1, indent);
      oss << ',';
      if (indent >= 0) {
        oss << std::endl;
      }
    });
    oss << _stringify_impl::__indent{indent, level} << '}';
  } else {
    oss << "{}";
    if (indent >= 0) {
      oss << std::endl;
    }
  }
  return oss.str();
}

}  // namespace ht::_tag_impl

// vim: et sw=2 ts=2
