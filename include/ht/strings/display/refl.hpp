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
struct DisplayHelper<T, std::void_t<std::enable_if_t<has_refl_v<T>>>> {
  using info_t = refl_info<T>;

  std::string operator()(const T &obj) const {
    std::ostringstream oss;
    oss << info_t::get_name();

    if constexpr (info_t::num_properties() > 0) {
      oss << " {" << std::endl;
      display_recursive(
          oss, obj,
          std::make_integer_sequence<uint32_t, info_t::num_properties()>{});
      oss << "}";
    } else {
      oss << " {}";
    }

    return oss.str();
  }

 private:
  template<uint32_t I, uint32_t... Rest>
  static void display_recursive(std::ostringstream &oss, const T &obj,
                                std::integer_sequence<uint32_t, I, Rest...>) {
    oss << "  " << info_t::property_name().at(I) << ": ";
    {
      std::ostringstream tmp_oss;
      tmp_oss << refl_ref<I>(obj);
      std::istringstream iss(tmp_oss.str());
      std::string line;
      bool first = true;
      while (std::getline(iss, line)) {
        if (first) {
          first = false;
        } else {
          oss << std::endl << "  ";
        }
        oss << line;
      }
    }
    oss << std::endl;
    if constexpr (sizeof...(Rest) > 0) {
      display_recursive(oss, obj, std::integer_sequence<uint32_t, Rest...>{});
    }
  }
};

}  // namespace ht::display_helper
