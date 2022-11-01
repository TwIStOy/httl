// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include <cstdint>
#include <functional>
#include <list>
#include <optional>
#include <unordered_map>
#include <utility>

#include <ht/functional/hash.hpp>

namespace ht {

template<typename KeyType, typename ValueType, typename Hash = Hash<KeyType>,
         typename KeyEqual = std::equal_to<>,
         typename Allocator =
             std::allocator<std::pair<const KeyType, ValueType>>,
         typename HashContainer = std::unordered_map<
             KeyType,
             typename std::list<std::pair<const KeyType, ValueType>>::iterator,
             Hash, KeyEqual>>
class lru_cache {
 public:
  using key_type        = KeyType;
  using mapped_type     = ValueType;
  using value_type      = std::pair<const key_type, mapped_type>;
  using size_type       = std::size_t;
  using difference_type = std::ptrdiff_t;
  using hasher          = Hash;
  using key_equal       = KeyEqual;
  using allocator_type  = Allocator;
  using reference       = value_type&;
  using const_reference = const value_type&;
  using pointer         = typename std::allocator_traits<Allocator>::pointer;
  using const_pointer =
      typename std::allocator_traits<Allocator>::const_pointer;
  using storage_type     = std::list<value_type>;
  using iterator         = typename storage_type::iterator;
  using const_iterator   = typename storage_type::const_iterator;
  using reverse_iterator = typename storage_type::reverse_iterator;

  explicit lru_cache(std::size_t max_size = 8) : max_size_(max_size) {
  }

  /**
   * Check if a key-value pair exists in cache
   */
  [[nodiscard]] inline bool contains(const key_type& key) const {
    return index_.contains(key);
  }

  inline reference operator[](const key_type& key) {
    if (auto it = index_.find(key); it != index_.end()) {
      return it->second->second;
    } else {
      clean();
      values_.push_front(std::make_pair(key, value_type{}));
      auto vit = values_.begin();
      index_.insert(std::make_pair(vit->first, vit));

      return vit->second;
    }
  }

  std::optional<reference> get(const key_type& key) {
    if (auto it = index_.find(key); it != index_.end()) {
      visit(it->second);
      return it->second->second;
    }
    return std::nullopt;
  }

  std::optional<const_reference> get(const key_type& key) const {
    if (auto it = index_.find(key); it != index_.end()) {
      visit(it->second);
      return it->second->second;
    }
    return std::nullopt;
  }

  iterator find(const key_type& key) {
    if (auto it = index_.find(key); it != index_.end()) {
      return it->second;
    }
    return values_.end();
  }

  const_iterator find(const key_type& key) const {
    if (auto it = index_.find(key); it != index_.end()) {
      return it->second;
    }
    return values_.end();
  }

  inline iterator begin() noexcept(noexcept(values_.begin())) {
    return values_.begin();
  }
  inline const_iterator begin() const noexcept(noexcept(values_.begin())) {
    return values_.begin();
  }

  inline iterator end() noexcept(noexcept(values_.end())) {
    return values_.end();
  }
  inline const_iterator end() const noexcept(noexcept(values_.end())) {
    return values_.end();
  }

  template<typename... Args>
  iterator emplace(Args&&...args) {
    return insert(value_type{std::forward<Args>(args)...});
  }

  iterator insert(value_type value) {
    if (auto it = index_.find(value.first); it != index_.end()) {
      visit(it->second);
      it->second->second = std::move(value.second);
      return it->second;
    } else {
      clean();
      values_.push_front(std::move(value));
      auto vit = values_.begin();
      index_.insert(std::make_pair(vit->first, vit));
      return vit;
    }
  }

  size_type size() const noexcept(noexcept(values_.size())) {
    return values_.size();
  }

  size_type max_size() const noexcept {
    return max_size_;
  }

 private:
  inline void clean() {
    while (values_.size() >= max_size_) {
      erase_entry(values_.rbegin());
    }
  }

  inline void erase_entry(iterator it) {
    index_.erase(it->first);
    values_.erase(it);
  }

  inline void erase_entry(reverse_iterator it) {
    erase_entry(std::next(it).base());
  }

  inline void erase_entry(const KeyType& key) {
    if (auto it = index_.find(key); it != index_.end()) {
      erase_entry(it->second);
    }
  }

  inline void visit(iterator it) const {
    if (it != values_.begin()) {
      values_.splice(values_.begin(), values_, it);
    }
  }

 private:
  size_type max_size_;

  mutable std::list<value_type> values_;
  HashContainer index_;
};

}  // namespace ht
