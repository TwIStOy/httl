// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include <cstdint>
#include <tuple>
#include <utility>

namespace ht {

template<typename T, typename U>
struct select_tuple_elemenmts;

template<typename T, std::size_t... Is>
  requires((Is <= std::tuple_size_v<T>) && ...)
struct select_tuple_elemenmts<T, std::index_sequence<Is...>> {
  using type = std::tuple<std::tuple_element_t<Is, T>...>;
};

template<typename T, typename U>
using select_tuple_elemenmts_t = typename select_tuple_elemenmts<T, U>::type;

}  // namespace ht

// vim: et sw=2 ts=2
