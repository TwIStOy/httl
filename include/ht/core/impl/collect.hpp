// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include <concepts>
#include <ranges>

namespace ht::_algorithm_impl {

template<typename C>
struct collect_helper {};

template<typename C, std::ranges::range R>
  requires std::convertible_to<std::ranges::range_value_t<R>,
                               typename C::value_type> &&
           std::ranges::sized_range<R>
C operator|(R&& r, collect_helper<C>) {
  return C{std::ranges::begin(r), std::ranges::end(r)};
}

}  // namespace ht::_algorithm_impl

namespace ht {

template<std::ranges::sized_range Container>
  requires(!std::ranges::view<Container>)
auto collect() {
  return _algorithm_impl::collect_helper<Container>{};
}
}  // namespace ht

// vim: et sw=2 ts=2
