// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#include "ht/strings/stringify.hpp"

#include <sstream>
#include <string>

#include "catch2/catch_all.hpp"
#include "ht/core/tag_invoke.hpp"
#include "ht/strings/string_utility.hpp"

struct Tmp {
  int x = 10;

  friend auto tag_invoke(ht::tag_t<ht::stringify>, const Tmp &value) {
    std::ostringstream oss;
    oss << value.x;
    return oss.str();
  }
};
TEST_CASE("stringify-test", "[stringify][strings]") {
  {
    Tmp tmp;
    auto res = ht::stringify(tmp);
    REQUIRE(res == "10");
  }

  {
    Tmp tmps[] = {{}, {}, {}};
    auto res   = ht::str_join(tmps, ", ");
    REQUIRE(res == "10, 10, 10");
  }
}

// vim: et sw=2 ts=2
