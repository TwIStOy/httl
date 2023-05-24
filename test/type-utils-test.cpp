// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#include <set>
#include <string>
#include <string_view>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>

#include "catch2/catch_all.hpp"
#include "container_utils.hpp"
#include "ht/functional/hash.hpp"
#include "ht/meta/impl/typename.hpp"

#include "sdt/core/trait/impl/container.hh"

#define __STR_VALUE(...)   __STR_VALUE__(__VA_ARGS__)
#define __STR_VALUE__(...) #__VA_ARGS__
#define CHECK_TYPE(...) \
  REQUIRE(ht::pretty_typename<__VA_ARGS__>::value == __STR_VALUE(__VA_ARGS__));

struct Tmp;

using std::operator""sv;

template<>
struct ht::readable_typename<Tmp> {
  static constexpr auto value = "Tmp"sv;
};

TEST_CASE("format type", "[core][type-utils]") {
  CHECK_TYPE(uint16_t);
  CHECK_TYPE(uint32_t);
  CHECK_TYPE(uint64_t);
  CHECK_TYPE(int16_t);
  CHECK_TYPE(int32_t);
  CHECK_TYPE(int64_t);

  // pointer
  REQUIRE(ht::pretty_typename<int64_t *>::value == "int64_t*");

  // lvalue ref
  REQUIRE(ht::pretty_typename<int64_t&>::value == "int64_t&");
  // rvalue ref
  REQUIRE(ht::pretty_typename<int64_t&&>::value == "int64_t&&");

  // string
  CHECK_TYPE(std::string);
  // string_view
  CHECK_TYPE(std::string_view);

  // vector
  CHECK_TYPE(std::vector<std::string>);

  // unordered_map
  CHECK_TYPE(std::unordered_map<std::string, std::string>);

  // tuple
  CHECK_TYPE(std::tuple<std::string, std::string>);

  // unordered_map
  REQUIRE_FALSE(
      ht::pretty_typename<std::unordered_map<std::string, std::string,
                                             ht::Hash<std::string>>>::value ==
      "std::unordered_map<std::string, std::string>");

  CHECK_TYPE(std::pair<std::string, std::string>);
  CHECK_TYPE(std::tuple<std::string, std::string, std::string>);
  CHECK_TYPE(std::variant<std::string, std::string, std::string>);

  CHECK_TYPE(std::unordered_map<std::string, std::string>);
  CHECK_TYPE(std::unordered_multimap<std::string, std::string>);
  CHECK_TYPE(std::map<std::string, std::string>);
  CHECK_TYPE(std::multimap<std::string, std::string>);

  CHECK_TYPE(std::unordered_set<std::string>);
  CHECK_TYPE(std::unordered_multiset<std::string>);
  CHECK_TYPE(std::set<std::string>);
  CHECK_TYPE(std::multiset<std::string>);

  CHECK_TYPE(Tmp);
}

// vim: et sw=2 ts=2
