// Copyright (c) 2020 - present, Hawtian Wang (twistoy.wang@gmail.com)
//

#pragma once  // NOLINT(build/header_guard)

#include <cassert>
#include <cstdint>
#include <memory>
#include <utility>
#include <vector>

#include <ht/container/impl/fib_heap_entry.hpp>

namespace ht {

template<
    typename KeyType, typename ValueType, typename Compare = std::less<KeyType>,
    typename Allocator =
        std::allocator<__fib_heap_impl::fib_heap_entry<KeyType, ValueType>>>
class FibonacciHeap {
 public:
  using key_type        = KeyType;
  using value_type      = ValueType;
  using size_type       = std::size_t;
  using difference_type = std::ptrdiff_t;

  using key_compare      = Compare;
  using allocator_type   = Allocator;
  using allocator_traits = std::allocator_traits<allocator_type>;

  using reference       = value_type&;
  using const_reference = const value_type&;
  using pointer         = typename std::allocator_traits<Allocator>::pointer;
  using const_pointer =
      typename std::allocator_traits<Allocator>::const_pointer;

  using entry_type = __fib_heap_impl::fib_heap_entry<KeyType, ValueType>;

  FibonacciHeap() = default;

  allocator_type get_allocator() const noexcept;

  FibonacciHeap(FibonacciHeap&& rhs) noexcept
      : __root(rhs.__root),
        __count(rhs.__count),
        __compare(std::move(rhs.__compare)),
        __allocator(std::move(rhs.__allocator)) {
    rhs.__count = 0;
    rhs.__root  = nullptr;
  }

  static FibonacciHeap Merge(FibonacciHeap x, FibonacciHeap y) {
    FibonacciHeap result;

    result.__root  = result.merge_heap(x.__root, y.__root);
    result.__count = x.size() + y.size();

    x.__root  = nullptr;
    y.__root  = nullptr;
    x.__count = 0;
    y.__count = 0;

    return result;
  }

  FibonacciHeap& operator=(const FibonacciHeap& rhs) {
    if (&rhs == this) {
      return *this;
    }

    destroy_heap(__root);
    __root  = rhs.__root->deep_copy(__allocator);
    __count = rhs.__count;
    return *this;
  }

  ~FibonacciHeap() {
    if (__root) {
      destroy_heap(__root);
      __count = 0;
    }
  }

  // Checks if the container has no elements.
  [[nodiscard]] inline bool empty() const noexcept {
    return __root == nullptr;
  }

  [[nodiscard]] inline size_type size() const noexcept {
    return __count;
  }

  entry_type *insert(key_type key, value_type value) {
    entry_type *entry = __allocator.allocate(1);
    allocator_traits::construct(__allocator, entry, std::move(key),
                                std::move(value));
    __root = merge_heap(entry, __root);
    __count++;
    return entry;
  }

  inline const auto& top() const {
    return __root->__value;
  }

  inline const auto& top_key() const {
    return __root->__key;
  }

  void decrease_key(entry_type *entry, key_type new_key) {
    assert(__compare(new_key, entry->__key));
    entry->__key = new_key;
    if (entry->__parent != nullptr &&
        __compare(entry->__key, entry->__parent->__key)) {
      cut_node(entry);
    }
    if (__compare(entry->__key, __root->__key)) {
      __root = entry;
    }
  }

  // remove the top element
  void pop() noexcept {
    auto entry = pop_impl();
    delete_(entry);
  }

 private:
  void delete_(entry_type *ptr) {  // {{{
    std::allocator_traits<Allocator>::destroy(__allocator, ptr);
    __allocator.deallocate(ptr, 1);
  }  // }}}

  void destroy_heap(entry_type *root) {  // {{{
    if (root == nullptr) {
      return;
    }

    auto iter = root;
    do {
      auto next = iter->__next;
      destroy_heap(iter->__child);
      delete_(iter);
      iter = next;
    } while (iter != root);
  }  // }}}

