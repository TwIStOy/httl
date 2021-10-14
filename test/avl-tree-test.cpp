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


