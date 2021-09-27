// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include <ostream>
#include <sstream>
#include <string>

namespace ht {

struct IDisplay {
  virtual ~IDisplay() = default;

  virtual void Stringify(std::ostream &oss) const = 0;

  inline std::string Stringify() const;
};

struct IDebugDisplay {
  virtual ~IDebugDisplay() = default;

  virtual void DebuggingStringify(std::ostream &) const = 0;

  inline std::string DebuggingStringify() const;
};

inline std::string IDisplay::Stringify() const {
  std::ostringstream oss;
  Stringify(oss);
  return oss.str();
}

inline std::string IDebugDisplay::DebuggingStringify() const {
  std::ostringstream oss;
  DebuggingStringify(oss);
  return oss.str();
}

}  // namespace ht

// vim: et sw=2 ts=2
