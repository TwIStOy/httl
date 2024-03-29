// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include <iterator>

#include <ht/container/impl/avl_tree_base.hpp>
#include <ht/strings/stringify.hpp>

namespace ht::__avl_impl {

template<typename _Tp>
struct _AVL_Tree_Node {
  __avl_tree_node _base_node;
  _Tp *_value;
};

template<typename _Tp>
struct _AVL_Tree_Iterator {
  using value_type = _Tp;
  using reference  = _Tp&;
  using pointer    = _Tp *;

  using iterator_category = std::bidirectional_iterator_tag;
  using difference_type   = std::ptrdiff_t;

  using _node_type = _AVL_Tree_Node<_Tp> *;
  using _Self      = _AVL_Tree_Iterator<_Tp>;

  _AVL_Tree_Iterator() noexcept : _node{nullptr} {
  }

  explicit _AVL_Tree_Iterator(_node_type _x) noexcept : _node(_x) {
  }

  explicit _AVL_Tree_Iterator(__avl_tree_node *_x) noexcept
      : _node(_x ? reinterpret_cast<_node_type>(_x) : nullptr) {
  }

  reference operator*() const noexcept {
    return *_node->_value;
  }

  pointer operator->() const noexcept {
    return _node->_value;
  }

  _Self& operator++() noexcept {
    _node = reinterpret_cast<_node_type>(_node->_base_node.next_node());
    return *this;
  }

  _Self operator++(int) noexcept {
    _Self __tmp = *this;
    operator++();
    return __tmp;
  }

  _Self& operator--() noexcept {
    _node = reinterpret_cast<_node_type>(_node->_base_node.previous_node());
    return *this;
  }

  _Self operator--(int) noexcept {
    _Self __tmp = *this;
    operator--();
    return __tmp;
  }

  bool operator==(const _Self& x) const noexcept {
    return _node == x._node;
  }

  bool operator!=(const _Self& x) const noexcept {
    return _node != x._node;
  }

  friend std::string tag_invoke(ht::tag_t<ht::debug_stringify>,
                                const _AVL_Tree_Iterator& v, uint16_t,
                                int16_t) {
    if (v._node == nullptr) {
      return "AVLTree-Iterator(null)";
    } else {
      std::ostringstream oss;
      oss << "AVLTree-Iterator(key = " << v._node->_value->first
          << ", value = " << v._node->_value->second << ")";
      return oss.str();
    }
  }

  _node_type _node;
};

template<typename _Tp>
struct _AVL_Tree_Const_Iterator {
  using value_type = _Tp;
  using reference  = _Tp&;
  using pointer    = _Tp *;

  using iterator = _AVL_Tree_Iterator<_Tp>;

  using iterator_category = std::bidirectional_iterator_tag;
  using difference_type   = std::ptrdiff_t;

  using _node_type = _AVL_Tree_Node<_Tp> *;
  using _Self      = _AVL_Tree_Const_Iterator<_Tp>;

  _AVL_Tree_Const_Iterator() noexcept : _node{nullptr} {
  }

  explicit _AVL_Tree_Const_Iterator(_node_type x) noexcept : _node{x} {
  }

  explicit _AVL_Tree_Const_Iterator(__avl_tree_node *_x) noexcept
      : _node(reinterpret_cast<_node_type>(_x)) {
  }

  _AVL_Tree_Const_Iterator(const iterator& it) noexcept : _node{it._node} {
  }

  reference operator*() const noexcept {
    return _node->_value;
  }

  pointer operator->() const noexcept {
    return &_node->_value;
  }

  _Self& operator++() noexcept {
    auto next = _node->_base_node.next_node();
    if (next) {
      _node = reinterpret_cast<_node_type>(next);
    } else {
      _node = nullptr;
    }
    return *this;
  }

  _Self operator++(int) noexcept {
    _Self __tmp = *this;
    operator++();
    return __tmp;
  }

  _Self& operator--() noexcept {
    auto next = _node->_base_node.previous_node();
    if (next) {
      _node = reinterpret_cast<_node_type>(next);
    } else {
      _node = nullptr;
    }
    return *this;
  }

  _Self operator--(int) noexcept {
    _Self __tmp = *this;
    operator--();
    return __tmp;
  }

  bool operator==(const _Self& x) const noexcept {
    return _node == x._node;
  }

  bool operator!=(const _Self& x) const noexcept {
    return _node != x._node;
  }

  friend std::string tag_invoke(ht::tag_t<ht::debug_stringify>,
                                const _AVL_Tree_Const_Iterator& v, uint16_t,
                                int16_t) {
    if (v._node == nullptr) {
      return "AVLTree-Const-Iterator(null)";
    } else {
      std::ostringstream oss;
      oss << "AVLTree-Const-Iterator(key = " << v._node->_value->first
          << ", value = " << v._node->_value->second << ")";
      return oss.str();
    }
  }

  _node_type _node;
};

}  // namespace ht::__avl_impl
