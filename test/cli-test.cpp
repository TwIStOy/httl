// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#include "ht/cli.hpp"

#include "catch2/catch_all.hpp"
#include "ht/macro/stealer.h"

using cli_parse_result =
    ht::result<ht::command_line_interpreter::input_command, std::string>;
using cli_commands_type = std::unordered_map<
    std::string, std::unique_ptr<ht::command_line_interpreter::command_base>>;

STEALER(cli_interp_stealer, ht::command_line_interpreter,
        STEAL_METHOD(cli_parse_result, parse, const std::string &),
        STEAL_FIELD(cli_commands_type, commands_));

TEST_CASE("cli parse, 01", "[cli]") {
  auto text = R"(abc)";

  ht::command_line_interpreter interp;
  cli_interp_stealer stealer(interp);
  auto r = stealer.parse(text);
  REQUIRE(r.is_ok());

  REQUIRE(r.unwrap().cmd == "abc");
  REQUIRE(r.unwrap().args.empty());
}

TEST_CASE("cli parse, 02", "[cli]") {
  auto text = R"(abc 123 "abc")";

  ht::command_line_interpreter interp;
  cli_interp_stealer stealer(interp);
  auto r = stealer.parse(text);
  REQUIRE(r.is_ok());

  REQUIRE(r.unwrap().cmd == "abc");
  REQUIRE(r.unwrap().args.size() == 2);
  REQUIRE(r.unwrap().args[0] == "123");
  REQUIRE(r.unwrap().args[1] == "abc");
}

TEST_CASE("cli parse, 03", "[cli]") {
  auto text = R"(abc 123 "a\nb\"c")";

  ht::command_line_interpreter interp;
  cli_interp_stealer stealer(interp);
  auto r = stealer.parse(text);
  REQUIRE(r.is_ok());

  REQUIRE(r.unwrap().cmd == "abc");
  REQUIRE(r.unwrap().args.size() == 2);
  REQUIRE(r.unwrap().args[0] == "123");
  REQUIRE(r.unwrap().args[1] == "a\nb\"c");
}

TEST_CASE("cli reg, 01", "[cli]") {
  ht::command_line_interpreter interp;
  cli_interp_stealer stealer(interp);
  interp.register_command(
      [](uint32_t a, uint32_t b) {
        return a + b;
      },
      "add", "add");

  REQUIRE(stealer.commands_.size() == 1);

  /*
   * auto r =
   * interp.eval("add 1 2");
   *
   * REQUIRE(
   */
}
