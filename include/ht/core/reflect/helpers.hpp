// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include <string_view>
#include <tuple>
#include <type_traits>
#include <utility>

namespace ht {

namespace __details {
template<typename T, typename = void>
struct _refl_info : std::false_type {};

template<typename T>
struct _refl_info<T, std::void_t<typename T::__ht_refl_info>> : std::true_type {
  using type = typename T::__ht_refl_info;
};
}  // namespace __details

template<typename T>
using has_refl = std::integral_constant<bool, __details::_refl_info<T>::value>;

template<typename T>
constexpr bool has_refl_v = __details::_refl_info<T>::value;

template<typename T>
concept refl_exists = has_refl_v<T>;

template<typename T>
  requires has_refl_v<T>
using refl_info = typename __details::_refl_info<T>::type;

template<uint32_t I, typename T>
  requires refl_exists<T>
static auto &refl_ref(T &obj) {
  return obj.*(std::get<I>(refl_info<std::remove_cvref_t<T>>::property_ref()));
}

template<typename T, uint32_t I>
  requires refl_exists<T>
using property_type_at = std::tuple_element_t<
    I, typename refl_info<std::remove_cvref_t<T>>::property_type>;

}  // namespace ht
