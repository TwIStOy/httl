// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include <cstddef>
#include <utility>

namespace ht {

template<std::size_t I, typename T>
struct index_sequence_plus;

template<std::size_t I, std::size_t... Is>
struct index_sequence_plus<I, std::index_sequence<Is...>> {
  using type = std::index_sequence<(Is + I)...>;
};

template<std::size_t I, typename T>
using index_sequence_plus_t = typename index_sequence_plus<I, T>::type;

}  // namespace ht

// vim: et sw=2 ts=2
