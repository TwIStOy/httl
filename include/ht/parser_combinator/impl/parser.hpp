// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include <concepts>
#include <type_traits>
#include <utility>

#include <ht/core/result.hpp>
#include <ht/core/type_traits.hpp>
#include <ht/parser_combinator/impl/input_stream.hpp>

namespace ht::_parser_combinator_impl {

template<typename T>
inline constexpr bool valid_parser_result_v = false;

template<typename T, typename U>
inline constexpr bool
    valid_parser_result_v<result<std::pair<T, input_stream>, U>> = true;

template<typename Func>
  requires std::invocable<Func, input_stream> &&
           valid_parser_result_v<std::invoke_result_t<Func, input_stream>>
struct _parser {
  using func_invoke_result = std::invoke_result_t<Func, input_stream>;

  using value_type = typename func_invoke_result::value_type::first_type;
  using error_type = typename func_invoke_result::error_type;
  using func_t     = Func;
  using result_t   = result<std::pair<value_type, input_stream>, error_type>;

  using result_as_tuple_t =
      std::conditional_t<is_tuple_v<value_type>, value_type,
                         std::tuple<value_type>>;

  [[no_unique_address]] func_t _action;

  template<bool noexcept_ = std::is_nothrow_invocable_v<Func, input_stream>>
  auto operator()(const input_stream& input) const noexcept(noexcept_) {
    return _action(input);
  }
};

}  // namespace ht::_parser_combinator_impl

namespace ht {

template<typename Func>
auto make_parser(Func&& func) {
  return _parser_combinator_impl::_parser<Func>{std::forward<Func>(func)};
}

template<typename T>
inline constexpr bool is_parser_v = false;

template<typename T>
inline constexpr bool is_parser_v<_parser_combinator_impl::_parser<T>> = true;

template<typename VT, typename ET = void>
using parser_result_t =
    result<std::pair<VT, _parser_combinator_impl::input_stream>, ET>;

}  // namespace ht

// vim: et sw=2 ts=2
