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
#include <ht/core/algorithm.hpp>
#include <ht/core/result.hpp>
#include <ht/parser_combinator/impl/input_stream.hpp>
#include <ht/parser_combinator/impl/parser.hpp>

namespace ht::combinators {

template<typename... T, std::size_t... Is>
auto flat_tuple_impl(std::tuple<T...>&& t, std::index_sequence<Is...>) {
  return std::tuple_cat(std::move(std::get<Is>(t))...);
}

template<typename... T>
auto flat_tuple(std::tuple<T...>&& t) {
  return flat_tuple_impl(std::move(t),
                         std::make_index_sequence<sizeof...(T)>{});
}

template<typename... Ps>
auto combinator_plus(Ps&&...ps) {
  using ps_result_t = std::tuple<typename std::decay_t<Ps>::result_t...>;
  using value_type  = decltype(std::tuple_cat(
      std::declval<typename std::decay_t<Ps>::result_as_tuple_t>()...));
  using result_t =
      result<std::pair<value_type, _parser_combinator_impl::input_stream>,
             std::string>;
  using no_flat_value_t =
      std::tuple<typename std::decay_t<Ps>::result_as_tuple_t...>;

  return make_parser(
      [ps = std::tuple<Ps...>(std::forward<Ps>(ps)...)](
          const _parser_combinator_impl::input_stream& _input) -> result_t {
        _parser_combinator_impl::input_stream input = _input;

        bool has_error = false;
        std::string error_msg;
        no_flat_value_t value;

        for_<sizeof...(Ps)>([&](auto _i) {
          static constexpr auto i = decltype(_i)::value;
          if (has_error) {
            return;
          }

          auto r = std::get<i>(ps)(input);
          if (r.is_err()) {
            has_error = true;
            if constexpr (std::is_same_v<typename decltype(r)::error_type,
                                         std::string>) {
              error_msg = r.unwrap_err();
            } else {
              error_msg = fmt::format("failed on parser-{}", i);
            }

            return;
          }

          input              = r.unwrap().second;
          std::get<i>(value) = std::move(std::move(r).unwrap().first);
        });

        if (has_error) {
          return err("combine operator: plus, failed");
        }
        return ok(std::make_pair(flat_tuple(std::move(value)), input));
      });
}

}  // namespace ht::combinators

namespace ht::_parser_combinator_impl {

template<typename T, typename U>
  requires is_parser_v<std::decay_t<T>> && is_parser_v<std::decay_t<U>>
auto operator+(T&& p0, U&& p1) {
  return combinators::combinator_plus(std::forward<T>(p0), std::forward<U>(p1));
}

}  // namespace ht::_parser_combinator_impl

// vim: et sw=2 ts=2
