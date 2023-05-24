// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include <string>
#include <string_view>
#include <vector>

#include <range/v3/range/conversion.hpp>
#include <range/v3/view/split.hpp>

namespace ht::formatter::details {

struct Writer {
  virtual ~Writer() = default;

  virtual void write_str(std::string_view str) = 0;
};

struct _Writer : public Writer {
  void write_str(std::string_view str) final;

  [[nodiscard]] std::string copy() const;

 private:
  std::string output_;
};

struct PadAdapter : public Writer {
  inline explicit PadAdapter(Writer *writer) : writer_(writer) {
  }

  void write_str(std::string_view str) final;

 private:
  Writer *writer_;
  bool on_newline = true;
};

inline auto _Writer::write_str(std::string_view str) -> void {
  output_.append(str);
}

inline auto _Writer::copy() const -> std::string {
  return output_;
}

inline auto PadAdapter::write_str(std::string_view str) -> void {
  while (!str.empty()) {
    auto pos = str.find('\n');
    // the last part
    if (pos == std::string_view::npos) {
      if (on_newline) {
        writer_->write_str("  ");
      }
      writer_->write_str(str);
      break;
    }

    auto line = str.substr(0, pos);
    if (on_newline) {
      writer_->write_str("  ");
    }
    writer_->write_str(line);
    writer_->write_str("\n");
    on_newline = true;
    str.remove_prefix(pos + 1);
  }
}

}  // namespace ht::formatter::details
