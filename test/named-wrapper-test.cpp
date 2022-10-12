// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#include <compare>
#include <functional>
#include <type_traits>

#include "catch2/catch_all.hpp"
#include "ht/container/named_wrapper.hpp"

TEST_CASE("construct from T", "[container][named_wrapper]") {
  using named_u32 = ht::named_wrapper<uint32_t, struct test_u32_tag>;

  named_u32 a(10u);
  named_u32 b;

  REQUIRE(a.value() == 10);
  REQUIRE(b.value() == 0);
}

TEST_CASE("named wrapper, skill incrementable", "[container][named_wrapper]") {
  using named_u32 = ht::named_wrapper<uint32_t, struct test_u32_tag,
                                      ht::named_wrapper_skills::incrementable>;

  named_u32 a(10u);
  named_u32 b(20u);

  a += b;

  REQUIRE(a.value() == 30);
}

TEST_CASE("named wrapper, skill pre-incrementable",
          "[container][named_wrapper]") {
  using named_u32 =
      ht::named_wrapper<uint32_t, struct test_u32_tag,
                        ht::named_wrapper_skills::pre_incrementable>;

  named_u32 a(10u);
  named_u32 b(20u);

  ++a;

  REQUIRE(a.value() == 11);
}

TEST_CASE("named wrapper, skill addable", "[container][named_wrapper]") {
  using named_u32 = ht::named_wrapper<uint32_t, struct test_u32_tag,
                                      ht::named_wrapper_skills::addable>;

  named_u32 a(10u);
  named_u32 b(20u);

  auto c = a + b;

  REQUIRE(std::is_same_v<std::decay_t<decltype(c)>, named_u32>);
  REQUIRE(c.value() == 30);
}

TEST_CASE("named wrapper, skill subtractable", "[container][named_wrapper]") {
  using named_u32 = ht::named_wrapper<uint32_t, struct test_u32_tag,
                                      ht::named_wrapper_skills::subtractable>;

  named_u32 a(10u);
  named_u32 b(20u);

  auto c = b - a;

  REQUIRE(std::is_same_v<std::decay_t<decltype(c)>, named_u32>);
  REQUIRE(c.value() == 10);
}

TEST_CASE("named wrapper, skill multiplicable", "[container][named_wrapper]") {
  using named_u32 = ht::named_wrapper<uint32_t, struct test_u32_tag,
                                      ht::named_wrapper_skills::multiplicable>;

  named_u32 a(10u);
  named_u32 b(20u);

  auto c = b * a;

  REQUIRE(std::is_same_v<std::decay_t<decltype(c)>, named_u32>);
  REQUIRE(c.value() == 200);
}

TEST_CASE("named wrapper, skill nagatable", "[container][named_wrapper]") {
  using named_i32 = ht::named_wrapper<int32_t, struct test_32_tag,
                                      ht::named_wrapper_skills::negatable>;

  named_i32 a(10);
  named_i32 b(20);

  auto c = -a;

  REQUIRE(std::is_same_v<std::decay_t<decltype(c)>, named_i32>);
  REQUIRE(c.value() == -10);
}

TEST_CASE("named wrapper, skill hash", "[container][named_wrapper]") {
  using named_i32 = ht::named_wrapper<int32_t, struct test_32_tag,
                                      ht::named_wrapper_skills::hashable>;

  named_i32 a(10);

  std::hash<named_i32>{}(a);
}

TEST_CASE("named wrapper, skill compare", "[container][named_wrapper]") {
  using named_i32 = ht::named_wrapper<int32_t, struct test_32_tag,
                                      ht::named_wrapper_skills::comparable>;

  named_i32 a(10), b(11);
  a < b;
  a == b;
}

// vim: et sw=2 ts=2
