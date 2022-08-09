// Copyright (c) 2020 - present, Hawtian Wang (twistoy.wang@gmail.com)
//

#pragma once  // NOLINT(build/header_guard)

#include <coroutine>
#include <type_traits>

namespace ht::coro {

template<typename T>
struct is_coroutine_handle : std::false_type {};

template<typename P>
struct is_coroutine_handle<std::coroutine_handle<P>> : std::true_type {};

template<>
struct is_coroutine_handle<std::coroutine_handle<>> : std::true_type {};

template<typename T>
concept coroutine_handle_type = is_coroutine_handle<T>::value;

}  // namespace ht::coro
