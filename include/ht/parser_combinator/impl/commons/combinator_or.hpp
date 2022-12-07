// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include <concepts>
#include <string>
#include <tuple>
#include <type_traits>
#include <utility>

#include <fmt/format.h>
#include <ht/core/result.hpp>
#include <ht/meta/impl/same_types.hpp>
#include <ht/parser_combinator/impl/input_stream.hpp>
#include <ht/parser_combinator/impl/parser.hpp>

namespace ht::combinators {

namespace __detail {

template<typename R, typename P, typename... Ps>
R exec_impl(const _parser_combinator_impl::input_stream& input, P&& p,
            Ps&&...ps) {
  auto r = p(input);
  if (r.is_ok()) {
    return ok(std::move(r).unwrap());
  } else {
    if constexpr (sizeof...(Ps) > 0) {
      return exec_impl<R>(input, std::forward<Ps>(ps)...);
    } else {
      return err("combine operator: or, failed");
    }
  }
}

}  // namespace __detail

auto combinator_or(as_parser auto&&...ps) {
  using value_type = std::common_type_t<typename HT_TYPE(ps)::value_type...>;
  using result_t =
      result<std::pair<value_type, _parser_combinator_impl::input_stream>,
             std::string>;

  return make_parser(
      [... ps = HT_FORWARD(ps)](
          const _parser_combinator_impl::input_stream& _input) -> result_t {
        return __detail::exec_impl<result_t>(_input, ps...);
      });
}

}  // namespace ht::combinators

namespace ht::_parser_combinator_impl {

auto operator||(as_parser auto&& p0, as_parser auto&& p1) {
  return combinators::combinator_or(HT_FORWARD(p0), HT_FORWARD(p1));
}

}  // namespace ht::_parser_combinator_impl

// vim: et sw=2 ts=2
