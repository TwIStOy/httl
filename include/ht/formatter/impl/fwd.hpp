// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#include <ht/formatter/impl/writer.hpp>

namespace ht::formatter::details {

struct DebugStruct;
struct DebugTuple;

struct Helper {
  [[nodiscard]] bool is_pretty() const;
  _Writer writer_;
};

}  // namespace ht::formatter::details
