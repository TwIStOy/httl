// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include <algorithm>
#include <memory>

#include <sdt/sync/fwd/mutex_fwd.hh>
#include <sdt/sync/fwd/rwlock_fwd.hh>

namespace sdt::sync::details {

/// An RAII implementation of a "scoped lock" of a mutex of value. When this
/// structure is dropped (falls out of scope), the lock will be unlocked.
template<typename T, typename M, template<typename> class L>
class LockGuard final {
 public:
  using value_type      = T;
  using reference       = value_type&;
  using const_reference = const value_type&;
  using allocator_type  = std::allocator<value_type>;
  using pointer         = std::allocator_traits<allocator_type>::pointer;
  using const_pointer   = std::allocator_traits<allocator_type>::const_pointer;

  using mutex_type = M;
  using lock_type  = L<M>;

  ~LockGuard() = default;

  [[nodiscard]] inline reference operator*() noexcept {
    return value_;
  }

  [[nodiscard]] inline const_reference operator*() const noexcept {
    return value_;
  }

  [[nodiscard]] inline pointer operator->() noexcept {
    return &value_;
  }

  [[nodiscard]] inline const_pointer operator->() const noexcept {
    return &value_;
  }

  [[nodiscard]] inline reference value() noexcept {
    return value_;
  }

  [[nodiscard]] inline const_reference value() const noexcept {
    return value_;
  }

 private:
  friend class Mutex<T, M>;
  friend class RWLock<T, M>;

  LockGuard(value_type& value, lock_type lk)
      : value_(value), lk_(std::move(lk)) {
  }

 private:
  value_type& value_;
  lock_type lk_;
};

}  // namespace sdt::sync::details
