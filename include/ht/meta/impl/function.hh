// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include <tuple>
#include <type_traits>
#include <utility>

namespace ht {

template<typename Fn>
struct function_traits
    : public function_traits<
          decltype(&std::remove_reference_t<Fn>::operator())> {};

template<typename T, typename R, typename... Args>
struct function_traits<R (T::*)(Args...) const>
    : function_traits<R (*)(Args...)> {};

template<typename T, typename R, typename... Args>
struct function_traits<R (T::*)(Args...)> : function_traits<R (*)(Args...)> {};

template<typename R, typename... Args>
struct function_traits<R (*)(Args...)> {
  static constexpr auto args_num = sizeof...(Args);

  using result_t = R;
  using args_t   = std::tuple<Args...>;
  template<std::size_t I>
  using arg_t = std::tuple_element_t<I, args_t>;
};

}  // namespace ht

// vim: et sw=2 ts=2
