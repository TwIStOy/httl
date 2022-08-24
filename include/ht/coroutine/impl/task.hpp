// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include "ht/coroutine/impl/task_promise.hpp"

namespace ht::coro::__impl {

template<typename T>
struct _task<T>::type {
  using promise_type = task_promise<T>;
  using value_type   = T;

  type() = default;

  explicit type(std::coroutine_handle<promise_type> handle)
      : handle_(std::move(handle)) {
  }

  ~type() {
    if (handle_) {
      handle_.destroy();
    }
  }

  std::coroutine_handle<promise_type> handle_;
};

}  // namespace ht::coro::__impl

// vim: et sw=2 ts=2
