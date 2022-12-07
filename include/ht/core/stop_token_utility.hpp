// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include <cassert>
#include <optional>
#include <stop_token>

#include <ht/core/cpp_feature.h>

namespace ht {

struct stop_source_functor {
  explicit stop_source_functor(std::stop_source *source) : source_(source) {
    assert(source_);
  }

  HT_ALWAYS_INLINE void operator()() const noexcept {
    source_->request_stop();
  }

  std::stop_source *source_;
};

template<typename S>
struct stop_token_adapter {
  explicit stop_token_adapter(std::stop_source *source) : source_(source) {
  }

  // After given stop_source is stopped, my stop_source will be stopped too.
  std::stop_token subscribe(S token) {
    const bool stop_possible = token.stop_possible();
    callback_.emplace(std::move(token), stop_source_functor(source_));
    return stop_possible ? source_->get_token() : std::stop_token{};
  }

  void unsubscribe() noexcept {
    callback_.reset();
  }

 private:
  using callback_t = std::stop_callback<stop_source_functor>;

  std::stop_source *source_;
  [[no_unique_address]] std::optional<callback_t> callback_{};
};

template<>
class stop_token_adapter<std::stop_token> {
 public:
  static std::stop_token subscribe(std::stop_token stoken) noexcept {
    return stoken;
  }

  void unsubscribe() noexcept {
  }
};

template<typename StopToken>
// RAII wrapper for stop_token_adapter
struct stop_token_adapter_subscription {
  std::stop_token subscribe(StopToken stoken) noexcept {
    isSubscribed_ = true;
    return adapter_.subscribe(std::move(stoken));
  }

  void unsubscribe() noexcept {
    if (isSubscribed_) {
      isSubscribed_ = false;
      adapter_.unsubscribe();
    }
  }

  ~stop_token_adapter_subscription() {
    unsubscribe();
  }

 private:
  bool isSubscribed_ = false;
  [[no_unique_address]] stop_token_adapter<StopToken> adapter_;
};

}  // namespace ht

// vim: et sw=2 ts=2
