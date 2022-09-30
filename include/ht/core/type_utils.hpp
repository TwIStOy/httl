// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include <cxxabi.h>

#include <memory>
#include <string>
#include <tuple>
#include <utility>

namespace ht {

template<typename T>
std::string demangle() {
  int status;
  std::unique_ptr<char[], void (*)(void *)> result(
      abi::__cxa_demangle(typeid(T).name(), nullptr, nullptr, &status),
      std::free);
  return result ? std::string(result.get()) : "error occurred";
}

template<typename T>
struct tuple_size_bytes {};

template<typename... Ts>
struct tuple_size_bytes<std::tuple<Ts...>> {
  static constexpr auto value = (sizeof(Ts) + ... + 0);
};

template<typename T>
inline static constexpr auto tuple_size_bytes_v = tuple_size_bytes<T>::value;

template<std::size_t I, std::size_t... Is>
auto index_sequence_plus(std::index_sequence<Is...>) {
  return std::index_sequence<(Is + I)...>{};
}

namespace _detail {

template<typename T, std::size_t... Is>
  requires((Is <= std::tuple_size_v<T>) && ...)
auto new_tuple_from_index(T t, std::index_sequence<Is...>) {
  return std::tuple<std::tuple_element_t<Is, T>...>{};
}

}  // namespace _detail

template<std::size_t I, typename... Ts>
  requires(I <= sizeof...(Ts))
struct tuple_slice {
  using first  = decltype(_detail::new_tuple_from_index(
      std::tuple<Ts...>{}, std::make_index_sequence<I>{}));
  using second = decltype(_detail::new_tuple_from_index(
      std::tuple<Ts...>{},
      index_sequence_plus<I>(std::make_index_sequence<sizeof...(Ts) - I>{})));
};

// Utility template struct for represent a specify type in parameters for
// overloading to avoid object overhead
template<typename T>
struct type_tag {
  using type = T;
};

}  // namespace ht

// vim: et sw=2 ts=2
