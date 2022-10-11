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
#include <ht/core/algorithm.hpp>
#include <ht/core/result.hpp>
#include <ht/parser_combinator/impl/input_stream.hpp>
#include <ht/parser_combinator/impl/parser.hpp>

namespace ht::combinators {

template<typename P>
auto combinator_option(P&& p) {
  using element_type = typename std::decay_t<P>::value_type;
  using value_type   = std::optional<element_type>;
  using result_t =
      result<std::pair<value_type, _parser_combinator_impl::input_stream>,
             std::string>;

  return make_parser([p = std::forward<P>(p)](const auto& _input) -> result_t {
    value_type res;
    _parser_combinator_impl::input_stream input = _input;

    auto r = p(input);
    if (r.is_err()) {
      return ok(std::make_pair(std::nullopt, _input));
    }
    return ok(r.unwrap());
    ;
  });
}

}  // namespace ht::combinators

// vim: et sw=2 ts=2
