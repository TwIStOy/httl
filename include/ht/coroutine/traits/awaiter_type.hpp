// Copyright (c) 2020 - present, Hawtian Wang (twistoy.wang@gmail.com)
//

#pragma once  // NOLINT(build/header_guard)

#include <concepts>
#include <coroutine>
#include <type_traits>

#include "ht/coroutine/traits/coroutine_handle_type.hpp"

namespace ht::coro {

template<typename T>
concept valid_await_suspend_return_value =
    std::is_void_v<T> || std::same_as<T, bool> || coroutine_handle_type<T>;

template<typename T>
concept awaiter_type = requires(T v, std::coroutine_handle<> h) {
                         { v.await_ready() } -> std::convertible_to<bool>;
                         { v.await_resume() };
                         {
                           v.await_suspend(h)
                           } -> valid_await_suspend_return_value;
                       };

}  // namespace ht::coro
