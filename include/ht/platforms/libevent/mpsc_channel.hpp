// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include <event.h>

#include <mutex>

namespace ht::platform::libevent {

template<typename E>
class mpsc_channel {
 public:
  explicit mpsc_channel(::event_base *base, int max_size = -1);

  using value_type = E;

 private:
  ::event_base *base_;
  int max_size_;
};

}  // namespace ht::platform::libevent

// vim: et sw=2 ts=2
