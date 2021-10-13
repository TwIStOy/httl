// Copyright (c) 2020 Agora.io, Inc.
//

#include "ht/macro/stealer.h"

#include <iostream>
#include <string>

#include "catch.hpp"

struct PrivateType {
 public:
  void SetPrivateInt(int x) {
    private_int = x;
  }

 private:
  int private_int;
  std::string private_str;

  void PrivateMethod1() {
    std::cout << "PrivateMethod1" << std::endl;
  }
  int PrivateMethod2() const {
    return private_int;
  }
  void PrivateMethod3(const std::string &, uint32_t) {
    (void)private_int;
  }
};

STEALER(PrivateTypeStealer, PrivateType, STEAL_FIELD(int, private_int),
        STEAL_FIELD(std::string, private_str),
        STEAL_METHOD(void, PrivateMethod1),
        STEAL_CONST_METHOD(int, PrivateMethod2),
        STEAL_METHOD(void, PrivateMethod3, const std::string &, uint32_t));

TEST_CASE("stealer macro test", "[stealer][macro]") {
  PrivateType private_object;
  PrivateTypeStealer stealer(private_object);

  private_object.SetPrivateInt(10);
  REQUIRE(stealer.private_int == 10);

  stealer.PrivateMethod1();
}
