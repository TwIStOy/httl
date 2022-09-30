// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include <ht/core/cpp_feature.h>

#include <ht/core/tag_invoke.hpp>

namespace ht {

struct unstoppable_token {
  template<typename F>
  struct callback_type {
    explicit callback_type(unstoppable_token, F &&) noexcept {
    }
  };

  static constexpr bool stop_requested() noexcept {
    return false;
  }
  static constexpr bool stop_possible() noexcept {
    return false;
  }
};

namespace _get_stop_token_impl {

struct _get_stop_token_cpo {
  template<typename T>
  HT_ALWAYS_INLINE auto operator()(const T &value) const noexcept {
    if constexpr (tag_invocable<_get_stop_token_cpo, T>) {
      return tag_invoke(_get_stop_token_cpo{}, value);
    } else {
      return unstoppable_token{};
    }
  }
};

inline const _get_stop_token_cpo get_stop_token;

}  // namespace _get_stop_token_impl

using _get_stop_token_impl::get_stop_token;

}  // namespace ht

// vim: et sw=2 ts=2
