// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#include "ht/network/impl/types/ip4_addr.hpp"

#include <iostream>
#include <sstream>
#include <string>
#include <string_view>
#include <tuple>
#include <unordered_map>
#include <variant>
#include <vector>

#include "catch2/catch_all.hpp"
#include "ht/strings/string_utility.hpp"

TEST_CASE("operator=", "[network][ip4_addr]") {
  ht::host_ordered_ip4 a(10), b(11);
  REQUIRE(a == b);
}

