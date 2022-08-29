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

#include "fmt/format.h"
#include "ht/core/algorithm.hpp"
#include "ht/core/result.hpp"
#include "ht/core/type_traits.hpp"
#include "ht/parser_combinator/impl/input_stream.hpp"
#include "ht/parser_combinator/impl/parser.hpp"

namespace ht::combinators {

template<typename U, typename... R>
inline constexpr bool all_same_impl = (std::is_same_v<U, R> && ...);

template<typename U>
inline constexpr bool all_same_impl<U> = true;

template<typename... T>
inline constexpr bool all_same = all_same_impl<T...>;

template<>
inline constexpr bool all_same<> = true;

namespace __detail {

template<typename R, typename P, typename... Ps>
R exec_impl(const _parser_combinator_impl::input_stream &input, P &&p,
            Ps &&...ps) {
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

template<typename... Ps>
  requires(is_parser_v<std::decay_t<Ps>> && ...) &&
          all_same<typename std::decay_t<Ps>::value_type...>
auto combinator_or(Ps &&...ps) {
  using ps_result_t = std::tuple<typename std::decay_t<Ps>::result_t...>;
  using value_type =
      typename std::tuple_element_t<0, ps_result_t>::value_type::first_type;
  using result_t =
      result<std::pair<value_type, _parser_combinator_impl::input_stream>,
             std::string>;

  return make_parser(
      [... ps = std::forward<Ps>(ps)](
          const _parser_combinator_impl::input_stream &_input) -> result_t {
        return __detail::exec_impl<result_t>(_input, ps...);
      });
}

}  // namespace ht::combinators

namespace ht::_parser_combinator_impl {

template<typename T, typename U>
  requires is_parser_v<std::decay_t<T>> && is_parser_v<std::decay_t<U>>
auto operator||(T &&p0, U &&p1) {
  return combinators::combinator_or(std::forward<T>(p0), std::forward<U>(p1));
}

}  // namespace ht::_parser_combinator_impl

// vim: et sw=2 ts=2
