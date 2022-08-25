// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include <cstdint>
#include <type_traits>
#include <utility>

namespace ht::_algorithm_impl {

template<typename Func, std::size_t... Is>
void for_(Func &&func, std::index_sequence<Is...>) {
  (func(std::integral_constant<std::size_t, Is>{}), ...);
}

}  // namespace ht::_algorithm_impl

namespace ht {

template<std::size_t N, typename Func>
void for_(Func &&func) {
  _algorithm_impl::for_(std::forward<Func>(func),
                        std::make_index_sequence<N>());
}

}  // namespace ht

// vim: et sw=2 ts=2
