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
#include <sdt/sync/impl/lock_guard.hh>

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

  Mutex();

 private:
};

}  // namespace sdt::sync
