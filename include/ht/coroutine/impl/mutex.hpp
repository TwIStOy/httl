// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include <atomic>
#include <cassert>
#include <coroutine>
#include <cstdint>
#include <utility>

namespace ht::coro {

template<template<typename> class A>
class _async_mutex {
 public:
  struct async_mutex_unique_lock_awaiter {
    explicit async_mutex_unique_lock_awaiter(_async_mutex *m) : mutex_(m) {
    }

    [[nodiscard]] static bool await_ready() noexcept {
      return false;
    }

    bool await_suspend(std::coroutine_handle<> co) noexcept {
      handle_ = co;

      while (true) {
        auto old_state = mutex_->state_.load(std::memory_order_acquire);

        if (old_state.locked_state > 0) {
          // already shared acquired, push myself onto the head of waiter stack
          next_ = old_state.unique_awaiters;

          auto new_state            = old_state;
          new_state.unique_awaiters = this;

          if (mutex_->state_.compare_exchange_weak(old_state, new_state,
                                                   std::memory_order_acquire,
                                                   std::memory_order_relaxed)) {
            // acquire failed, should suspend
            return true;
          }
        } else if (old_state.locked_state == 0) {
          // not locked, acquire immediately
          auto new_state         = old_state;
          new_state.locked_state = -1;

          if (mutex_->state_.compare_exchange_weak(old_state, new_state,
                                                   std::memory_order_acquire,
                                                   std::memory_order_relaxed)) {
            // lock acquired, don't suspend
            return false;
          }
        } else {
          // already unique acquired, push myself onto the head of waiter stack
          next_ = old_state.unique_awaiters;

          auto new_state            = old_state;
          new_state.unique_awaiters = this;

          if (mutex_->state_.compare_exchange_weak(old_state, new_state,
                                                   std::memory_order_acquire,
                                                   std::memory_order_relaxed)) {
            // acquire failed, should suspend
            return true;
          }
        }
      }
    }

    void await_resume() {
    }

    _async_mutex *mutex_;
    std::coroutine_handle<> handle_;
    async_mutex_unique_lock_awaiter *next_{nullptr};
  };

  struct async_mutex_shared_lock_awaiter {
    explicit async_mutex_shared_lock_awaiter(_async_mutex *m) : mutex_(m) {
    }

    [[nodiscard]] static bool await_ready() noexcept {
      return false;
    }

    bool await_suspend(std::coroutine_handle<> co) noexcept {
      handle_ = co;

      while (true) {
        auto old_state = mutex_->state_.load(std::memory_order_acquire);

        if (old_state.locked_state > 0) {
          // already shared acquired
          auto new_state = old_state;
          new_state.locked_state++;

          if (mutex_->state_.compare_exchange_weak(old_state, new_state,
                                                   std::memory_order_acquire,
                                                   std::memory_order_relaxed)) {
            // lock acquired, don't suspend
            return false;
          }
        } else if (old_state.locked_state == 0) {
          // not locked, acquire immediately
          auto new_state = old_state;
          new_state.locked_state++;

          if (mutex_->state_.compare_exchange_weak(old_state, new_state,
                                                   std::memory_order_acquire,
                                                   std::memory_order_relaxed)) {
            // lock acquired, don't suspend
            return false;
          }
        } else {
          // already unique acquired
          next_ = old_state.shared_awaiters;

          auto new_state            = old_state;
          new_state.shared_awaiters = this;

          if (mutex_->state_.compare_exchange_weak(old_state, new_state,
                                                   std::memory_order_acquire,
                                                   std::memory_order_relaxed)) {
            // acquired failed, suspend
            return true;
          }
        }
      }
    }

    void await_resume() {
    }

    _async_mutex *mutex_;
    std::coroutine_handle<> handle_;
    async_mutex_shared_lock_awaiter *next_{nullptr};
  };

  /**
   * @brief construct a mutex that is not currently locked.
   */
  _async_mutex();

  /**
   * @brief destroy a mutex
   *
   * behaviour is undefined if there are any waiting awaiters.
   */
  ~_async_mutex();

  /***********************
   *  Exclusive Locking  *
   ***********************/
  async_mutex_unique_lock_awaiter lock() {
    return async_mutex_unique_lock_awaiter{this};
  }

  bool try_lock() {
    while (true) {
      auto old_state = state_.load(std::memory_order_acquire);

      if (old_state.locked_state == 0) {
        // not locked, acquire immediately
        auto new_state         = old_state;
        new_state.locked_state = -1;

        if (state_.compare_exchange_weak(old_state, new_state,
                                         std::memory_order_acquire,
                                         std::memory_order_relaxed)) {
          // lock acquired, don't suspend
          return true;
        }
      } else {
        // already shared or unique acquired
        return false;
      }
    }
  }

  void unlock() {
    assert(state_.load(std::memory_order_relaxed).locked_state == -1);

    while (true) {
      state old_state = state_.load(std::memory_order_acquire);

      if (old_state.unique_awaiters == nullptr &&
          old_state.shared_awaiters == nullptr) {
        // no next
        auto new_state         = old_state;
        new_state.locked_state = 0;

        if (state_.compare_exchange_weak(old_state, new_state,
                                         std::memory_order_acquire,
                                         std::memory_order_relaxed)) {
          return;
        }
      } else if (old_state.unique_awaiters == nullptr) {
        // notify all shared awaiters to resume
        // TODO(hawtian): impl this
      } else if (old_state.unique_awaiters != nullptr) {
        // notify next unique awaiter
        auto new_state            = old_state;
        new_state.locked_state    = -1;
        new_state.unique_awaiters = old_state.unique_awaiters->next_;

        if (state_.compare_exchange_weak(old_state, new_state,
                                         std::memory_order_acquire,
                                         std::memory_order_relaxed)) {
          old_state.unique_awaiters->handle_.resume();
          return;
        }
      }
    }
  }

  /********************
   *  Shared Locking  *
   ********************/
  async_mutex_shared_lock_awaiter lock_shared() {
    return async_mutex_shared_lock_awaiter{this};
  }

  bool try_lock_shared() {
    while (true) {
      auto old_state = state_.load(std::memory_order_acquire);

      if (old_state.locked_state >= 0) {
        // not locked, acquire immediately
        auto new_state = old_state;
        new_state.locked_state++;

        if (state_.compare_exchange_weak(old_state, new_state,
                                         std::memory_order_acquire,
                                         std::memory_order_relaxed)) {
          // lock acquired, don't suspend
          return true;
        }
      } else {
        // already unique acquired
        return false;
      }
    }
  }

  void unlock_shared();

 private:
  struct state {
    async_mutex_unique_lock_awaiter *unique_awaiters{nullptr};
    async_mutex_shared_lock_awaiter *shared_awaiters{nullptr};
    // this field  provides synchronisation form the mutex, it can provide
    // three kinds of values:
    //
    // - negative: unique locked
    // - zero: not locked
    // - positive: shared locked, the number of shared locking acquirements
    int32_t locked_state{0};
  };
  A<state> state_;
};

template<template<typename> class A = std::atomic>
using async_mutex = _async_mutex<A>;

}  // namespace ht::coro

// vim: et sw=2 ts=2
