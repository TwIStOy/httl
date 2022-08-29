// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include <tuple>

namespace ht {

template<typename... T>
struct inspect;

template<typename T>
inline constexpr bool is_tuple_v = false;

template<typename... Args>
inline constexpr bool is_tuple_v<std::tuple<Args...>> = true;

namespace _type_traits_impl {

template<typename R, typename... Args>
std::tuple<R, std::tuple<Args...>> argument_helper(R (*)(Args...));

template<typename R, typename Cls, typename... Args>
std::tuple<R, std::tuple<Args...>> argument_helper(R (Cls::*)(Args...));

template<typename R, typename Cls, typename... Args>
std::tuple<R, std::tuple<Args...>> argument_helper(R (Cls::*)(Args...) const);

template<typename F>
decltype(argument_helper(&F::operator())) argument_helper(F);

template<typename T>
struct function_signature {};

template<typename R, typename... Args>
struct function_signature<std::tuple<R, std::tuple<Args...>>> {
  using result_t   = R;
  using argument_t = std::tuple<Args...>;
};

}  // namespace _type_traits_impl

template<typename F>
using function_signature = _type_traits_impl::function_signature<
    decltype(_type_traits_impl::argument_helper(std::declval<F>()))>;

}  // namespace ht

// vim: et sw=2 ts=2
