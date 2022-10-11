// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include <ht/meta/impl/index_sequence_plus.hpp>
#include <ht/meta/impl/select_tuple_element.hpp>

#include <cstdint>
#include <tuple>
#include <utility>

namespace ht {

template<std::size_t I, typename... Ts>
  requires(I <= sizeof...(Ts))
struct tuple_slice {
  using first =
      select_tuple_elemenmts_t<std::tuple<Ts...>, std::make_index_sequence<I>>;

  using second = select_tuple_elemenmts_t<
      std::tuple<Ts...>,
      index_sequence_plus<I, std::make_index_sequence<sizeof...(Ts) - I>>>;
};

}  // namespace ht

// vim: et sw=2 ts=2
