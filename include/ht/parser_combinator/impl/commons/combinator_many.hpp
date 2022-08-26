// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include <concepts>
#include <ranges>
#include <string>
#include <tuple>
#include <type_traits>
#include <utility>
#include <vector>

#include "fmt/format.h"
#include "ht/core/algorithm.hpp"
#include "ht/core/result.hpp"
#include "ht/core/type_traits.hpp"
#include "ht/parser_combinator/impl/input_stream.hpp"
#include "ht/parser_combinator/impl/parser.hpp"

namespace ht::combinators {

template<typename P, template<typename> class S = std::vector>
auto combinator_many(P &&p, uint32_t at_least = 0) {
  using element_type = typename std::decay_t<P>::value_type;
  using value_type   = S<element_type>;
  using result_t =
      result<std::pair<value_type, _parser_combinator_impl::input_stream>,
             std::string>;

  return make_parser(
      [p = std::forward<P>(p), at_least](const auto &_input) -> result_t {
        value_type res;
        _parser_combinator_impl::input_stream input = _input;
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
                               at_least, std::ranges::size(res)));
      });
}
}  // namespace ht::combinators

namespace ht::_parser_combinator_impl {

template<typename T>
  requires is_parser_v<std::decay_t<T>>
auto operator*(T &&p0, uint32_t at_least) {
  return combinators::combinator_many(std::forward<T>(p0), at_least);
}

}  // namespace ht::_parser_combinator_impl

// vim: et sw=2 ts=2
