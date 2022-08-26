// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include <string>
#include <vector>

#include "ht/core/result.hpp"

namespace ht {

class command_line_interpreter {
  struct command_info {
    std::string name;
    std::string help;
  };

  struct input_command {
    std::string cmd;
    std::vector<std::string> args;
  };

  // std::vector<command_info> commands_;

  auto parse(const std::string &text) -> result<input_command, std::string> {
    std::string word;
    for (auto c : text) {
    }
    /*
     * func_.clear();
     * args_.clear();
     *
     * std::string word;
     * for (char c : text) {
     *   if (std::isspace(c)) {
     *     if (!word.empty()) {
     *       args_.push_back(word);
     *       word.clear();
     *     }
     *   } else {
     *     word.push_back(c);
     *   }
     * }
     * if (!word.empty()) {
     *   args_.push_back(word);
     * }
     *
     * if (!args_.empty()) {
     *   func_ = args_[0];
     *   args_.erase(args_.begin());
     * }
     */
  }
};

}  // namespace ht

// vim: et sw=2 ts=2
