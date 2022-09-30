// Copyright (c) 2020 - present, Hawtian Wang (twistoy.wang@gmail.com)
//

#pragma once  // NOLINT(build/header_guard)

#include <cstdint>
#include <memory>
#include <utility>

namespace ht::__fib_heap_impl {

template<typename KeyType, typename ValueType,
         typename Compare = std::less<KeyType>>
struct fib_heap_entry {
  using key_type        = KeyType;
  using value_type      = ValueType;
  using size_type       = std::size_t;
  using reference       = value_type&;
  using const_reference = const value_type&;
  using key_compare     = Compare;

  fib_heap_entry(key_type key, value_type value)
      : __key(std::move(key)),
        __value(std::move(value)),
        __next(this),
        __prev(this) {
  }

  key_type __key;
  value_type __value;

  fib_heap_entry *__next   = nullptr;
  fib_heap_entry *__prev   = nullptr;
  fib_heap_entry *__parent = nullptr;
  fib_heap_entry *__child  = nullptr;

  uint16_t __degree = 0;
  bool __mark       = false;

  template<typename Allocator>
  fib_heap_entry *deep_copy(Allocator& alloc) {
    fib_heap_entry *new_entry = alloc.allocate(1);
    std::allocator_traits<Allocator>::construct(alloc, new_entry, __key,
                                                __value);

    if (__next != this && __next != nullptr) {
      new_entry->__next         = __next->deep_copy(alloc);
      new_entry->__next->__prev = new_entry;
    }
    if (__child != nullptr && __child != this) {
      new_entry->__child           = __child->deep_copy(alloc);
      new_entry->__child->__parent = new_entry;
    }
  }
};

}  // namespace ht::__fib_heap_impl
