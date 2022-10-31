// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include <cstdint>

namespace ht {

template<typename T>
auto quick_pow(T a, uint16_t p) {
  T res = 1;
  while (p) {
    if (p & 1) {
      res = res * a;
    }
    a = a * a;
    p /= 2;
  }
  return res;
}

template<typename T>
auto quick_pow(T a, uint16_t p, T m) {
  T res = 1;
  while (p) {
    if (p & 1) {
      res = (res * a) % m;
    }
    a = (a * a) % m;
    p /= 2;
  }
  return res;
}

}  // namespace ht

// vim: et sw=2 ts=2
