// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#include "ht/core/result.hpp"

#include <concepts>
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

TEST_CASE("copy operator=", "[result][core]") {
  using result_t = ht::result<std::string, uint32_t>;
  { result_t empty; }
  result_t tmp2;
  tmp2.set_value("fuck");
  REQUIRE(tmp2.is_ok());
  REQUIRE(tmp2.unwrap() == "fuck");

  static_assert(std::copy_constructible<std::string>);
  static_assert(std::copy_constructible<uint32_t>);

  {
    result_t tmp = ht::ok("test");
    tmp->append("c");
    tmp2 = tmp;
  }

  REQUIRE(tmp2.is_ok());
  REQUIRE(tmp2.unwrap() == "testc");
}

TEST_CASE("move operator=", "[result][core]") {
  using result_t = ht::result<std::string, uint32_t>;
  result_t tmp2;
  {
    result_t tmp = ht::ok("test");
    tmp2         = std::move(tmp);
  }

  REQUIRE(tmp2.is_ok());
  REQUIRE(tmp2.unwrap() == "test");
}

TEST_CASE("copy construct", "[result][core]") {
  using result_t = ht::result<std::string, uint32_t>;
  result_t tmp   = ht::ok("test");
  auto tmp2      = tmp;

  REQUIRE(tmp2.is_ok());
  REQUIRE(tmp2.unwrap() == "test");
}

TEST_CASE("move construct", "[result][core]") {
  using result_t = ht::result<std::string, uint32_t>;
  result_t tmp   = ht::ok("test");
  auto tmp2      = std::move(tmp);

  REQUIRE(tmp2.is_ok());
  REQUIRE(tmp2.unwrap() == "test");
}

TEST_CASE("operator->", "[result][core]") {
  struct Tmp {
    int a;
  };
  using result_t = ht::result<Tmp, uint32_t>;
  result_t tmp   = ht::ok(Tmp{10});

  REQUIRE(tmp.is_ok());
  REQUIRE(tmp->a == 10);
}

TEST_CASE("function map", "[result][core]") {
  struct Tmp {
    std::string res;
  };
  using from_result_t = ht::result<Tmp, uint32_t>;
  using to_result_t   = ht::result<std::string, uint32_t>;

  from_result_t tmp = ht::ok(Tmp{"tmp"});

  REQUIRE(tmp.is_ok());
  REQUIRE(tmp->res == "tmp");

  to_result_t tmp2 = std::move(tmp).map([](Tmp &&x) {
    std::string xx(std::move(x.res));
    xx.append("tmp");
    return xx;
  });

  REQUIRE(tmp2.is_ok());
  REQUIRE(tmp2.unwrap() == "tmptmp");
}

TEST_CASE("function map_err", "[result][core]") {
  struct Tmp {
    std::string res;
  };
  using from_result_t = ht::result<Tmp, uint32_t>;
  using to_result_t   = ht::result<Tmp, std::string>;

  from_result_t tmp = ht::err(10);

  REQUIRE(tmp.is_err());
  REQUIRE(tmp.unwrap_err() == 10);

  to_result_t tmp2 = std::move(tmp).map_err([](uint32_t x) {
    std::string xx = std::to_string(x);
    xx.append("tmp");
    return xx;
  });

  REQUIRE(tmp2.is_err());
  REQUIRE(tmp2.unwrap_err() == "10tmp");
}

// vim: et sw=2 ts=2
