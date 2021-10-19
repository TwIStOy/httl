// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#include <iostream>
#include <map>
#include <string>

#include "catch.hpp"
#include "ht/container/avl_tree.hpp"
#include "ht/macro/stealer.h"

TEST_CASE("find after insert", "[avl-tree][container]") {
  ht::AVLTree<std::string, int> tree;
  tree.insert(std::make_pair("foo", 1));
  tree.insert(std::make_pair("bar", 2));
  tree.insert(std::make_pair("foobar", 3));

  REQUIRE(tree.size() == 3);

  std::cout << ht::DebugStringify(tree) << std::endl;

  {
    auto it = tree.find("foo");
    std::cout << ht::DebugStringify(it) << std::endl;
    REQUIRE(it != tree.end());
    REQUIRE(it->first == "foo");
    REQUIRE(it->second == 1);
  }
  {
    auto it = tree.find("bar");
    std::cout << ht::DebugStringify(it) << std::endl;
    REQUIRE(it != tree.end());
    REQUIRE(it->first == "bar");
    REQUIRE(it->second == 2);
  }
  {
    auto it = tree.find("foobar");
    std::cout << ht::DebugStringify(it) << std::endl;
    REQUIRE(it != tree.end());
    REQUIRE(it->first == "foobar");
    REQUIRE(it->second == 3);
  }
  {
    auto it = tree.find("foobarfoo");
    std::cout << ht::DebugStringify(it) << std::endl;
    REQUIRE(it == tree.end());
  }
}

TEST_CASE("erase after insert", "[avl-tree][container]") {
  ht::AVLTree<std::string, int> tree;
  tree.insert(std::make_pair("foo", 1));
  tree.insert(std::make_pair("bar", 2));
  tree.insert(std::make_pair("foobar", 3));

  REQUIRE(tree.size() == 3);

  std::cout << ht::DebugStringify(tree) << std::endl;

  {
    auto cnt = tree.erase("foo");
    REQUIRE(cnt == 1);
  }

  REQUIRE(tree.size() == 2);
}

TEST_CASE("benchmark", "[avl-tree][container]") {
  std::random_device rd;
  std::mt19937 gen(rd());

  ht::AVLTree<uint32_t, uint32_t> htmp;
  std::map<uint32_t, uint32_t> stdmap;
  std::vector<uint32_t> keys(1000);
  for (auto i = 0u; i < 1000; ++i) {
    keys[i] = gen();
  }

  {
    std::vector<int64_t> cost;
    for (auto i = 0u; i < 1000; ++i) {
      auto st = std::chrono::high_resolution_clock::now();
      htmp.insert(std::make_pair(keys[i], 1));
      auto ed = std::chrono::high_resolution_clock::now();
      cost.push_back((ed - st).count());
    }
    std::sort(std::begin(cost), std::end(cost));
    auto min = cost.front();
    auto max = cost.back();
    auto p95 = cost[950];
    auto p99 = cost[990];
    std::cout << "htmap, min: " << min << ", "
              << "max: " << max << ", "
              << "p95: " << p95 << ", "
              << "p99: " << p99 << std::endl;
  }

  {
    std::vector<int64_t> cost;
    for (auto i = 0u; i < 1000; ++i) {
      auto st = std::chrono::high_resolution_clock::now();
      stdmap.insert(std::make_pair(keys[i], 1));
      auto ed = std::chrono::high_resolution_clock::now();
      cost.push_back((ed - st).count());
    }

    std::sort(std::begin(cost), std::end(cost));
    auto min = cost.front();
    auto max = cost.back();
    auto p95 = cost[950];
    auto p99 = cost[990];
    std::cout << "stdmap, min: " << min << ", "
              << "max: " << max << ", "
              << "p95: " << p95 << ", "
              << "p99: " << p99 << std::endl;
  }
}
