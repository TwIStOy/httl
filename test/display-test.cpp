// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#include "ht/strings/display.hpp"

#include <iostream>
#include <sstream>
#include <vector>

#include "catch2/catch_all.hpp"
#include "ht/strings/string_utility.hpp"

struct I_S_Struct : ht::IDisplay {
  void Stringify(std::ostream &oss) const override {
    oss << "I_S_Struct";
  }
};

struct H_S_Struct {};

namespace ht::display_helper {
template<>
struct DisplayHelper<H_S_Struct> {
  inline std::string operator()(const H_S_Struct &s) const {
    return "H_S_Struct";
  }
};
}  // namespace ht::display_helper

TEST_CASE("display test", "[strings][display]") {
  I_S_Struct i_d{};
  H_S_Struct i_b{};

  SECTION("1") {
    {
      std::ostringstream oss;
      ht::Stringify(oss, i_d);
      REQUIRE(oss.str() == "I_S_Struct");
    }

    {
      std::ostringstream oss;
      ht::Stringify(oss, i_b);
      REQUIRE(oss.str() == "H_S_Struct");
    }
  }

  SECTION("2") {
    (void)fmt::format("{}", "test");
  }
}

TEST_CASE("display test with fmt", "[strings][display]") {
  SECTION("uint32_t") {
    uint32_t v = 10;
    auto x     = fmt::format("{}", v);
    REQUIRE(x == "10");
  }
}

TEST_CASE("JoinString", "[strings]") {
  std::vector<I_S_Struct> vec;
  vec.resize(3);

  SECTION("1") {
    auto str = ht::JoinString(vec, ", ");
    REQUIRE(str == "I_S_Struct, I_S_Struct, I_S_Struct");
  }
}
