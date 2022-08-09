// Copyright (c) 2020 - present, Hawtian Wang (twistoy.wang@gmail.com)
//

#pragma once  // NOLINT(build/header_guard)

#include <atomic>
#include <condition_variable>
#include <coroutine>
#include <mutex>

namespace ht::coro::detail {

class manual_event {
 public:
  inline explicit manual_event(bool init = false) : is_set_(init) {
  }

  ~manual_event() = default;

  void set() noexcept {
    std::unique_lock<std::mutex> lk(mutex_);
    is_set_ = true;
    cv_.notify_all();
  }

  void reset() noexcept {
    std::unique_lock<std::mutex> lk(mutex_);
    is_set_ = false;
  }

  void wait() noexcept {
    std::unique_lock<std::mutex> lk(mutex_);
    cv_.wait(lk, [this]() {
      return is_set_;
    });
  }

 private:
  std::atomic<int> value_;
  std::mutex mutex_;
  std::condition_variable cv_;
  bool is_set_{false};
};

}  // namespace ht::coro::detail
