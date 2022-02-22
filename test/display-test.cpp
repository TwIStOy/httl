// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#include "ht/strings/display.hpp"

#include <sstream>

#include "catch2/catch_all.hpp"

struct I_D_Struct : ht::IDebugDisplay {
  void DebuggingStringify(std::ostream &oss) const {
    oss << "I_D_Struct";
  }
};

struct I_S_Struct : ht::IDisplay {
  void Stringify(std::ostream &oss) const {
    oss << "I_S_Struct";
  }
};

struct I_B_Struct : ht::IDisplay, ht::IDebugDisplay {
  void Stringify(std::ostream &oss) const {
    oss << "I_B_Struct";
  }

  void DebuggingStringify(std::ostream &oss) const {
    oss << "I_B_Struct";
  }
};

struct H_D_Struct {};

struct H_S_Struct {};

struct H_B_Struct {};

namespace ht::display_helper {
template<>
struct DebugDisplayHelper<H_D_Struct> {
  inline std::string operator()(const H_D_Struct &s) const {
    return "H_D_Struct";
  }
};

template<>
struct DisplayHelper<H_S_Struct> {
  inline std::string operator()(const H_S_Struct &s) const {
    return "H_S_Struct";
  }
};

template<>
struct DebugDisplayHelper<H_B_Struct> {
  inline std::string operator()(const H_D_Struct &s) const {
    return "H_B_Struct";
  }
};

template<>
struct DisplayHelper<H_B_Struct> {
  inline std::string operator()(const H_S_Struct &s) const {
    return "H_B_Struct";
  }
};
}  // namespace ht::display_helper

TEST_CASE("display test", "[strings][display]") {
  I_D_Struct i_d{};
  I_B_Struct i_b{};

  SECTION("1") {
    {
      std::ostringstream oss;
      ht::DebugStringify(oss, i_d);
      REQUIRE(oss.str() == "I_D_Struct");
    }

    {
      std::ostringstream oss;
      ht::DebugStringify(oss, i_b);
      REQUIRE(oss.str() == "I_B_Struct");
    }
  }

  SECTION("2") {
  }
}

TEST_CASE("display test with fmt", "[strings][display]") {
}
