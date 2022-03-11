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
#include "ht/container/ac_automaton.hpp"

namespace ht {

TEST_CASE("build automaton", "[ac-automaton][container]") {
  ht::ac_automaton ac;

  ac.push("she");
  ac.push("he");
  ac.push("say");
  ac.push("shr");
  ac.push("her");

  ac.build();
}

TEST_CASE("push and query", "[ac-automaton][container]") {
  ht::ac_automaton ac;

  ac.push("she");
  ac.push("he");
  ac.push("say");
  ac.push("shr");
  ac.push("her");

  ac.build();

  std::string text = "shesayhe";
  auto results     = ac.query(text);
  REQUIRE(!results.empty());
  for (const auto &[p, pos] : results) {
    std::cout << "(" << p << ", " << pos << ")" << std::endl;
  }
}

}  // namespace ht

// vim: et sw=2 ts=2
