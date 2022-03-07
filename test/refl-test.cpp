// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#include <utility>

#include "catch2/catch_all.hpp"
#include "ht/core/reflect/helpers.hpp"
#include "ht/core/reflect/macros.h"
#include "ht/network/socket.hpp"

TEST_CASE("test reflect struct", "[reflect][compile_time]") {
  struct TestType {
    int foo;
    double bar;
    uint32_t foobar;

    HT_REFL_INS_DECL(TestType, foo, bar, foobar);
  };

  REQUIRE(ht::has_refl_v<TestType>);
  REQUIRE(!ht::has_refl_v<uint32_t>);

  auto info = ht::refl_info<TestType>{};

  REQUIRE(info.get_name() == "TestType");
  REQUIRE(info.num_properties() == 3);
  REQUIRE(info.property_name().size() == 3);

  REQUIRE(info.property_name().at(0) == "foo");
  REQUIRE(info.property_name().at(1) == "bar");
  REQUIRE(info.property_name().at(2) == "foobar");

  REQUIRE(std::is_same_v<
          std::tuple_element_t<0, ht::refl_info<TestType>::property_type>,
          int>);
  REQUIRE(std::is_same_v<
          std::tuple_element_t<1, ht::refl_info<TestType>::property_type>,
          double>);
  REQUIRE(std::is_same_v<
          std::tuple_element_t<2, ht::refl_info<TestType>::property_type>,
          uint32_t>);

  TestType test;
  test.foo              = 0;
  ht::refl_ref<0>(test) = 1;

  REQUIRE(test.foo == 1);
}

