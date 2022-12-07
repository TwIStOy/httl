// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include <concepts>
#include <optional>
#include <ranges>
#include <string>
#include <tuple>
#include <type_traits>
#include <utility>
#include <vector>

#include <fmt/format.h>
#include <ht/core/result.hpp>
#include <ht/parser_combinator/impl/input_stream.hpp>
#include <ht/parser_combinator/impl/parser.hpp>

namespace ht::combinators {

auto combinator_converter(as_parser auto&& p, auto&& f)
  requires std::invocable<HT_TYPE(f), typename HT_TYPE(p)::value_type>
{
  using from_type  = typename HT_TYPE(p)::value_type;
  using value_type = std::invoke_result_t<HT_TYPE(f), from_type>;
  using error_type = typename HT_TYPE(p)::error_type;
  using result_t =
      result<std::pair<value_type, _parser_combinator_impl::input_stream>,
             error_type>;

  return make_parser(
      [p = HT_FORWARD(p), f = HT_FORWARD(f)](const auto& _input) -> result_t {
        auto input = _input;

        auto r = p(input);
        if (r.is_err()) {
          if constexpr (std::is_same_v<error_type, void>) {
            return err();
          } else {
            return err(std::move(r).unwrap_err());
          }
        }
        return ok(std::make_pair(f(std::move(std::move(r).unwrap().first)),
                                 r.unwrap().second));
      });
}

}  // namespace ht::combinators

namespace ht::_parser_combinator_impl {

auto operator>>(auto&& p, auto&& f) {
  return combinators::combinator_converter(HT_FORWARD(p), HT_FORWARD(f));
}

}  // namespace ht::_parser_combinator_impl

// vim: et sw=2 ts=2
