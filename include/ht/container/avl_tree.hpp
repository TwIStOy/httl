// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include <cassert>
#include <functional>

#include "ht/container/impl/avl_tree_base.hpp"
#include "ht/container/impl/avl_tree_iterator.hpp"
#include "ht/strings/display.hpp"

namespace ht {

template<typename Key, typename T, typename Compare = std::less<Key>,
         typename Allocator = std::allocator<std::pair<const Key, T>>>
class AVLTree : public IDebugDisplay {
 public:
  using key_type        = Key;
  using mapped_type     = T;
  using value_type      = std::pair<const Key, T>;
  using size_type       = std::size_t;
  using difference_type = std::ptrdiff_t;
  using key_compare     = Compare;
  using allocator_type  = Allocator;
  using reference       = value_type &;
  using const_reference = const value_type &;
  using pointer         = typename std::allocator_traits<Allocator>::pointer;
  using const_pointer =
      typename std::allocator_traits<Allocator>::const_pointer;

  using iterator         = __avl_impl::_AVL_Tree_Iterator<value_type>;
  using const_iterator   = __avl_impl::_AVL_Tree_Const_Iterator<value_type>;
  using reverse_iterator = std::reverse_iterator<iterator>;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;

  using node_type = __avl_impl::_AVL_Tree_Node<value_type>;

  AVLTree() = default;

  ~AVLTree() {
    clear();
  }

  template<typename ForwardIterator,
           typename = std::enable_if_t<std::is_same_v<
               typename ForwardIterator::value_type, value_type>>>
  AVLTree(ForwardIterator begin, ForwardIterator end);

  iterator find(const key_type &key) {
    return iterator(find_node(key));
  }

  std::pair<iterator, bool> insert(value_type &&data) {
    auto position                       = &__base.__root;
    __avl_impl::__avl_tree_node *parent = nullptr;
    while (*position) {
      parent = *position;
      if (data.first <
          reinterpret_cast<node_type *>(parent->__data)->_value->first) {
        position = &parent->__left;
      } else if (reinterpret_cast<node_type *>(parent->__data)->_value->first <
                 data.first) {
        position = &parent->__right;
      } else {
        return {iterator(parent), false};
      }
    }

    *position      = new __avl_impl::__avl_tree_node(parent, 0, nullptr);
    auto data_node = new node_type{*position, new value_type{std::move(data)}};
    (*position)->__data = data_node;

    // rebalance tree
    __base.rebalance_new_node(*position);
    __base.__count++;

    assert(__base.check_node(__base.__root));

    return {iterator(*position), true};
  }

  std::pair<iterator, bool> insert(const value_type &data) {
    return insert(value_type{data});
  }

  template<class P>
  std::pair<iterator, bool> insert(P &&value) {
    return insert(value_type{std::move(value)});
  }

  template<class InputIt>
  void insert(InputIt first, InputIt last) {
    for (auto it = first; it != last; ++it) {
      insert(*it);
    }
  }

  void insert(std::initializer_list<value_type> ilist) {
    for (auto &&v : ilist) {
      insert(std::move(v));
    }
  }

  size_t size() const {
    return __base.__count;
  }

  void clear() {
    destroy_tree(__base.__root);
    __base.__count = 0;
    __base.__root  = nullptr;
  }

  template<class... Args>
  std::pair<iterator, bool> emplace(Args &&...args) {
    return insert(value_type{std::forward<Args>(args)...});
  }

  void erase(iterator pos) {
    if (pos.__node) {
      __base.erase_node(pos.__node->__node);
      delete pos.__node->__node;
      delete pos.__node;
      __base.__count--;
    }
  }

  iterator erase(const_iterator pos);

  void erase(iterator first, iterator last);
  void erase(const_iterator first, const_iterator last);

  size_type erase(const key_type &key) {
    __avl_impl::__avl_tree_node *node = find_node(key);
    if (node) {
      __base.erase_node(node);
      delete reinterpret_cast<node_type *>(node->__data);
      delete node;
      __base.__count--;
    }
    return 0;
  }

  void DebuggingStringify(std::ostream &oss) const {
    oss << "AVLTree " << size() << " nodes: [";
    in_order_traval(__base.__root, [&oss](node_type *node) {
      oss << "(" << node->_value->first << ", " << node->_value->second
          << "), ";
    });
    oss << "]";
  }

  iterator begin() {
    if (__base.__root) {
      return iterator(__base.__root->left_most_node());
    }
    return end();
  }

  iterator end() {
    __avl_impl::__avl_tree_node *ptr = nullptr;
    return iterator(ptr);
  }

 private:
  void destroy_tree(__avl_impl::__avl_tree_node *node) {
    if (node) {
      auto data = reinterpret_cast<node_type *>(node->__data);
      delete data;

      destroy_tree(node->__left);
      destroy_tree(node->__right);
      delete node;
    }
  }

  __avl_impl::__avl_tree_node *find_node(const key_type &key) {
    auto node = __base.__root;
    while (node) {
      auto data = reinterpret_cast<node_type *>(node->__data);
      if (data->_value->first < key) {
        node = node->__right;
      } else if (key < data->_value->first) {
        node = node->__left;
      } else {
        return node;
      }
    }
    return nullptr;
  }

  void in_order_traval(__avl_impl::__avl_tree_node *root,
                       const std::function<void(node_type *node)> &f) const {
    if (root) {
      if (root->__left) {
        in_order_traval(root->__left, f);
      }
      f(reinterpret_cast<node_type *>(root->__data));
      if (root->__right) {
        in_order_traval(root->__right, f);
      }
    }
  }

 private:
  __avl_impl::__avl_tree_base __base;
};

}  // namespace ht

// vim: et sw=2 ts=2
