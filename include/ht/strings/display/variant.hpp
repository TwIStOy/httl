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

template<typename... Args>
struct DebugDisplayHelper<std::variant<Args...>> {
  using variant_t = std::variant<Args...>;

  std::string operator()(const variant_t &obj) const {
    std::ostringstream oss;
    oss << "std::variant<";
    MergeTypes<Args...>(oss);
    oss << ">(";

    std::visit(
        [&](const auto &r) {
          oss << _impl_variant::Demangle<std::decay_t<decltype(r)>>() << ": ";
          DisplayDebugString(oss, r);
        },
        obj);
    oss << ")";

    return oss.str();
  }

 private:
  template<typename First, typename... Rest>
  static void MergeTypes(std::ostringstream &oss) {
    oss << _impl_variant::Demangle<First>();
    ((oss << ", " << _impl_variant::Demangle<Rest>()), ...);
  }
};

}  // namespace ht::display_helper

// vim: et sw=2 ts=2
