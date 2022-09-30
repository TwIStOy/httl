// Copyright (c) 2020 - present, Hawtian Wang (twistoy.wang@gmail.com)
//

#pragma once  // NOLINT(build/header_guard)

#include <ht/coroutine/traits/get_awaiter.hpp>

namespace ht::coro {

template<typename T>
concept can_get_awaiter =
    requires(T v) { (__details::get_awaiter(std::declval<T>())); };

template<can_get_awaiter T>
struct awaitable_traits {
  using awaiter_t = decltype(__details::get_awaiter(std::declval<T>()));

  using awaiter_result_t = decltype(std::declval<awaiter_t>().await_resume());
};

}  // namespace ht::coro
