// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include <cxxabi.h>

#include <memory>
#include <string>

namespace ht {

template<typename T>
std::string demangle() {
  int status;
  std::unique_ptr<char[], void (*)(void *)> result(
      abi::__cxa_demangle(typeid(T).name(), nullptr, nullptr, &status),
      std::free);
  return result ? std::string(result.get()) : "error occurred";
}

}  // namespace ht

// vim: et sw=2 ts=2
