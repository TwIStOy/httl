// Copyright (c) 2020 - present, Hawtian Wang (twistoy.wang@gmail.com)
//

#pragma once  // NOLINT(build/header_guard)

#include <utility>

#include "ht/coroutine/detail/manual_event.hh"
#include "ht/coroutine/tasks/sync_wait.hh"

namespace ht::coro::utils {

template<typename T>
auto sync_wait(T &&awaitable) {
  auto t = make_sync_wait_task(std::forward<T>(awaitable));
  detail::manual_event event;
  t.start(&event);
  event.wait();
  return t.result();
}

}  // namespace ht::coro::utils
