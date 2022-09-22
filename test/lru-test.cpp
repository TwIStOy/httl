// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#include <algorithm>
#include <string>
#include <utility>

#include "catch2/catch_all.hpp"
#include "ht/container/lru_cache.hpp"

using ht::lru_cache;

#define LRU_CASE(name) TEST_CASE(name, "[container][lru]")

LRU_CASE("default construct") {
  lru_cache<std::string, std::string> cache;

  REQUIRE(cache.size() == 0);
  REQUIRE(cache.max_size() == 8);
}

LRU_CASE("contains") {
  lru_cache<uint32_t, std::string> cache;

  REQUIRE_FALSE(cache.contains(1));
}

LRU_CASE("insert one") {
  lru_cache<uint32_t, std::string> cache;

  auto it = cache.insert(std::make_pair(1, "1"));

  REQUIRE(it->first == 1);
  REQUIRE(it->second == "1");
  REQUIRE(it == cache.begin());
  REQUIRE(cache.contains(1));
}

LRU_CASE("emplace one") {
  lru_cache<uint32_t, std::string> cache;

  auto it = cache.emplace(1, "1");

  REQUIRE(it->first == 1);
  REQUIRE(it->second == "1");
  REQUIRE(it == cache.begin());
  REQUIRE(cache.contains(1));
}

LRU_CASE("multiple insert") {
  lru_cache<uint32_t, std::string> cache;

  for (uint32_t i = 0; i < 200; i++) {
    auto it = cache.insert(std::make_pair(i, std::to_string(i)));
    REQUIRE(it->first == i);
    REQUIRE(it->second == std::to_string(i));
    REQUIRE(it == cache.begin());

    for (uint32_t j = 0; j < i; j++) {
      auto exists = i - j + 1;
      REQUIRE(cache.contains(j) == (exists <= 8));
    }

    auto expect_size = std::min<std::size_t>(i + 1, 8);
    REQUIRE(cache.size() == expect_size);
  }
}

LRU_CASE("value non-copyable") {
  struct non_copyable {
    non_copyable()                     = default;
    non_copyable(const non_copyable &) = delete;
    non_copyable(non_copyable &&)      = default;

    non_copyable &operator=(const non_copyable &) = delete;
    non_copyable &operator=(non_copyable &&)      = default;
  };

  lru_cache<uint32_t, non_copyable> cache;
  non_copyable v;
  cache.insert(std::make_pair(1, std::move(v)));
  cache.insert(std::make_pair(2, non_copyable{}));

  REQUIRE(cache.size());
}
