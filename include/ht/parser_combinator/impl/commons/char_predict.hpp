// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include <utility>

#include "ht/core/result.hpp"
#include "ht/parser_combinator/impl/input_stream.hpp"
#include "ht/parser_combinator/impl/parser.hpp"

namespace ht::combinators {

template<typename F>
inline auto make_char_predict_parser(F &&f) {
  return make_parser([p = std::forward<F>(f)](
                         const _parser_combinator_impl::input_stream &input)
                         -> parser_result_t<char, std::string> {
    if (input.is_eof()) {
      return err("reach eof");
    }
    if (p(input.raw_input().front())) {
      return ok(std::make_pair(input.raw_input().front(), input.consume(1)));
    }
    return err("predict failed");
  });
}

static inline auto char_any = make_char_predict_parser([](char) {
  return true;
});

}  // namespace ht::combinators

// vim: et sw=2 ts=2
