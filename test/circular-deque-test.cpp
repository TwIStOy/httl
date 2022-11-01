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
#include "ht/container/impl/circular_deque.hpp"
#include "ht/macro/stealer.h"
#include "ht/strings/stringify.hpp"

using test_deque = ht::circular_deque<int>;

STEALER(test_deque_stealer, test_deque,
        STEAL_FIELD(typename test_deque::size_type, begin_),
        STEAL_FIELD(typename test_deque::size_type, end_));

TEST_CASE("circular-deque initialize", "[container][circular-deque]") {
  ht::circular_deque<int> a(10);

  REQUIRE(a.size() == 0);
  REQUIRE(a.empty());
  REQUIRE(a.max_size() == 10);
  REQUIRE(a.capacity() == 11);
}

TEST_CASE("circular-deque at, out_of_range", "[container][circular-deque]") {
  ht::circular_deque<int> a(10);
  REQUIRE_THROWS_AS(a.at(0), std::out_of_range);
}

TEST_CASE("circular-deque at, normal", "[container][circular-deque]") {
  ht::circular_deque<int> a(10);
  test_deque_stealer stealer(a);

  a.push_back(10);

  REQUIRE_NOTHROW(a.at(0));
  REQUIRE(a.at(0) == 10);

  REQUIRE(stealer.begin_ == 0);
  REQUIRE(stealer.end_ == 1);
}

TEST_CASE("circular-deque [], no throw", "[container][circular-deque]") {
  ht::circular_deque<int> a(10);
  test_deque_stealer stealer(a);

  a.push_back(10);

  REQUIRE_NOTHROW(a[0]);
  REQUIRE(a[0] == 10);

  REQUIRE(stealer.begin_ == 0);
  REQUIRE(stealer.end_ == 1);
}

TEST_CASE("circular-deque front", "[container][circular-deque]") {
  ht::circular_deque<int> a(10);
  test_deque_stealer stealer(a);

  a.push_back(10);
  a.push_back(9);

  REQUIRE(a.size() == 2);
  REQUIRE_NOTHROW(a.front());
  REQUIRE(a.front() == 10);

  REQUIRE(stealer.begin_ == 0);
  REQUIRE(stealer.end_ == 2);
}

TEST_CASE("circular-deque back", "[container][circular-deque]") {
  ht::circular_deque<int> a(10);
  test_deque_stealer stealer(a);

  a.push_back(10);
  a.push_back(9);

  REQUIRE(a.size() == 2);
  REQUIRE_NOTHROW(a.back());
  REQUIRE(a.back() == 9);

  REQUIRE(stealer.begin_ == 0);
  REQUIRE(stealer.end_ == 2);
}

// vim: et sw=2 ts=2
