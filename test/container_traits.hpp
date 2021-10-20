// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include "ht/container/avl_tree.hpp"

namespace __ht_test {

struct container_traits_base {
  static constexpr bool is_container       = false;
  static constexpr bool is_adaptor         = false;
  static constexpr bool is_reversible      = false;
  static constexpr bool is_allocator_aware = false;
  static constexpr bool is_associative     = false;
  static constexpr bool is_unordered       = false;
  static constexpr bool is_mapped          = false;

  static constexpr bool has_erase                = false;
  static constexpr bool has_erase_after          = false;
  static constexpr bool has_throwing_erase       = false;
  static constexpr bool has_insert               = false;
  static constexpr bool has_insert_after         = false;
  static constexpr bool has_emplace              = false;
  static constexpr bool has_push_pop             = false;
  static constexpr bool has_size_type_constructo = false;
};

template<typename _Tp>
struct container_traits;

template<typename _Tp1, typename _Tp2, typename Tp3, typename Tp4>
struct container_traits<ht::AVLTree<_Tp1, _Tp2, Tp3, Tp4>>
    : public container_traits_base {
  static constexpr bool is_container       = true;
  static constexpr bool is_reversible      = true;
  static constexpr bool is_allocator_aware = true;
  static constexpr bool is_associative     = true;
  static constexpr bool is_mapped          = true;

  static constexpr bool has_erase   = true;
  static constexpr bool has_insert  = true;
  static constexpr bool has_emplace = true;
};

}  // namespace __ht_test

// vim: et sw=2 ts=2
