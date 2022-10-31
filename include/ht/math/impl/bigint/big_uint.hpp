// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include <algorithm>
#include <cstdint>
#include <vector>

namespace ht {

template<typename T = uint32_t>
class big_uint {
 public:
  using digit_t = T;
  /*
   * static constexpr digit_t radix =
   *     (static_cast<digit_t>(1) << (sizeof(digit_t) / 2)) - 1;
   */
 private:
  static void do_simple_add(const std::vector<digit_t>& lhs,
                            const std::vector<digit_t>& rhs,
                            std::vector<digit_t> *out) {
    /*
     * auto sz = std::max(lhs.size(), rhs.size());
     * out->resize(sz);
     *
     * for (auto i = 0u; i < sz; i++) {
     *   (*out)[i] = lhs[i] + rhs[i];
     *   if ((*out)[i] < lhs[i]) {
     *     (*out)[i + 1]++;
     *   }
     * }
     */
  }

 private:
  std::vector<digit_t> digits_;
};

}  // namespace ht

// vim: et sw=2 ts=2
