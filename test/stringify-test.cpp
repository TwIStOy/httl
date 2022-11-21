// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#include "ht/strings/stringify.hpp"

#include <iostream>
#include <sstream>
#include <string>
#include <string_view>
#include <tuple>
#include <unordered_map>
#include <variant>
#include <vector>

#include "catch2/catch_all.hpp"
#include "ht/core/reflect/helpers.hpp"
#include "ht/core/reflect/macros.h"
#include "ht/core/tag_invoke.hpp"
#include "ht/strings/string_utility.hpp"

struct Tmp {
  int x = 10;

  friend auto tag_invoke(ht::tag_t<ht::stringify>, const Tmp& value, uint16_t,
                         int16_t) {
    std::ostringstream oss;
    oss << value.x;
    return oss.str();
  }

  friend auto tag_invoke(ht::tag_t<ht::debug_stringify>, const Tmp& value,
                         uint16_t, int16_t) {
    std::ostringstream oss;
    oss << value.x;
    return oss.str();
  }
};

TEST_CASE("test simple struct", "[stringify][strings]") {
  {
    Tmp tmp;
    auto res = ht::stringify(tmp);
    REQUIRE(res == "10");
  }

  {
    Tmp tmps[] = {{}, {}, {}};
    auto res = ht::str_join(tmps, ", ", [](std::string *output, const auto& r) {
      output->append(ht::stringify(r));
    });
    REQUIRE(res == "10, 10, 10");
  }
}

TEST_CASE("test variant", "[stringify][strings]") {
  std::variant<uint32_t, std::string, Tmp> a = Tmp{};

  std::cerr << ht::stringify(a) << std::endl;
  // std::cerr << ht::debug_stringify(a) << std::endl;
}

struct InnerReflType {
  int x         = 10;
  int y         = 20;
  std::string z = "z";
  Tmp tmp{};

  HT_REFL_INS_DECL(InnerReflType, x, y, z, tmp);
};

struct ReflType {
  int x         = 10;
  int y         = 20;
  std::string z = "z";
  Tmp tmp{};
  InnerReflType inner{};

  HT_REFL_INS_DECL(ReflType, x, y, z, tmp, inner);
};

TEST_CASE("test refl", "[stringify][strings]") {
  ReflType value;

  std::cerr << ht::stringify(value, 2) << std::endl;
  std::cerr << ht::debug_stringify(value, 2) << std::endl;
}

TEST_CASE("test stl vec", "[stringify][strings]") {
  std::vector<InnerReflType> value{{}, {}, {}};
  std::cerr << ht::debug_stringify(value, 2) << std::endl;
}

TEST_CASE("test stl map", "[stringify][strings]") {
  std::unordered_map<std::string, InnerReflType> value{
      {"1", {}}, {"2", {}}, {"3", {}}};
  std::cerr << ht::debug_stringify(value, 2) << std::endl;
}

TEST_CASE("test stl tuple", "[stringify][strings]") {
  std::tuple<InnerReflType, InnerReflType, InnerReflType> value;
  std::cerr << ht::debug_stringify(value, 2) << std::endl;
}

TEST_CASE("test string_view concat", "[strings][concat]") {
  using std::operator""sv;
  static constexpr auto a = "hello"sv;
  static constexpr auto b = " world"sv;
  static constexpr auto c = "!"sv;

  constexpr auto sum = ht::concat_sv<a, b, c>::value;
}

// vim: et sw=2 ts=2
