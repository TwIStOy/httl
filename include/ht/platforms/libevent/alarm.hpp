// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include <event.h>

#include <chrono>
#include <memory>
#include <utility>

#include "ht/platforms/libevent/event_deleter.hpp"

namespace ht::platform::libevent {

template<typename F>
class alarm {
 public:
  explicit alarm(::event_base *base, F callback);

  ~alarm() = default;

  void cancel() {
    event_.reset();
  }

  void setup(std::chrono::milliseconds later) {
    ::timeval t{};
    t.tv_sec  = later.count() / 1000;
    t.tv_usec = (later.count() % 1000ull) * 1000ull;

    event_.reset(::event_new(base_, -1, EV_READ, &alarm::event_callback, this));
    evtimer_add(event_.get(), &t);
  }

 private:
  static void event_callback(int fd, short event, void *context) {
    (void)fd;
    (void)event;
    auto p = reinterpret_cast<alarm *>(context);
    p->event_.reset();
    p->callback_();
  }

 private:
  ::event_base *base_;
  std::unique_ptr<::event, EventDeleter> event_;
  [[no_unique_address]] F callback_;
};

template<typename F>
auto make_alarm(::event_base *base, F &&f) {
  return alarm<F>(base, std::forward<F>(f));
}

}  // namespace ht::platform::libevent

// vim: et sw=2 ts=2
