// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#include <catch2/catch_all.hpp>
#include <ht/coroutine/coroutine.hpp>
#include <ht/coroutine/traits/get_awaiter.hpp>
#include <iostream>

TEST_CASE("coroutine handle type", "[coroutine][traits]") {
  struct P;
  REQUIRE(ht::coro::coroutine_handle_type<std::coroutine_handle<>>);
  REQUIRE(ht::coro::coroutine_handle_type<std::coroutine_handle<P>>);
}

TEST_CASE("awaiter type", "[coroutine][traits]") {
  struct awaiter1 {
    bool await_ready();
    void await_resume();
    void await_suspend();  // invalid
  };
  REQUIRE_FALSE(ht::coro::awaiter_type<awaiter1>);

  struct awaiter2 {
    bool await_ready();
    void await_resume();
    void await_suspend(std::coroutine_handle<>);
  };
  REQUIRE(ht::coro::awaiter_type<awaiter2>);
}

TEST_CASE("do not exec before await", "[coroutine][task]") {
  bool started = false;

  auto func = [&]() -> ht::task<int> {
    std::cout << "func exec" << std::endl;
    started = true;
    co_return 10;
  };

  auto v = ht::sync_wait([&]() -> ht::task<int> {
    std::cout << "task exec" << std::endl;
    auto t = func();

    REQUIRE(!started);
    int x = (co_await t) * 2;
    REQUIRE(started);

    co_return x;
  }());

  REQUIRE(v == 20);
}

TEST_CASE("awaiting default-constructed task throws broken_promise",
          "[coroutine][task]") {
  ht::sync_wait([&]() -> ht::task<> {
    ht::task<> t;
    REQUIRE_THROWS_WITH(co_await t, "broken promise");
  }());
}

TEST_CASE("lots of tasks", "[coroutine][task]") {
  auto return_one = []() -> ht::task<int> {
    co_return 1;
  };

  ht::sync_wait([](auto func) -> ht::task<> {
    int sum = 0;
    for (int i = 0; i < 1'000'000; ++i) {
      sum += co_await func();
    }
    REQUIRE(sum == 1'000'000);
  }(return_one));
}

TEST_CASE("task of reference type", "[coroutine][task]") {
  int value = 3;
  auto f    = [&]() -> ht::task<int &> {
    co_return value;
  };

  SECTION("rvalue") {
    ht::sync_wait([&]() -> ht::task<> {
      decltype(auto) result = co_await f();
      static_assert(std::is_same_v<decltype(result), int &>);
      REQUIRE(&result == &value);
    }());
  }

  SECTION("lvalue") {
    ht::sync_wait([&]() -> ht::task<> {
      auto t                = f();
      decltype(auto) result = co_await t;

      static_assert(std::is_same_v<decltype(result), int &>);
      REQUIRE(&result == &value);
    }());
  }
}

TEST_CASE("detached task start automatically", "[coroutine][detached_task]") {
  bool wait_for_value = false;
  bool started        = false;

  class manually_event {
   public:
    auto operator co_await() noexcept {
      class awaiter {
       public:
        explicit awaiter(manually_event *e) : e_(e) {
        }

        bool await_ready() const noexcept {
          return e_->state_.load() == State::Set;
        }

        bool await_suspend(std::coroutine_handle<> awaiter) {
          e_->handle_ = awaiter;

          auto v = State::NotSet;
          return e_->state_.compare_exchange_strong(v, State::Waiting);
        }

        void await_resume() noexcept {
        }

       private:
        manually_event *e_;
      };

      return awaiter{this};
    }

    void Set() {
      const auto v = state_.exchange(State::Set);
      if (v == State::Waiting) {
        handle_.resume();
      }
    }

    void Reset() noexcept {
      auto v = State::Set;
      state_.compare_exchange_strong(v, State::NotSet);
    }

   private:
    enum class State {
      NotSet,
      Waiting,
      Set,
    };
    std::atomic<State> state_{State::NotSet};
    std::coroutine_handle<> handle_;
  };

  manually_event ev;

  auto get_value = [&]() -> ht::task<int> {
    std::cout << "wait ev" << std::endl;
    co_await ev;
    std::cout << "after ev" << std::endl;
    co_return 10;
  };

  auto func = [&]() -> ht::detached_task {
    wait_for_value = true;
    co_await get_value();
    started = true;
    co_return;
  };

  REQUIRE(!wait_for_value);
  REQUIRE(!started);

  func();

  REQUIRE(wait_for_value);
  REQUIRE(!started);

  std::cout << "SET" << std::endl;
  ev.Set();

  REQUIRE(started);
}

// vim: et sw=2 ts=2
