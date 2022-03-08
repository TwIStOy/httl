// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include <cxxabi.h>

#include <memory>
#include <sstream>
#include <string>
#include <type_traits>
#include <typeinfo>
#include <variant>

#include "ht/strings/display.hpp"

namespace ht::display_helper {

namespace _impl_variant {
template<typename T>
inline std::string Demangle() {
  int status;
  std::unique_ptr<char[], void (*)(void *)> result(
      abi::__cxa_demangle(typeid(T).name(), nullptr, nullptr, &status),
      std::free);
  return result ? std::string(result.get()) : "???";
}

}  // namespace _impl_variant

template<typename... Args>
struct DisplayHelper<std::variant<Args...>> {
  using variant_t = std::variant<Args...>;
  std::string operator()(const variant_t &obj) const {
    return std::visit(
        [](const auto &r) {
          return Stringify(r);
        },
        obj);
  }
};

}  // namespace ht::display_helper

// vim: et sw=2 ts=2
