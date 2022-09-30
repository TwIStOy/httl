// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include <algorithm>
#include <coroutine>

namespace ht::coro {

namespace _exchange_coroutine_handle_impl {

struct _exchange_coroutine_handle_cpo {
  template<typename T>
  auto operator()(T &p, std::coroutine_handle<> handle) const {
    return tag_invoke(_exchange_coroutine_handle_cpo{}, p, handle);
  }
};
inline const _exchange_coroutine_handle_cpo exchange_coroutine_handle;

}  // namespace _exchange_coroutine_handle_impl

using _exchange_coroutine_handle_impl::exchange_coroutine_handle;

}  // namespace ht::coro

// vim: et sw=2 ts=2
