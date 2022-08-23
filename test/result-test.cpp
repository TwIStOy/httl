// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#include "ht/core/result.hpp"

#include <string>

#include "catch2/catch_all.hpp"

TEST_CASE("construct from ok", "[result][core]") {
  auto tmp                            = ht::ok("test");
  ht::result<std::string, uint32_t> r = ht::ok("test");

  REQUIRE(r.is_ok());
  REQUIRE(!r.is_err());
  REQUIRE(r.unwrap() == "test");
}

TEST_CASE("construct from err", "[result][core]") {
  auto tmp                            = ht::ok("test");
  ht::result<std::string, uint32_t> r = ht::err(123);

  REQUIRE(!r.is_ok());
  REQUIRE(r.is_err());
  REQUIRE_THROWS(r.unwrap());
}

// vim: et sw=2 ts=2
