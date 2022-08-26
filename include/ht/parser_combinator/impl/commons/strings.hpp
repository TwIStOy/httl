// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include <regex>
#include <string_view>
#include <utility>

#include "ht/core/result.hpp"
#include "ht/parser_combinator/impl/input_stream.hpp"
#include "ht/parser_combinator/impl/parser.hpp"

namespace ht::combinators {

inline auto make_regex_parser(std::string_view s) {
  auto regex = std::regex(s.data(), s.size());
  return make_parser(
      [regex =
           std::move(regex)](const _parser_combinator_impl::input_stream &input)
          -> result<std::pair<std::string_view,
                              _parser_combinator_impl::input_stream>,
                    void> {
        auto res = std::cmatch();
        if (std::regex_search(std::begin(input.raw_input()),
                              std::end(input.raw_input()), res, regex,
                              std::regex_constants::match_continuous)) {
          auto match_len = res.length();
          return ok(std::make_pair(input.raw_input().substr(0, match_len),
                                   input.consume(match_len)));
        }

        return err();
      });
}

inline auto make_string_eq_parser(std::string_view s) {
  return make_parser(
      [s](const _parser_combinator_impl::input_stream &input)
          -> result<std::pair<std::string_view,
                              _parser_combinator_impl::input_stream>,
                    void> {
        if (input.raw_input().size() < s.size()) {
          return err();
        }
        auto first_bytes = std::string_view(input.raw_input().data(), s.size());
        if (s.compare(first_bytes) == 0) {
          return ok(std::make_pair(s, input.consume(s.size())));
        }

        return err();
      });
}

}  // namespace ht::combinators

// vim: et sw=2 ts=2
