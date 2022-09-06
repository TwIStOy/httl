// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include <event.h>
#include <memory>

namespace ht::platform::libevent {

struct EventDeleter {
  void operator()(void *p) const noexcept {
    auto e = reinterpret_cast<struct ::event *>(p);
    ::event_del(e);
    ::event_free(e);
  }
};
using EventPtr = std::unique_ptr<::event, EventDeleter>;

}  // namespace ht::platform::libevent

// vim: et sw=2 ts=2
