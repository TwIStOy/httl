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

TEST_CASE("find after insert", "[avl-tree][container]") {
  ht::AVLTree<std::string, int> tree;
  tree.insert(std::make_pair("foo", 1));
  tree.insert(std::make_pair("bar", 1));
  tree.insert(std::make_pair("foobar", 1));

  REQUIRE(tree.size() == 3);

  std::cout << ht::DebugStringify(tree) << std::endl;
}
