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

namespace ht::core::__tag_invoke {

void tag_invoke();

struct _fn {
  template<typename CPO, typename... Args,
           bool noexcept_ = noexcept(tag_invoke(std::declval<CPO>(),
                                                std::declval<Args>()...))>
  constexpr auto operator()(CPO cpo, Args&&...args) const noexcept(noexcept_) {
    return tag_invoke(std::move(cpo), std::forward<Args>(args)...);
  }
};

}  // namespace ht::core::__tag_invoke

namespace ht {

namespace _tag_invoke {
inline constexpr core::__tag_invoke::_fn tag_invoke{};
}  // namespace _tag_invoke
using namespace _tag_invoke;  // NOLINT

template<auto& CPO>
using tag_t = std::remove_cvref_t<decltype(CPO)>;

template<typename Tag, typename... Args>
concept tag_invocable = std::is_invocable_v<decltype(tag_invoke), Tag, Args...>;

template<class Tag, class... Args>
concept nothrow_tag_invocable =
    tag_invocable<Tag, Args...> &&
    std::is_nothrow_invocable_v<decltype(tag_invoke), Tag, Args...>;

template<class Tag, class... Args>
inline bool constexpr nothrow_tag_invocable_v =
    tag_invocable<Tag, Args...> &&
    std::is_nothrow_invocable_v<decltype(tag_invoke), Tag, Args...>;

template<class Tag, class... Args>
using tag_invoke_result =
    std::invoke_result<decltype(tag_invoke), Tag, Args...>;

template<class Tag, class... Args>
using tag_invoke_result_t =
    std::invoke_result_t<decltype(tag_invoke), Tag, Args...>;

}  // namespace ht

// vim: et sw=2 ts=2
