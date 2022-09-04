// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#include <memory>
#include <span>
#include <tuple>
#include <utility>

#include "catch2/catch_all.hpp"
#include "ht/core/type_utils.hpp"
#include "ht/memory/memory_view.hh"

struct POD_A {  // 8
  uint32_t f1;
  uint32_t f2;
} __attribute__((packed));

struct POD_B {  // 16
  uint32_t f1;
  uint32_t f2;
  uint64_t f3;
} __attribute__((packed));

struct POD_C {  // 20
  uint32_t f1;
  uint32_t f2;
  uint32_t f3;
  uint64_t f4;
} __attribute__((packed));

struct NonPOD {
  std::string str;
};

TEST_CASE("test memory view", "[memory][memory-view]") {
  auto buf = std::make_unique<char[]>(100);

  SECTION("normal") {
    auto s       = std::span<char>{buf.get(), 100};
    auto view    = ht::view_as<POD_A, POD_B, POD_C>(s);
    using view_t = std::decay_t<decltype(view)>;

    REQUIRE(std::is_same_v<view_t::raw_ptr_t, char *>);
    REQUIRE(std::tuple_size_v<view_t::layers_pack_t> == 3);
    REQUIRE(
        std::is_same_v<std::tuple_element_t<0, view_t::layers_pack_t>, POD_A>);
    REQUIRE(
        std::is_same_v<std::tuple_element_t<1, view_t::layers_pack_t>, POD_B>);
    REQUIRE(
        std::is_same_v<std::tuple_element_t<2, view_t::layers_pack_t>, POD_C>);
  }

  SECTION("const") {
    auto s       = std::span<const char>{buf.get(), 100};
    auto view    = ht::view_as<POD_A, POD_B, POD_C>(s);
    using view_t = std::decay_t<decltype(view)>;

    REQUIRE(std::is_same_v<view_t::raw_ptr_t, const char *>);
    REQUIRE(std::tuple_size_v<view_t::layers_pack_t> == 3);
    REQUIRE(std::is_same_v<std::tuple_element_t<0, view_t::layers_pack_t>,
                           const POD_A>);
    REQUIRE(std::is_same_v<std::tuple_element_t<1, view_t::layers_pack_t>,
                           const POD_B>);
    REQUIRE(std::is_same_v<std::tuple_element_t<2, view_t::layers_pack_t>,
                           const POD_C>);
  }
}

TEST_CASE("test type-utils: tuple_slice", "[memory][tuple-slice]") {
  using slice0 = ht::tuple_slice<0, POD_A, POD_B, POD_C>;
  REQUIRE(std::tuple_size_v<slice0::first> == 0);
  REQUIRE(std::tuple_size_v<slice0::second> == 3);
  REQUIRE(ht::tuple_size_bytes_v<slice0::first> == 0);
  REQUIRE(ht::tuple_size_bytes_v<slice0::second> == 44);
  using slice1 = ht::tuple_slice<1, POD_A, POD_B, POD_C>;
  REQUIRE(std::tuple_size_v<slice1::first> == 1);
  REQUIRE(std::tuple_size_v<slice1::second> == 2);
  REQUIRE(ht::tuple_size_bytes_v<slice1::first> == 8);
  REQUIRE(ht::tuple_size_bytes_v<slice1::second> == 36);
  using slice2 = ht::tuple_slice<2, POD_A, POD_B, POD_C>;
  REQUIRE(std::tuple_size_v<slice2::first> == 2);
  REQUIRE(std::tuple_size_v<slice2::second> == 1);
  REQUIRE(ht::tuple_size_bytes_v<slice2::first> == 24);
  REQUIRE(ht::tuple_size_bytes_v<slice2::second> == 20);
  using slice3 = ht::tuple_slice<3, POD_A, POD_B, POD_C>;
  REQUIRE(std::tuple_size_v<slice3::first> == 3);
  REQUIRE(std::tuple_size_v<slice3::second> == 0);
  REQUIRE(ht::tuple_size_bytes_v<slice3::first> == 44);
  REQUIRE(ht::tuple_size_bytes_v<slice3::second> == 0);
}

TEST_CASE("test layer", "[memory][memory-view]") {
  auto buf     = std::make_unique<char[]>(100);
  auto s       = std::span<char>{buf.get(), 100};
  auto view    = ht::view_as<POD_A, POD_B, POD_C>(s);
  using view_t = std::decay_t<decltype(view)>;

  {
    auto ptr = view.layer<0>();
    REQUIRE(reinterpret_cast<char *>(ptr) == buf.get());
  }
  {
    auto ptr = view.layer<1>();
    REQUIRE(reinterpret_cast<char *>(ptr) == buf.get() + 8);
  }
  {
    auto ptr = view.layer<2>();
    REQUIRE(reinterpret_cast<char *>(ptr) == buf.get() + 24);
  }
}

// vim: et sw=2 ts=2
