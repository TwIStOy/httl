// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#include "ht/container/impl/avl_tree_base.hpp"

#include <algorithm>

namespace ht::__avl_impl {

static inline int __left_height(__avl_tree_node *node) {
  return node->__left ? node->__left->__height : 0;
}

static inline int __right_height(__avl_tree_node *node) {
  return node->__right ? node->__right->__height : 0;
}

__avl_tree_node::__avl_tree_node(__avl_tree_node *parent, int height,
                                 void *data)
    : __parent(parent), __height(height), __data(data) {
}

__avl_tree_node *__avl_tree_node::left_most_node() {
  if (__left == nullptr) {
    return this;
  }
  return __left->left_most_node();
}

__avl_tree_node *__avl_tree_node::right_most_node() {
  if (__right == nullptr) {
    return this;
  }
  return __right->right_most_node();
}

__avl_tree_node *__avl_tree_node::next_node() {
  if (__right) {
    return __right->left_most_node();
  }

  auto node = this;
  while (true) {
    auto last = node;
    node      = node->__parent;
    if (node == nullptr)
      break;
    if (node->__left == last)
      break;
  }

  return node;
}

__avl_tree_node *__avl_tree_node::previous_node() {
  if (__left) {
    return __left->right_most_node();
  }

  auto node = this;
  while (true) {
    auto last = node;
    node      = node->__parent;
    if (node == nullptr)
      break;
    if (node->__right == last)
      break;
  }

  return node;
}

int __avl_tree_node::update_height() {
  int h_left  = __left ? __left->__height : 0;
  int h_right = __right ? __right->__height : 0;
  __height    = std::max(h_left, h_right) + 1;
  return __height;
}

__avl_tree_node *__avl_tree_base::first_node() {
  auto node = __root;
  if (node == nullptr) {
    return nullptr;
  }

  while (node->__left) {
    node = node->__left;
  }
  return node;
}

void __avl_tree_base::replace_child(__avl_tree_node *old_node,
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

__avl_tree_node *__avl_tree_base::node_rotate_left(__avl_tree_node *node) {
  auto right    = node->__right;
  auto parent   = node->__parent;
  node->__right = right->__left;
  if (right->__left) {
    right->__left->__parent = node;
  }
  right->__left   = node;
  right->__parent = parent;
  replace_child(node, right, parent);
  node->__parent = right;
  return right;
}

__avl_tree_node *__avl_tree_base::node_rotate_right(__avl_tree_node *node) {
  auto left    = node->__left;
  auto parent  = node->__parent;
  node->__left = left->__right;
  if (left->__right) {
    left->__right->__parent = node;
  }
  left->__right  = node;
  left->__parent = parent;
  replace_child(node, left, parent);
  node->__parent = left;
  return left;
}

void __avl_tree_base::replace_node(__avl_tree_node *old_node,
                                   __avl_tree_node *new_node) {
  auto parent = old_node->__parent;
  replace_child(old_node, new_node, parent);
  if (old_node->__left)
    old_node->__left->__parent = new_node;
  if (old_node->__right)
    old_node->__right->__parent = new_node;
  new_node->__left   = old_node->__left;
  new_node->__right  = old_node->__right;
  new_node->__parent = old_node->__parent;
  new_node->__height = old_node->__height;
}

__avl_tree_node *__avl_tree_base::fix_l(__avl_tree_node *node) {
  auto right = node->__right;
  int h0     = __left_height(right);
  int h1     = __right_height(right);
  if (h0 > h1) {
    right = node_rotate_right(right);
    right->__right->update_height();
    right->update_height();
  }
  node = node_rotate_left(node);
  node->__left->update_height();
  node->update_height();
  return node;
}

__avl_tree_node *__avl_tree_base::fix_r(__avl_tree_node *node) {
  auto left = node->__left;
  int h0    = __left_height(left);
  int h1    = __right_height(left);
  if (h0 < h1) {
    left = node_rotate_left(left);
    left->__left->update_height();
    left->update_height();
  }
  node = node_rotate_right(node);
  node->__right->update_height();
  node->update_height();
  return node;
}

void __avl_tree_base::rebalance(__avl_tree_node *node) {
  while (node) {
    int h0     = __left_height(node);
    int h1     = __right_height(node);
    int diff   = h0 - h1;
    int height = std::max(h0, h1) + 1;
    if (node->__height != height) {
      node->__height = height;
    } else if (diff >= -1 && diff <= 1) {
      break;
    }
    if (diff < -1) {
      node = fix_l(node);
    } else if (diff > 2) {
      node = fix_r(node);
    }
    node = node->__parent;
  }
}

void __avl_tree_base::rebalance_new_node(__avl_tree_node *node) {
  node->__height = 1;
  for (node = node->__parent; node; node = node->__parent) {
    int h0     = __left_height(node);
    int h1     = __right_height(node);
    int diff   = h0 - h1;
    int height = std::max(h0, h1) + 1;
    if (node->__height == height)
      break;
    node->__height = height;
    if (diff < -1) {
      node = fix_l(node);
    } else if (diff > 1) {
      node = fix_r(node);
    }
  }
}

bool __avl_tree_base::check_node(__avl_tree_node *node) {
  if (node == nullptr)
    return true;

  int h0     = __left_height(node);
  int h1     = __right_height(node);
  int height = std::max(h0, h1) + 1;
  int diff   = h0 - h1;
  return diff >= -1 && diff <= 1 && height == node->__height &&
         check_node(node->__left) && check_node(node->__right);
}

void __avl_tree_base::erase_node(__avl_tree_node *node) {
  __avl_tree_node *parent = nullptr;

  if (node->__left && node->__right) {
    auto old = node;
    node = node->__right->left_most_node();
    auto child  = node->__right;
    parent = node->__parent;
    if (child) {
      child->__parent = parent;
    }
    replace_child(node, child, parent);
    if (node->__parent == old)
      parent = node;
    node->__left   = old->__left;
    node->__right  = old->__right;
    node->__parent = old->__parent;
    node->__height = old->__height;
    replace_child(old, node, old->__parent);
    old->__left->__parent = node;
    if (old->__right) {
      old->__right->__parent = node;
    }
  } else {
    __avl_tree_node *child;
    if (node->__left == nullptr) {
      child = node->__right;
    } else {
      child = node->__left;
    }
    parent = node->__parent;
    replace_child(node, child, parent);
    if (child) {
      child->__parent = parent;
    }
  }
  if (parent) {
    rebalance(parent);
  }
}

}  // namespace ht::__avl_impl

// vim: et sw=2 ts=2
