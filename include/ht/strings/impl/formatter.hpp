// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include <string>
#include <string_view>

namespace ht {

struct FormatterHelper;

namespace details {

struct DebugStruct {
  template<typename T>
  DebugStruct& field(std::string_view name, const T& value);
  void finish();

 private:
  explicit DebugStruct(FormatterHelper *helper);
  friend struct FormatterHelper;

 private:
  FormatterHelper *helper_;
  bool has_fields_ = false;
};

struct DebugTuple {
  template<typename T>
  DebugStruct& field(const T& value);
  void finish();

 private:
  FormatterHelper *helper_;
};

}  // namespace details

struct FormatterHelper {
 public:
  [[nodiscard]] bool is_pretty() const;

  details::DebugStruct debug_struct(std::string_view name);

 private:
  std::string output_;
};

namespace details {

DebugStruct::DebugStruct(FormatterHelper *helper) : helper_(helper) {
}

template<typename T>
DebugStruct& DebugStruct::field(std::string_view name, const T& value) {
  if (helper_->is_pretty()) {
  }

  return *this;
}

}  // namespace details

}  // namespace ht
