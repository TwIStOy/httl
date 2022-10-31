// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include <array>
#include <cstddef>
#include <cstdint>
#include <limits>
#include <stdexcept>
#include <vector>

namespace ht {

class big_integer_exception : std::runtime_error {
 public:
  using runtime_error::runtime_error;
};

}  // namespace ht

namespace ht::__big_integer_impl {

template<int MaxSize, typename E>
struct basic_big_integer_storage {
  uint32_t count_ = 0;
  std::array<E, MaxSize> digits_;

  inline void reserve(uint32_t sz) {
    if (sz > MaxSize) [[unlikely]] {
      throw big_integer_exception("Reserve overflow");
    }
  }
};

template<typename E>
struct basic_big_integer_storage<-1, E> {
  uint32_t count_ = 0;
  std::vector<E> digits_;

  inline void reserve(uint32_t sz) {
    digits_.resize(sz);
  }
};

}  // namespace ht::__big_integer_impl

// vim: et sw=2 ts=2
