// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include <sstream>
#include <type_traits>

#include <ht/core/tag_invoke.hpp>
#include <ht/meta/impl/typename.hpp>

namespace ht {

namespace _stringify_impl {
struct __indent {
  int16_t indent;
  uint16_t level;
};

static inline std::ostream& operator<<(std::ostream& oss,
                                       const __indent& settings) {
  if (settings.indent < 0) {
    return oss;
  }
  if (settings.indent == 0 || settings.level == 0) {
    return oss;
  }
  for (int16_t i = 0; i < settings.indent; i++) {
    for (uint16_t j = 0; j < settings.level; j++) {
      oss << ' ';
    }
  }
  return oss;
}
}  // namespace _stringify_impl

namespace _tag_impl {

struct stringify_fn {
  template<typename T, bool noexcept_ = nothrow_tag_invocable_v<
                           stringify_fn, T, uint16_t, int16_t>>
  auto operator()(T&& value, int16_t indent = -1) const noexcept(noexcept_) {
    if constexpr (ht::tag_invocable<stringify_fn, T, uint16_t, int16_t>) {
      return ht::tag_invoke(*this, std::forward<T>(value),
                            static_cast<uint16_t>(0), indent);
    } else {
      std::ostringstream oss;
      oss << std::forward<T>(value);
      return oss.str();
    }
  }

  template<typename T, bool noexcept_ = nothrow_tag_invocable_v<
                           stringify_fn, T, uint16_t, int16_t>>
  auto operator()(T&& value, uint16_t level, int16_t indent) const
      noexcept(noexcept_) {
    if constexpr (ht::tag_invocable<stringify_fn, T, uint16_t, int16_t>) {
      return ht::tag_invoke(*this, std::forward<T>(value), level, indent);
    } else {
      std::ostringstream oss;
      oss << std::forward<T>(value);
      return oss.str();
    }
  }
};

struct debug_stringify_fn {
  template<typename T, bool noexcept_ = nothrow_tag_invocable_v<
                           debug_stringify_fn, T, uint16_t, int16_t>>
  auto operator()(T&& value, int16_t indent = -1) const noexcept(noexcept_) {
    std::ostringstream oss;
    oss << "<anoymous>: " << pretty_typename<T>::value << " = "
        << ht::tag_invoke(*this, std::forward<T>(value),
                          static_cast<uint16_t>(0), indent);
    return oss.str();
  }

  template<typename T, bool noexcept_ = nothrow_tag_invocable_v<
                           debug_stringify_fn, T, uint16_t, int16_t>>
  auto operator()(T&& value, uint16_t level, int16_t indent) const
      noexcept(noexcept_) {
    std::ostringstream oss;
    if (level == 0) {
      oss << "<anoymous>: " << pretty_typename<T>::value << " = ";
    }
    oss << ht::tag_invoke(*this, std::forward<T>(value), level, indent);
    return oss.str();
  }
};

}  // namespace _tag_impl

inline constexpr _tag_impl::stringify_fn stringify{};
inline constexpr _tag_impl::debug_stringify_fn debug_stringify{};

}  // namespace ht

// vim: et sw=2 ts=2
