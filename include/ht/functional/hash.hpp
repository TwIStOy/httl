// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include <concepts>
#include <cstddef>
#include <functional>
#include <string>
#include <string_view>
#include <tuple>
#include <type_traits>
#include <utility>

#include <ht/meta/impl/for_.hpp>

namespace ht {

template<typename T>
struct Hash;

namespace _ht_hash_internal {

// NOTE(hawtian): hash_combine function and magic numbers from boost
template<typename T>
void hash_combine(std::size_t *seed, const T& value) {
  Hash<T> hasher;
  *seed ^= hasher(value) + 0x9e3779b9 + (*seed << 6) + (*seed >> 2);
}

template<typename T, typename = void>
struct has_transparent : std::false_type {};

template<typename T>
struct has_transparent<T, std::void_t<typename T::is_transparent>>
    : std::true_type {};

template<typename T>
static constexpr bool has_transparent_v = has_transparent<T>::value;

}  // namespace _ht_hash_internal

template<typename T>
struct Hash {
  // default implementation, use std::hash
  using hash_t = std::hash<T>;
  // NOTE(hawtian): in default mode, no `is_transparent` defined

  [[nodiscard]] inline std::size_t operator()(const T& value) const noexcept {
    return hash_t{}(value);
  }
};

template<>
struct Hash<std::string> {
  using hash_t         = std::hash<std::string_view>;
  using is_transparent = void;

  [[nodiscard]] inline std::size_t operator()(
      std::string_view value) const noexcept {
    return hash_t{}(value);
  }
};

template<typename First, typename Second>
struct Hash<std::pair<First, Second>> {
  using hash_first_t  = Hash<First>;
  using hash_second_t = Hash<Second>;

  template<typename T, typename U>
    requires std::invocable<hash_first_t, const T&> &&
             std::invocable<hash_second_t, const U&>
  std::size_t operator()(const std::pair<T, U>& rhs) const noexcept {
    std::size_t seed = 0;
    _ht_hash_internal::hash_combine(&seed, rhs.first);
    _ht_hash_internal::hash_combine(&seed, rhs.rhs);
    return seed;
  }
};

template<typename... Args>
struct Hash<std::tuple<Args...>> {
 private:
  template<typename Func, std::size_t... Is>
  void for_(Func&& func, std::index_sequence<Is...>) {
    (func(std::integral_constant<std::size_t, Is>{}), ...);
  }

 public:
  template<typename... Ts>
    requires(std::invocable<Hash<Args>, const Ts&> && ...)
  std::size_t operator()(const std::tuple<Ts...>& arg) const noexcept {
    std::size_t seed = 0;

    for_(
        [&seed, &arg](auto _i) {
          constexpr auto i = decltype(_i)::value;
          _ht_hash_internal::hash_combine(&seed, std::get<i>(arg));
        },
        std::make_index_sequence<sizeof...(Args)>{});

    return seed;
  }
};

}  // namespace ht

// vim: et sw=2 ts=2
