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
#include <vector>

#include <fmt/format.h>
#include <range/v3/core.hpp>

#include <ht/core/cpp_feature.h>
#include <ht/core/result.hpp>
#include <ht/parser_combinator/impl/input_stream.hpp>
#include <ht/parser_combinator/impl/parser.hpp>
#include "range/v3/range/concepts.hpp"

namespace ht::combinators {

template<template<typename> class S = std::vector>
auto combinator_many(auto&& p, uint32_t at_least = 0)
  requires ranges::sized_range<S<typename HT_TYPE(p)::value_type>>
{
  using element_type = typename HT_TYPE(p)::value_type;
  using value_type   = S<element_type>;
  using result_t =
      result<std::pair<value_type, _parser_combinator_impl::input_stream>,
             std::string>;

  return make_parser(
      [p = HT_FORWARD(p), at_least](const auto& _input) -> result_t {
        value_type res;
        auto input = _input;
        while (true) {
          auto r = p(input);
          if (r.is_err()) {
            break;
          }
          res.emplace_back(std::move(std::move(r).unwrap().first));
          input = r.unwrap().second;
        }
        if (res.size() >= at_least) {
          return ok(std::make_pair(std::move(res), input));
        }
        return err(fmt::format("combinator many, failed: expect {} but {}",
                               at_least, ranges::size(res)));
      });
}
}  // namespace ht::combinators

namespace ht::_parser_combinator_impl {

auto operator*(auto&& p0, uint32_t at_least)
  requires is_parser_v<HT_TYPE(p0)>
{
  return combinators::combinator_many(HT_FORWARD(p0), at_least);
}

}  // namespace ht::_parser_combinator_impl

// vim: et sw=2 ts=2
