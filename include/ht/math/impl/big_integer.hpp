// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include <cstddef>
#include <stdexcept>
#include <utility>

#include "ht/strings/stringify.hpp"

namespace ht {

class big_integer_exception : std::runtime_error {
 public:
  using runtime_error::runtime_error;
};

template<int MaxSize>
class basic_big_integer {
 public:
  basic_big_integer();

  template<int S>
  basic_big_integer operator+(const basic_big_integer<S>& rhs) const {
    if constexpr (MaxSize > 0) {
      // check result
    }
  }

  template<int S>
  basic_big_integer operator-(const basic_big_integer<S>& rhs) const;

  template<int S>
  basic_big_integer operator*(const basic_big_integer<S>& rhs) const;

  template<int S>
  basic_big_integer operator/(const basic_big_integer<S>& rhs) const;

  template<int S>
  basic_big_integer operator%(const basic_big_integer<S>& rhs) const;

  template<int S>
  basic_big_integer operator^(const basic_big_integer<S>& rhs) const;

  template<int S>
  basic_big_integer operator&(const basic_big_integer<S>& rhs) const;

  template<int S>
  basic_big_integer operator|(const basic_big_integer<S>& rhs) const;

  basic_big_integer operator~() const;

  template<int S>
  std::pair<basic_big_integer, basic_big_integer> divide(
      const basic_big_integer<S>& rhs) const;

  template<int S>
  basic_big_integer operator<(const basic_big_integer<S>& rhs) const;

  template<int S>
  basic_big_integer operator>(const basic_big_integer<S>& rhs) const;

  template<int S>
  basic_big_integer operator==(const basic_big_integer<S>& rhs) const;

 private:
};

using big_integer = basic_big_integer<-1>;

}  // namespace ht

// vim: et sw=2 ts=2
