// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#include <type_traits>

#include "catch2/catch_all.hpp"
#include "ht/core/named_wrapper.hpp"

TEST_CASE("construct from T", "[core][named_wrapper]") {
  using named_u32 = ht::named_wrapper<uint32_t, struct test_u32_tag>;

  named_u32 a(10u);
  named_u32 b;

  REQUIRE(a.value() == 10);
  REQUIRE(b.value() == 0);
}

TEST_CASE("named wrapper, skill incrementable", "[core][named_wrapper]") {
  using named_u32 = ht::named_wrapper<uint32_t, struct test_u32_tag,
                                      ht::named_wrapper_skills::incrementable>;

  named_u32 a(10u);
  named_u32 b(20u);

  a += b;

  REQUIRE(a.value() == 30);
}

// vim: et sw=2 ts=2
