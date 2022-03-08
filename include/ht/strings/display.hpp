// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include <fmt/format.h>

#include <ostream>
#include <sstream>
#include <string>
#include <type_traits>

namespace ht {

struct IDisplay {
  virtual ~IDisplay() = default;

  virtual void Stringify(std::ostream &oss) const = 0;

  [[nodiscard]] inline std::string Stringify() const;
};

namespace display_helper {

template<typename T>
struct DisplayHelper {};

template<typename T, typename = void>
struct IsHelperImpled : public std::false_type {};

template<typename T>
struct IsHelperImpled<
    T, std::void_t<decltype(DisplayHelper<T>{}(std::declval<T>()))>>
    : std::true_type {};

}  // namespace display_helper

template<typename T>
constexpr bool is_stringifiable_v =
    display_helper::IsHelperImpled<T>::value || std::is_base_of_v<IDisplay, T>;

inline std::string IDisplay::Stringify() const {
  std::ostringstream oss;
  Stringify(oss);
  return oss.str();
}

template<typename T,
         typename = std::enable_if_t<std::is_base_of_v<IDisplay, T> ||
                                     display_helper::IsHelperImpled<T>::value>>
inline std::ostream &operator<<(std::ostream &oss, const T &obj) {
  if constexpr (std::is_base_of_v<IDisplay, T>) {
    static_cast<const IDisplay &>(obj).Stringify(oss);
    return oss;
  }
  if constexpr (display_helper::IsHelperImpled<T>::value) {
    display_helper::DisplayHelper<T> helper;
    return oss << helper(obj);
  }
}

template<typename T,
         typename = std::enable_if_t<std::is_base_of_v<IDisplay, T> ||
                                     display_helper::IsHelperImpled<T>::value>>
void Stringify(std::ostream &oss, const T &obj) {
  oss << obj;
}

template<typename T,
         typename = std::enable_if_t<std::is_base_of_v<IDisplay, T> ||
                                     display_helper::IsHelperImpled<T>::value>>
std::string Stringify(const T &obj) {
  std::ostringstream oss;
  oss << obj;
  return oss.str();
}

}  // namespace ht

// vim: et sw=2 ts=2
