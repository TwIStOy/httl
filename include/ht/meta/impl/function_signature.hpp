// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include <tuple>
#include <utility>

namespace ht {

namespace _func_sig_impl {

template<typename R, typename... Args>
std::tuple<R, std::tuple<Args...>> arg_helper(R (*)(Args...));

template<typename Cls, typename R, typename... Args>
std::tuple<R, std::tuple<Args...>> arg_helper(R (Cls::*)(Args...));

template<typename Cls, typename R, typename... Args>
std::tuple<R, std::tuple<Args...>> arg_helper(R (Cls::*)(Args...) const);

template<typename F>
auto arg_helper(F) -> decltype(arg_helper(&F::operator()));

template<typename T>
struct func_sig {};

template<typename R, typename... Args>
struct func_sig<std::tuple<R, std::tuple<Args...>>> {
  using result_t   = R;
  using argument_t = std::tuple<Args...>;
};

}  // namespace _func_sig_impl

template<typename F>
using function_signature =
    _func_sig_impl::func_sig<decltype(_func_sig_impl::arg_helper(
        std::declval<F>()))>;

}  // namespace ht

// vim: et sw=2 ts=2
