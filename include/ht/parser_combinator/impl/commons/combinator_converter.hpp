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
#include <ht/core/type_traits.hpp>
#include <ht/parser_combinator/impl/input_stream.hpp>
#include <ht/parser_combinator/impl/parser.hpp>

namespace ht::combinators {

template<typename P, typename F>
  requires std::invocable<F, typename std::remove_cvref_t<P>::value_type>
auto combinator_converter(P&& p, F&& f) {
  using from_type  = typename std::decay_t<P>::value_type;
  using value_type = std::invoke_result_t<F, from_type>;
  using error_type = typename std::decay_t<P>::error_type;
  using result_t =
      result<std::pair<value_type, _parser_combinator_impl::input_stream>,
             error_type>;

  return make_parser([p = std::forward<P>(p),
                      f = std::forward<F>(f)](const auto& _input) -> result_t {
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

template<typename P, typename F>
auto operator>>(P&& p, F&& f) {
  return combinators::combinator_converter(std::forward<P>(p),
                                           std::forward<F>(f));
}

}  // namespace ht::_parser_combinator_impl

// vim: et sw=2 ts=2
