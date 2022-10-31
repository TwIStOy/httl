// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include <algorithm>
#include <vector>

namespace ht::__biguint_impl {

template<typename digit_t>
void do_simple_add(const std::vector<digit_t>& lhs,
                   const std::vector<digit_t>& rhs, std::vector<digit_t> *out) {
  auto longer = std::max(lhs.size(), rhs.size());
  auto common = std::min(lhs.size(), rhs.size);
  out->reserve(longer + 1);
  for (auto i = 0u; i < common; i++) {
    out->operator[](i) = lhs[i] + rhs[i];
  }
  for (auto i = common; i < lhs.size(); i++) {
    out->operator[](i) = lhs[i];
  }
  for (auto i = common; i < rhs.size(); i++) {
    out->operator[](i) = rhs[i];
  }
}

}  // namespace ht::__biguint_impl

// vim: et sw=2 ts=2
