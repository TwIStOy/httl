// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#include <string>
#include <utility>

#include "catch2/catch_all.hpp"
#include "catch2/catch_test_macros.hpp"
#include "ht/core/result.hpp"
#include "ht/parser_combinator/impl/commons/combinator_many.hpp"
#include "ht/parser_combinator/impl/commons/combinator_or.hpp"
#include "ht/parser_combinator/impl/commons/combinator_plus.hpp"
#include "ht/parser_combinator/impl/input_stream.hpp"
#include "ht/parser_combinator/impl/parser.hpp"

TEST_CASE("construct simple parser", "[parser_combinator]") {
  auto parser = ht::make_parser(
      [](const ht::_parser_combinator_impl::input_stream &input)
          -> ht::result<
              std::pair<char, ht::_parser_combinator_impl::input_stream>,
              void> {
        if (!input.is_eof()) {
          auto first_char = input.raw_input().front();
          if (first_char == ' ') {
            return ht::ok(std::make_pair(' ', input.consume(1)));
          } else {
            return ht::err();
          }
        }
        return ht::err();
      });

  std::string input = "  ";

  auto s = parser(ht::_parser_combinator_impl::input_stream{input});
  REQUIRE(s.is_ok());
  REQUIRE(s.unwrap().first == ' ');
  REQUIRE(s.unwrap().second.current_column() == 2);
}

TEST_CASE("combinator plus", "[parser_combinator]") {
  auto parser = ht::make_parser(
      [](const ht::_parser_combinator_impl::input_stream &input)
          -> ht::result<
              std::pair<char, ht::_parser_combinator_impl::input_stream>,
              void> {
        if (!input.is_eof()) {
          auto first_char = input.raw_input().front();
          if (first_char == ' ') {
            return ht::ok(std::make_pair(' ', input.consume(1)));
          } else {
            return ht::err();
          }
        }
        return ht::err();
      });

  { auto new_parser = ht::combinators::combinator_plus(parser, parser); }
  auto new_parser   = parser + parser;
  std::string input = "   ";

  auto s = new_parser(ht::_parser_combinator_impl::input_stream{input});
  REQUIRE(s.is_ok());
  REQUIRE(s.unwrap().first == std::make_tuple(' ', ' '));
  REQUIRE(s.unwrap().second.current_column() == 3);
}

TEST_CASE("combinator or", "[parser_combinator]") {
  auto expect0 = ht::make_parser(
      [](const ht::_parser_combinator_impl::input_stream &input)
          -> ht::result<
              std::pair<char, ht::_parser_combinator_impl::input_stream>,
              void> {
        if (!input.is_eof()) {
          auto first_char = input.raw_input().front();
          if (first_char == '0') {
            return ht::ok(std::make_pair('0', input.consume(1)));
          } else {
            return ht::err();
          }
        }
        return ht::err();
      });

  auto expect1 = ht::make_parser(
      [](const ht::_parser_combinator_impl::input_stream &input)
          -> ht::result<
              std::pair<char, ht::_parser_combinator_impl::input_stream>,
              void> {
        if (!input.is_eof()) {
          auto first_char = input.raw_input().front();
          if (first_char == '1') {
            return ht::ok(std::make_pair('1', input.consume(1)));
          } else {
            return ht::err();
          }
        }
        return ht::err();
      });

  auto new_parser = ht::combinators::combinator_or(expect0, expect1);
  {
    std::string input = "011";

    auto s = new_parser(ht::_parser_combinator_impl::input_stream{input});
    REQUIRE(s.is_ok());
    REQUIRE(s.unwrap().first == '0');
    REQUIRE(s.unwrap().second.current_column() == 2);
  }

  {
    std::string input = "111";

    auto s = new_parser(ht::_parser_combinator_impl::input_stream{input});
    REQUIRE(s.is_ok());
    REQUIRE(s.unwrap().first == '1');
    REQUIRE(s.unwrap().second.current_column() == 2);
  }
}

TEST_CASE("combinator many", "[parser_combinator]") {
  auto parser = ht::make_parser(
      [](const ht::_parser_combinator_impl::input_stream &input)
          -> ht::result<
              std::pair<char, ht::_parser_combinator_impl::input_stream>,
              void> {
        if (!input.is_eof()) {
          auto first_char = input.raw_input().front();
          if (first_char == '0') {
            return ht::ok(std::make_pair('0', input.consume(1)));
          } else {
            return ht::err();
          }
        }
        return ht::err();
      });

  auto new_parser   = parser * 0;
  std::string input = "000";

  auto s = new_parser(ht::_parser_combinator_impl::input_stream{input});
  REQUIRE(s.is_ok());
  REQUIRE(s.unwrap().first.size() == 3);
  REQUIRE(s.unwrap().second.current_column() == 4);
}

// vim: et sw=2 ts=2
