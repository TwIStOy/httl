// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include <cctype>
#include <cstdlib>
#include <functional>
#include <memory>
#include <string>
#include <string_view>
#include <tuple>
#include <type_traits>
#include <unordered_map>
#include <utility>
#include <vector>

#include "fmt/format.h"
#include "ht/core/result.hpp"
#include "ht/core/type_traits.hpp"
#include "ht/parser_combinator/parser_combinator.hpp"
#include "ht/strings/stringify.hpp"

namespace ht {

namespace _cli_impl {

static inline auto cli_char =
    combinators::make_char_predict_parser([](char ch) {
      return std::isalnum(ch);
    });

static inline auto str_char =
    combinators::make_char_predict_parser([](char ch) {
      return ch != '"' && ch != '\\';
    });

static inline auto escaped_char =
    (combinators::make_char_predict_parser([](char ch) {
       return '\\';
     }) +
     combinators::char_any) >>
    [](const auto &x) {
      auto ch = std::get<1>(x);
      if (ch == 'b') {
        return '\b';
      } else if (ch == 'n') {
        return '\n';
      } else if (ch == 'r') {
        return '\r';
      } else
        return std::get<1>(x);
    };

// static inline auto str0 = combinators::combinator_many(str_char);

static inline auto str_double_quote =
    combinators::make_char_predict_parser([](char ch) {
      return ch == '"';
    });

static inline auto cli_string = (str_double_quote +
                                 (((str_char || escaped_char) * 0) >>
                                  [](const auto &s) {
                                    std::string str;
                                    for (auto c : s) {
                                      str.push_back(c);
                                    }
                                    return str;
                                  }) +
                                 str_double_quote) >>
                                [](auto &&x) {
                                  return std::get<1>(x);
                                };

static inline auto cli_arg = ((cli_char * 1) >>
                              [](auto &&x) {
                                return std::string{std::begin(x), std::end(x)};
                              }) ||
                             cli_string;

static inline auto cli_space =
    combinators::make_char_predict_parser([](char ch) {
      return std::isspace(ch);
    }) *
    1;

static inline auto cli_line = (cli_arg + (((cli_space + cli_arg) >>
                                           [](auto &&x) {
                                             return std::get<1>(x);
                                           }) *
                                          0));

}  // namespace _cli_impl

class command_line_interpreter {
 public:
  struct input_command {
    std::string cmd;
    std::vector<std::string> args;
  };

  struct command_base {
    explicit command_base(std::string help) : help(std::move(help)) {
    }
    std::string help;

    virtual result<std::string, std::string> invoke(
        const std::vector<std::string> &args) = 0;
  };

 private:
  std::unordered_map<std::string, std::unique_ptr<command_base>> commands_;

  template<typename To>
  static To type_convert(const std::string &t) {
    if constexpr (std::is_same_v<To, std::string>) {
      return t;
    } else if constexpr (std::is_integral_v<To>) {
      char *end;
      return std::strtoll(t.data(), &end, 10);
    } else {
      return To(t);
    }
  }

  template<typename argument_t, typename Func, std::size_t... I>
  static auto call_command(Func &&f, std::index_sequence<I...>,
                           const std::vector<std::string> &args) {
    return f(type_convert<std::tuple_element_t<I, argument_t>>(args[I])...);
  }

 public:
  template<typename Func>
  std::string register_command(Func &&func, std::string name,
                               std::string help_msg) {
    using sig = function_signature<Func>;

    struct command final : command_base {
      command(Func &&func, std::string help_msg)
          : command_base(std::move(help_msg)), func(std::forward<Func>(func)) {
      }

      std::decay_t<Func> func;
      result<std::string, std::string> invoke(
          const std::vector<std::string> &args) final {
        if (args.size() != std::tuple_size_v<typename sig::argument_t>) {
          return err(fmt::format(
              "argument number not match, expect: {}, but {}",
              std::tuple_size_v<typename sig::argument_t>, args.size()));
        }

        auto v = call_command<typename sig::argument_t>(
            this->func,
            std::make_index_sequence<
                std::tuple_size_v<typename sig::argument_t>>{},
            args);

        return ok(ht::stringify(v));
      }
    };

    commands_.emplace(std::move(name),
                      std::make_unique<command>(std::forward<Func>(func),
                                                std::move(help_msg)));
  }

  result<std::string, std::string> eval(const std::string &text) {
    auto r = parse(text);
    if (r.is_err()) {
      return err(std::move(r).unwrap_err());
    }

    auto [cmd, args] = r.unwrap();
    if (auto it = commands_.find(cmd); it != commands_.end()) {
      return it->second->invoke(args);
    } else {
      return err(fmt::format("no command: {} found", cmd));
    }
  }

 private:
  result<input_command, std::string> parse(const std::string &text) {
    auto input = parser_combinator::input_stream{text};

    auto r = _cli_impl::cli_line(input);
    if (r.is_err()) {
      return err(std::move(r).unwrap_err());
    }
    auto [cmd, args] = r.unwrap().first;
    return ok(input_command{std::move(cmd), std::move(args)});
  }
};

}  // namespace ht

// vim: et sw=2 ts=2
