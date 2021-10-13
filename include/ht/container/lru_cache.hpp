// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include <cstdint>
#include <list>
#include <unordered_map>

namespace ht {

template<typename KeyType, typename ValueType, uint32_t MaxSize = 8>
class LruCache {
 public:
  LruCache() = default;

  /**
   * @brief Put key-value pair into cache. If key already exists, replace it.
   *
   * @param key key to insert into cache
   * @param value value to insert into cache
   */
  void Push(KeyType key, ValueType value);

  /**
   * @brief Check if a key-value pair exists in cache
   *
   * @param key key to check for existence
   * @return true if key exists
   */
  bool Has(KeyType key) const;

  bool Get(KeyType key, ValueType *value) const;

 private:
  using Entry = std::pair<KeyType, ValueType>;

  void EraseEntry(typename std::list<Entry>::iterator it) {
    queue_.erase(it->first);
    list_.erase(it);
  }

  void EraseEntry(KeyType key) {
    typename std::list<Entry>::iterator it;
    auto qit = queue_.find(key);

    if (qit != queue_.end()) {
      it = qit->second;

      queue_.erase(qit);
      list_.erase(it);
    }
  }

 private:
  mutable std::list<Entry> list_;

  std::unordered_map<KeyType, typename std::list<Entry>::iterator> queue_;
};

template<typename KeyType, typename ValueType, uint32_t MaxSize>
void LruCache<KeyType, ValueType, MaxSize>::Push(KeyType key, ValueType value) {
  EraseEntry(key);
  auto it = list_.insert(list_.end(), std::make_pair(key, value));
  if (list_.size() > MaxSize) {
    EraseEntry(list_.begin());
  }

  queue_.insert(std::make_pair(key, it));
}

template<typename KeyType, typename ValueType, uint32_t MaxSize>
bool LruCache<KeyType, ValueType, MaxSize>::Has(KeyType key) const {
  return queue_.find(key) != queue_.end();
}

template<typename KeyType, typename ValueType, uint32_t MaxSize>
bool LruCache<KeyType, ValueType, MaxSize>::Get(KeyType key,
                                                ValueType *value) const {
  auto qit = queue_.find(key);
  if (qit == queue_.end()) {
    return false;
  }

  auto it = qit->second;
  list_.splice(list_.end(), list_, it);

  if (value) {
    *value = qit->second->second;
  }

  return true;
}

}  // namespace ht

// vim: et sw=2 ts=2