  entry_type *merge_heap(entry_type *x, entry_type *y) {  // {{{
    if (x == nullptr && y == nullptr) {
      return nullptr;
    }
    if (x != nullptr && y == nullptr) {
      return x;
    }
    if (x == nullptr && y != nullptr) {
      return y;
    }

    auto cache        = x->__next;
    x->__next         = y->__next;
    x->__next->__prev = x;
    y->__next         = cache;
    y->__next->__prev = y;

    return __compare(x->__key, y->__key) ? x : y;
  }  // }}}

  entry_type *pop_impl() noexcept {  // {{{
    assert(!empty());
    __count--;

    entry_type *to_pop = __root;

    // remove this element from root link
    if (to_pop->__next == to_pop) {
      __root = nullptr;
    } else {
      to_pop->__prev->__next = to_pop->__next;
      to_pop->__next->__prev = to_pop->__prev;

      __root = to_pop->__next;
    }

    // clear the parent fields of all of the min element's children
    if (to_pop->__child != nullptr) {
      entry_type *iter = to_pop->__child;
      do {
        iter->__parent = nullptr;
        iter           = iter->__next;
      } while (iter != to_pop->__child);
    }

    // splice the children of the root element into the top list
    __root = merge_heap(__root, to_pop->__child);

    if (__root == nullptr) {
      return to_pop;
    }

    // root list to traverse
    std::vector<entry_type *> to_visit;
    for (entry_type *iter = __root; to_visit.empty() || to_visit[0] != iter;
         iter             = iter->__next) {
      to_visit.push_back(iter);
    }

    std::vector<entry_type *> tree_table;
    for (entry_type *curr : to_visit) {
      while (true) {
        while (curr->__degree >= tree_table.size()) {
          tree_table.push_back(nullptr);
        }

        if (tree_table[curr->__degree] == nullptr) {
          // first element in this degree
          tree_table[curr->__degree] = curr;
          break;
        }

        entry_type *rhs = tree_table[curr->__degree];

        // clear this slot
        tree_table[curr->__degree] = nullptr;

        entry_type *less_element =
            __compare(rhs->__key, curr->__key) ? rhs : curr;
        std::size_t xor_sum = reinterpret_cast<std::size_t>(rhs) ^
                              reinterpret_cast<std::size_t>(curr);
        auto greater_element = reinterpret_cast<entry_type *>(
            xor_sum ^ reinterpret_cast<std::size_t>(less_element));

        // break greater one out of the root list, then merge it into
        // less one's child list
        greater_element = remove_from_link(greater_element);
        less_element->__child =
            merge_heap(less_element->__child, greater_element);
        greater_element->__parent = less_element;
        greater_element->__mark   = false;

        less_element->__degree++;

        curr = less_element;
      }

      // update global min element
      if (__compare(curr->__key, __root->__key)) {
        __root = curr;
      }
    }
    return to_pop;
  }  // }}}

  static entry_type *remove_from_link(entry_type *entry) {  // {{{
    entry->__next->__prev = entry->__prev;
    entry->__prev->__next = entry->__next;
    entry->__next         = entry;
    entry->__prev         = entry;
    return entry;
  }  // }}}

  void cut_node(entry_type *entry) {  // {{{
    entry->__mark = false;

    if (entry->__parent == nullptr) {
      return;
    }

    if (entry->__next != entry) {
      entry->__next->__prev = entry->__prev();
      entry->__prev->__next = entry->__next();
    }

    if (entry->__parent->__child == entry) {
      if (entry->__next != entry) {
        entry->__parent->__child = entry->__next;
      } else {
        entry->__parent->__child = nullptr;
      }
    }
    entry->__parent->__degree--;

    entry->__prev = entry;
    entry->__next = entry;

    __root = merge_heap(__root, entry);

    if (entry->__parent->__mark) {
      cut_node(entry->__parent);
    } else {
      entry->__parent->__mark = true;
    }

    entry->__parent = nullptr;
  }  // }}}

 private:
  entry_type *__root = nullptr;  // min entry
  uint32_t __count   = 0;
  allocator_type __allocator;
  key_compare __compare;
};

}  // namespace ht

// vim: fdm=marker
