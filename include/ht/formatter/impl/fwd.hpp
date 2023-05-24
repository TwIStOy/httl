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

struct Helper : public Writer {
  [[nodiscard]] bool is_pretty() const;

  void write_str(std::string_view str) final;

 private:
  _Writer writer_;
};

inline void Helper::write_str(std::string_view str) {
  writer_.write_str(str);
}

}  // namespace ht::formatter::details
