// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include <algorithm>
#include <cstdint>

#include "ht/macro/cpp_feature.h"

namespace ht::__avl_impl {

struct __avl_tree_node {
  __avl_tree_node *__left;
  __avl_tree_node *__right;
  __avl_tree_node *__parent;
  int __height;

  __avl_tree_node *next_node();

  __avl_tree_node *previous_node();

  __avl_tree_node *left_most_node();

  __avl_tree_node *right_most_node();

  int update_height();
};

ALWAYS_INLINE int __avl_tree_node::update_height() {
  int h_left  = __left ? __left->__height : 0;
  int h_right = __right ? __right->__height : 0;
  __height    = std::max(h_left, h_right) + 1;
  return __height;
}

ALWAYS_INLINE __avl_tree_node *__avl_tree_node::left_most_node() {
  auto node = this;
  while (node->__left) {
    node = node->__left;
  }
  return node;
}

ALWAYS_INLINE __avl_tree_node *__avl_tree_node::right_most_node() {
  auto node = this;
  while (node->__right) {
    node = node->__right;
  }
  return node;
}

struct __avl_tree_base {
  // avl root
  __avl_tree_node *__root = nullptr;

  // node count
  std::size_t __count{0};

  /*
   * // node offset in user data structure
   * std::size_t __offset;
   *
   * // size of user data structure
   * std::size_t __size;
   */

  __avl_tree_node *first_node();

  __avl_tree_node *last_node();

  void replace_child(__avl_tree_node *old_node, __avl_tree_node *new_node,
                     __avl_tree_node *parent);

  void replace_node(__avl_tree_node *old_node, __avl_tree_node *new_node);

  __avl_tree_node *node_rotate_left(__avl_tree_node *node);

  __avl_tree_node *node_rotate_right(__avl_tree_node *node);

  __avl_tree_node *fix_l(__avl_tree_node *node);

  __avl_tree_node *fix_r(__avl_tree_node *node);

  void rebalance(__avl_tree_node *node);

  void rebalance_new_node(__avl_tree_node *node);

  void erase_node(__avl_tree_node *node);

  static bool check_node(__avl_tree_node *node);
};

ALWAYS_INLINE void __avl_tree_base::replace_child(__avl_tree_node *old_node,
                                                  __avl_tree_node *new_node,
                                                  __avl_tree_node *parent) {
  if (parent) {
    if (parent->__left == old_node) {
      parent->__left = new_node;
    }
    if (parent->__right == old_node) {
      parent->__right = new_node;
    }
  } else {
    __root = new_node;
  }
}

}  // namespace ht::__avl_impl

// vim: et sw=2 ts=2
