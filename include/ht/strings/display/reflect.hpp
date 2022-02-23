// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include <fmt/format.h>

#include <sstream>
#include <type_traits>
#include <utility>

#include "ht/core/reflect/helpers.hpp"
#include "ht/strings/display.hpp"

namespace ht::display_helper {

template<typename T>
struct DebugDisplayHelper<T, std::void_t<std::enable_if_t<has_refl_v<T>>>> {
  refl_info<T> info;

  std::string operator()(const T &obj) const {
    std::ostringstream oss;
    oss << info.get_name();

    if constexpr (info.num_properties() > 0) {
      oss << " {";
      display_recursive(
          oss, obj,
          std::make_integer_sequence<uint32_t, info.num_properties()>{});
      oss << "}";
    } else {
      oss << " {}";
    }

    return oss.str();
  }

 private:
  template<uint32_t I, uint32_t... Rest>
  void display_recursive(std::ostringstream &oss, const T &obj,
                         std::integer_sequence<uint32_t, I, Rest...>) {
    oss << "  " << info.property_name().at(I) << ": "
        << show_sub_value(refl_ref<I>(obj)) << std::endl;
    if constexpr (sizeof...(Rest) > 0) {
      display_recursive(oss, obj, std::integer_sequence<uint32_t, Rest...>{});
    }
  }

  template<typename U>
  std::string show_sub_value(const U &v) const {
    if constexpr (IsDebugHelperImpled<U>::value) {
      return fmt::format("{:?}", v);
    } else {
      return fmt::format("{}", v);
    }
  }
};

}  // namespace ht::display_helper
