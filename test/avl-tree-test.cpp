// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#include <iostream>
#include <map>
#include <string>

#include "catch2/catch_all.hpp"
#include "container_utils.hpp"
#include "ht/container/avl_tree.hpp"
#include "ht/macro/stealer.h"
#include "ht/strings/stringify.hpp"

TEST_CASE("find after insert", "[avl-tree][container]") {
  ht::AVLTree<std::string, int> tree = {};
  tree.insert(std::make_pair("foo", 1));
  tree.insert(std::make_pair("bar", 2));
  tree.insert(std::make_pair("foobar", 3));

  REQUIRE(tree.size() == 3);

  std::cout << ht::debug_stringify(tree) << std::endl;

  {
    auto it = tree.find("foo");
    std::cout << ht::debug_stringify(it) << std::endl;
    REQUIRE(it != tree.end());
    REQUIRE(it->first == "foo");
    REQUIRE(it->second == 1);
  }
  {
    auto it = tree.find("bar");
    std::cout << ht::debug_stringify(it) << std::endl;
    REQUIRE(it != tree.end());
    REQUIRE(it->first == "bar");
    REQUIRE(it->second == 2);
  }
  {
    auto it = tree.find("foobar");
    std::cout << ht::debug_stringify(it) << std::endl;
    REQUIRE(it != tree.end());
    REQUIRE(it->first == "foobar");
    REQUIRE(it->second == 3);
  }
  {
    auto it = tree.find("foobarfoo");
    std::cout << ht::debug_stringify(it) << std::endl;
    REQUIRE(it == tree.end());
  }
}

TEST_CASE("erase after insert", "[avl-tree][container]") {
  ht::AVLTree<std::string, int> tree;
  tree.insert(std::make_pair("foo", 1));
  tree.insert(std::make_pair("bar", 2));
  tree.insert(std::make_pair("foobar", 3));

  REQUIRE(tree.size() == 3);

  std::cout << ht::debug_stringify(tree) << std::endl;

  {
    auto cnt = tree.erase("foo");
    REQUIRE(cnt == 1);
  }

  REQUIRE(tree.size() == 2);
}

static void benchmark_insert(uint32_t count, bool random) {
  static std::random_device rd;
  static std::mt19937 gen(rd());

  std::cout << (random ? "random" : "no random") << std::endl;

  ht::AVLTree<uint32_t, uint32_t> htmp;
  std::map<uint32_t, uint32_t> stdmap;
  std::vector<uint32_t> keys(count);
  for (auto i = 0u; i < count; ++i) {
    if (random) {
      keys[i] = gen();
    } else {
      keys[i] = i;
    }
  }

  auto get_sum = [](const auto &x) {
    int64_t v = 0;
    for (const auto &vv : x) {
      v += vv;
    }
    return v;
  };

  {
    std::vector<int64_t> cost;
    for (auto i = 0u; i < count; ++i) {
      auto st = std::chrono::high_resolution_clock::now();
      htmp.insert(std::make_pair(keys[i], keys[i] * 10));
      auto ed = std::chrono::high_resolution_clock::now();
      cost.push_back((ed - st).count());
    }
    std::sort(std::begin(cost), std::end(cost));
    auto min = cost.front();
    auto max = cost.back();
    auto p95 = cost[static_cast<uint64_t>(count * 0.95)];
    auto p99 = cost[static_cast<uint32_t>(count * 0.99)];
    std::cout << "htmap " << htmp.size() << ", min: " << min << ", "
              << "max: " << max << ", "
              << "p95: " << p95 << ", "
              << "p99: " << p99 << ", "
              << "avg: " << (get_sum(cost) / count) << std::endl;
  }

  {
    std::vector<int64_t> cost;
    for (auto i = 0u; i < count; ++i) {
      auto st = std::chrono::high_resolution_clock::now();
      stdmap.insert(std::make_pair(keys[i], keys[i] * 10));
      auto ed = std::chrono::high_resolution_clock::now();
      cost.push_back((ed - st).count());
    }

    std::sort(std::begin(cost), std::end(cost));
    auto min = cost.front();
    auto max = cost.back();
    auto p95 = cost[static_cast<uint32_t>(count * 0.95)];
    auto p99 = cost[static_cast<uint32_t>(count * 0.99)];
    std::cout << "stdmap " << stdmap.size() << ", min: " << min << ", "
              << "max: " << max << ", "
              << "p95: " << p95 << ", "
              << "p99: " << p99 << ", "
              << "avg: " << (get_sum(cost) / count) << std::endl;
  }
}

TEST_CASE("benchmark", "[avl-tree][container][benchmark]") {
  benchmark_insert(1000000, false);
  benchmark_insert(1000000, true);
  /*
   * benchmark_insert(100000000, false);
   * benchmark_insert(100000000, true);
   */
}

template<typename T>
struct alloc {
  typedef T value_type;
  typedef T *pointer;
  typedef const T *const_pointer;
  typedef T &reference;
  typedef const T &const_reference;
  typedef unsigned size_type;
  typedef int difference_type;

  template<typename U>
  struct rebind {
    typedef alloc<U> other;
  };

  alloc() = default;

  template<typename U>
  explicit alloc(const alloc<U> &) {
  }

  pointer allocate(size_type n, const void * = nullptr) {
    return std::allocator<T>().allocate(n);
  }
  void deallocate(pointer p, size_type n) {
    std::allocator<T>().deallocate(p, n);
  }

  [[nodiscard]] size_type max_size() const {
    return -1;
  }

  void construct(pointer p, const T &t) {
    new ((void *)p) T(t);
  }
  void destroy(pointer p) {
    p->~T();
  }

  pointer address(reference x) const noexcept {
    return &x;
  }
  [[nodiscard]] const_pointer address(const_reference x) const noexcept {
    return &x;
  }
};

template<typename T, typename U>
bool operator==(alloc<T>, alloc<U>) {
  return true;
}

template<typename T, typename U>
bool operator!=(alloc<T>, alloc<U>) {
  return false;
}
TEST_CASE("c++03 allocator", "[avl-tree][container][stl]") {
  ht::AVLTree<int, int, std::less<>, alloc<std::pair<const int, int>>> m;
  m[1];
}

TEST_CASE("compile", "[avl-tree][container]") {
  using container = ht::AVLTree<int, int>;

  container value;

  __ht_test::types<container> tmp{};
  __ht_test::populate<container>{value};
  __ht_test::reverse_members<container>{value};
}
