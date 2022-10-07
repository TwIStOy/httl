// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include <type_traits>
#include <utility>

namespace ht {

template<typename Func>
  requires std::is_nothrow_move_constructible_v<Func>
class _scope_guard {
 public:
  explicit _scope_guard(Func&& func) noexcept
      : func_(std::forward<Func>(func)) {
  }

  ~_scope_guard() {
    reset();
  }

  void release() noexcept {
    released_ = true;
  }

  void reset() noexcept {
    static_assert(noexcept(std::forward<Func>(func_)()));

    if (!std::exchange(released_, true)) {
      std::forward<Func>(func_)();
    }
  }

 private:
  [[no_unique_address]] Func func_;
  bool released_ = false;
};

template<typename Func>
[[nodiscard]] _scope_guard<Func> scope_guard(Func&& func) {
  return _scope_guard<Func>(std::forward<Func>(func));
}

}  // namespace ht

// vim: et sw=2 ts=2
