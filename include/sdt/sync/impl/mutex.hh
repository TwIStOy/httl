// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include <algorithm>
#include <memory>
#include <utility>

#include <sdt/sync/fwd/mutex_fwd.hh>
#include <sdt/sync/impl/lock_guard.hh>
#include <type_traits>

namespace sdt::sync {

template<typename T, typename M>
class Mutex {
 public:
  using value_type      = T;
  using reference       = value_type&;
  using const_reference = const value_type&;
  using allocator_type  = std::allocator<value_type>;
  using pointer         = std::allocator_traits<allocator_type>::pointer;
  using const_pointer   = std::allocator_traits<allocator_type>::const_pointer;
  using mutex_type      = M;

  template<typename U = T,
           typename   = std::enable_if_t<std::is_default_constructible_v<U>>>
  Mutex() : value_(), mutex_() {
  }

  template<typename... Args>
  explicit Mutex(Args&&...args)
      : value_(std::forward<Args>(args)...), mutex_() {
  }

  Mutex(const Mutex&)            = delete;
  Mutex& operator=(const Mutex&) = delete;

  template<typename U = T,
           typename   = std::enable_if_t<std::is_move_constructible_v<T>>>
  Mutex(Mutex&& rhs) noexcept  // NOLINT
      : value_(std::move(rhs.value_)), mutex_(std::move(rhs.mutex_)) {
  }

  template<typename U = T,
           typename   = std::enable_if_t<std::is_move_assignable_v<T>>>
  Mutex& operator=(Mutex&& rhs) noexcept {
    value_ = std::move(rhs.value_);
    mutex_ = std::move(rhs.mutex_);
    return *this;
  }

 private:
  T value_;
  mutex_type mutex_;
};

}  // namespace sdt::sync
