// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include <fmt/format.h>

#include <concepts>
#include <stdexcept>
#include <type_traits>
#include <variant>

#include "ht/core/box.hpp"
#include "ht/core/cpp_feature.h"

namespace ht {

struct result_unwrap_error : public std::runtime_error {
  template<typename... Args>
  explicit result_unwrap_error(fmt::format_string<Args...> fmt, Args &&...args)
      : runtime_error(fmt::format(fmt, std::forward<Args>(args)...)) {
  }
};

namespace __impl {

struct value_tag;
struct error_tag;

template<typename Tag, typename T>
struct temp_wrapper {
  T value;
};

template<typename Tag>
struct temp_wrapper<Tag, void> {};

template<typename T, typename D>
struct value_result_base {
  using value_type   = T;
  using derived_type = D;

  HT_ALWAYS_INLINE value_type &unwrap() const & {
  }

  box<value_type> value_;
};

}  // namespace __impl

template<typename VT, typename ET>
struct result {
  using value_type = VT;
  using error_type = ET;

 private:
  enum class _stat { empty, value, error };
  _stat stat_{_stat::empty};
  union {
    box<value_type> value_;
    box<error_type> error_;
  };

 public:
  template<typename U>
    requires std::convertible_to<U, value_type>
  result(__impl::temp_wrapper<__impl::value_tag, U> v) {  // NOLINT
    if constexpr (std::is_void_v<U>) {
      construct_union_member(&value_);
    } else {
      construct_union_member(&value_, std::move(v.value));
    }
    stat_ = _stat::value;
  }

  template<typename U>
    requires std::convertible_to<U, error_type>
  result(__impl::temp_wrapper<__impl::error_tag, U> v) {  // NOLINT
    if constexpr (std::is_void_v<U>) {
      construct_union_member(&error_);
    } else {
      construct_union_member(&error_, std::move(v.value));
    }
    stat_ = _stat::error;
  }

  [[nodiscard]] HT_ALWAYS_INLINE bool is_ok() const noexcept {
    return stat_ == _stat::value;
  }

  template<typename Func>
    requires std::is_invocable_v<Func, value_type>
  [[nodiscard]] HT_ALWAYS_INLINE bool is_ok_and(Func &&func) const
      noexcept(std::is_nothrow_invocable_v<Func, value_type>) {
    return is_ok() && std::forward<Func>(func)(value_.get());
  }

  HT_ALWAYS_INLINE operator bool() const {  // NOLINT
    return is_ok();
  }

  [[nodiscard]] HT_ALWAYS_INLINE bool is_err() const noexcept {
    return stat_ == _stat::error;
  }

  template<typename Func>
    requires std::is_invocable_v<Func, error_type>
  [[nodiscard]] HT_ALWAYS_INLINE bool is_err_and(Func &&func) const
      noexcept(std::is_nothrow_invocable_v<Func, error_type>) {
    return is_err() && std::forward<Func>(func)(error_.get());
  }

  HT_ALWAYS_INLINE decltype(auto) unwrap() & {
    if (!is_ok()) {
      throw result_unwrap_error{"unwrap failed"};
    }

    if constexpr (std::is_void_v<value_type>) {
      return;
    } else {
      return value_.get();
    }
  }

  HT_ALWAYS_INLINE decltype(auto) unwrap() const & {
    if (!is_ok()) {
      throw result_unwrap_error{"unwrap failed"};
    }

    if constexpr (std::is_void_v<value_type>) {
      return;
    } else {
      return value_.get();
    }
  }

  HT_ALWAYS_INLINE decltype(auto) unwrap() && {
    if (!is_ok()) {
      throw result_unwrap_error{"unwrap failed"};
    }

    if constexpr (std::is_void_v<value_type>) {
      return;
    } else {
      return std::move(value_).get();
    }
  }

  HT_ALWAYS_INLINE decltype(auto) unwrap() const && {
    if (!is_ok()) {
      throw result_unwrap_error{"unwrap failed"};
    }

    if constexpr (std::is_void_v<value_type>) {
      return;
    } else {
      return std::move(value_).get();
    }
  }

  HT_ALWAYS_INLINE decltype(auto) unwrap_err() & {
    if (!is_err()) {
      throw result_unwrap_error{"unwrap failed"};
    }

    if constexpr (std::is_void_v<error_type>) {
      return;
    } else {
      return error_.get();
    }
  }

  HT_ALWAYS_INLINE decltype(auto) unwrap_err() && {
    if (!is_err()) {
      throw result_unwrap_error{"unwrap failed"};
    }

    if constexpr (std::is_void_v<error_type>) {
      return;
    } else {
      return std::move(error_).get();
    }
  }

  HT_ALWAYS_INLINE decltype(auto) unwrap_err() const & {
    if (!is_err()) {
      throw result_unwrap_error{"unwrap failed"};
    }

    if constexpr (std::is_void_v<error_type>) {
      return;
    } else {
      return error_.get();
    }
  }

  HT_ALWAYS_INLINE decltype(auto) unwrap_err() const && {
    if (!is_err()) {
      throw result_unwrap_error{"unwrap failed"};
    }

    if constexpr (std::is_void_v<error_type>) {
      return;
    } else {
      return std::move(error_).get();
    }
  }
};

template<typename T>
HT_ALWAYS_INLINE __impl::temp_wrapper<__impl::value_tag, T> ok(T value) {
  return {std::move(value)};
}

HT_ALWAYS_INLINE __impl::temp_wrapper<__impl::value_tag, void> ok() {
  return {};
}

template<typename T>
HT_ALWAYS_INLINE __impl::temp_wrapper<__impl::error_tag, T> err(T value) {
  return {std::move(value)};
}

HT_ALWAYS_INLINE __impl::temp_wrapper<__impl::error_tag, void> err() {
  return {};
}

}  // namespace ht

// vim: et sw=2 ts=2
