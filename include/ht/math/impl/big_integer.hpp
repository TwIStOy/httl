// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include <algorithm>
#include <cstddef>
#include <limits>
#include <stdexcept>
#include <type_traits>
#include <utility>
#include <vector>

#include <ht/math/impl/big_integer_storage.hpp>
#include <ht/strings/stringify.hpp>

namespace ht {

template<int MaxSize, typename E = int32_t>
  requires std::is_signed_v<E>
class basic_big_integer
    : protected __big_integer_impl::basic_big_integer_storage<MaxSize, E> {
 public:
  using element_type_t = E;

  static constexpr element_type_t radix =
      std::numeric_limits<element_type_t>::max() / 2 - 1;

  static constexpr bool dynamic_extend = (MaxSize == -1);

  basic_big_integer() = default;

  template<int S>
  basic_big_integer operator+(const basic_big_integer<S, E>& rhs) const {
    if (this->neg_ == rhs.neg_) {
      auto res = do_simple_plus(rhs);
      res.neg_ = this->neg_;
      return res;
    } else if (!this->neg_ && rhs.neg_) {
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

  basic_big_integer pow(uint32_t p) const;

  basic_big_integer operator~() const;

  template<int S>
  std::pair<basic_big_integer, basic_big_integer> divide(
      const basic_big_integer<S>& rhs) const;

  template<int S>
  basic_big_integer operator<(const basic_big_integer<S>& rhs) const;

  template<int S>
  basic_big_integer operator>(const basic_big_integer<S>& rhs) const;

  template<int S>
  basic_big_integer operator==(const basic_big_integer<S>& rhs) const {
    if (this->count_ != rhs.count_) {
      return false;
    }
    for (auto i = 0; i < this->count_; i++) {
      if (this->digits_[i] != rhs.digits_[i]) {
        return false;
      }
    }
    return true;
  }

 private:
  void fix_count() {
    while (this->digits_[this->count_] != 0) {
      this->count_++;
    }
  }

  template<int S>
  auto do_simple_plus(const basic_big_integer<S, E>& rhs) const {
    auto expect_size = std::max(rhs.count_, this->count_) + 1;

    basic_big_integer res;
    res.reserve(expect_size);

    for (auto i = 0; i < expect_size; i++) {
      res.digits_[i] = this->digits_[i] + rhs.digits_[i];
    }
    res.digits_[expect_size] = 0;

    for (auto i = 0; i < expect_size; i++) {
      res.digits_[i + 1] += res.digits_[i] / radix;
      res.digits_[i] %= radix;
    }
    fix_count();

    return res;
  }

  template<int S>
  auto do_simple_substract(const basic_big_integer<S, E>& rhs) const {
    auto expect_size = std::max(rhs.count_, this->count_) + 1;

    basic_big_integer res;
    res.reserve(expect_size);

    for (auto i = 0; i < expect_size; i++) {
      res.digits_[i] = this->digits_[i] - rhs.digits_[i];
    }
    res.digits_[expect_size] = 0;

    for (auto i = 0; i < expect_size; i++) {
      if (res.digits_[i] < 0) {
        res.digits_[i] += radix;
        res.digits_[i + 1] -= 1;
      }
    }
    fix_count();

    return res;
  }

  bool neg_{false};
};

using big_integer = basic_big_integer<-1>;

}  // namespace ht

// vim: et sw=2 ts=2
