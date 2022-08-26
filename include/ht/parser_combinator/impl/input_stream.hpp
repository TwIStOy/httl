// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include <cassert>
#include <string_view>

namespace ht::_parser_combinator_impl {

struct input_stream {
  struct position {
    uint32_t row;
    uint32_t column;
  };

  inline input_stream(std::string_view s, position p) : str_(s), pos_(p) {
  }

  inline explicit input_stream(std::string_view s) : str_(s), pos_{1, 1} {
  }

  [[nodiscard]] inline bool is_eof() const {
    return str_.empty();
  }

  [[nodiscard]] inline std::string_view raw_input() const {
    return str_;
  }

  [[nodiscard]] inline input_stream consume(uint32_t n) const {
    assert(n <= str_.size());

    auto new_pos = pos_;

    for (auto i = 0u; i < n; ++i) {
      auto ch = str_[i];
      if (ch == '\n') {
        ++new_pos.row;
        new_pos.column = 1;
      } else {
        ++new_pos.column;
      }
    }
    return {str_.substr(n), new_pos};
  }

  [[nodiscard]] inline uint32_t current_line() const {
    return pos_.row;
  }

  [[nodiscard]] inline uint32_t current_column() const {
    return pos_.column;
  }

 private:
  std::string_view str_;
  position pos_;
};

}  // namespace ht::_parser_combinator_impl

// vim: et sw=2 ts=2
