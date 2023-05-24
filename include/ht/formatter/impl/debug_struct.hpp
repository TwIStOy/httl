// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#include <cassert>
#include <string_view>

#include <ht/formatter/impl/fwd.hpp>

namespace ht::formatter::details {

struct DebugStruct {
  DebugStruct();

  template<typename T>
  DebugStruct& field(std::string_view name, const T& value);
  void finish();

 private:
  Helper *helper_;
  bool has_fields_ = false;
};

template<typename T>
DebugStruct& DebugStruct::field(std::string_view name, const T& value) {
  assert(helper_ != nullptr);

  if (helper_->is_pretty()) {
    if (!has_fields_) {
      helper_->write_str(" {\n");
    }

    auto sub = PadAdapter{helper_};
    sub.write_str(name);
    sub.write_str(": ");
    value.fmt(&sub);
    sub.write_str(",\n");
  } else {
    if (has_fields_) {
      helper_->write_str(", ");
    } else {
      helper_->write_str(" { ");
    }
    helper_->write_str(name);
    helper_->write_str(": ");
    value.fmt(helper_);
  }

  return *this;
}

}  // namespace ht::formatter::details
