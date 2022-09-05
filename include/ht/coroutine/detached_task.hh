// Copyright (c) 2020 - present, Hawtian Wang (twistoy.wang@gmail.com)
//

#pragma once  // NOLINT(build/header_guard)

#include <atomic>
#include <coroutine>
#include <memory>

namespace ht::coro {

class detached_task_promise;

class detached_task_handle {
 public:
  inline explicit detached_task_handle(
      std::coroutine_handle<> coroutine) noexcept
      : coroutine_(coroutine) {
  }

  inline bool finish() noexcept {
    if (finished_.exchange(true)) {
      return false;
    }
    coroutine_.destroy();
    return true;
  }

 private:
  std::atomic<bool> finished_{false};
  std::coroutine_handle<void> coroutine_;
};

class detached_task {
 public:
  using promise_type = detached_task_promise;

  explicit detached_task(std::shared_ptr<detached_task_handle> handle);

  bool cancel() noexcept;

 private:
  std::shared_ptr<detached_task_handle> handle_;
};

class detached_task_promise {
 public:
  class final_awaiter {
   public:
    explicit final_awaiter(
        std::shared_ptr<detached_task_handle> handle) noexcept;

    void await_resume() const noexcept {
    }

    [[nodiscard]] static bool await_ready() noexcept {
      return false;
    }

    void await_suspend(std::coroutine_handle<> coroutine) noexcept;

   private:
    std::shared_ptr<detached_task_handle> handle_;
  };

  detached_task_promise();

  detached_task get_return_object();

  static std::suspend_never initial_suspend() noexcept {
    return {};
  }

  final_awaiter final_suspend() noexcept;

  void return_void() const noexcept {
  }

  static void unhandled_exception() noexcept;

 private:
  std::shared_ptr<detached_task_handle> handle_;
};

inline detached_task_promise::detached_task_promise()
    : handle_{std::make_shared<detached_task_handle>(
          std::coroutine_handle<detached_task_promise>::from_promise(*this))} {
}

inline detached_task_promise::final_awaiter::final_awaiter(
    std::shared_ptr<detached_task_handle> handle) noexcept
    : handle_{std::move(handle)} {
}

inline void detached_task_promise::final_awaiter::await_suspend(
    std::coroutine_handle<>) noexcept {
  handle_->finish();
}

inline detached_task detached_task_promise::get_return_object() {
  return detached_task{handle_};
}

inline detached_task_promise::final_awaiter
detached_task_promise::final_suspend() noexcept {
  return final_awaiter{handle_};
}

inline void detached_task_promise::unhandled_exception() noexcept {
  std::terminate();
}

inline detached_task::detached_task(
    std::shared_ptr<detached_task_handle> handle)
    : handle_(std::move(handle)) {
}

inline bool detached_task::cancel() noexcept {
  return handle_->finish();
}

}  // namespace ht::coro
