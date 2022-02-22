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

  inline std::string Stringify() const;
};

struct IDebugDisplay {
  virtual ~IDebugDisplay() = default;

  virtual void DebuggingStringify(std::ostream &) const = 0;

  inline std::string DebuggingStringify() const;
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

template<typename T, typename = void>
struct DebugDisplayHelper {};

template<typename T, typename = void>
struct IsDebugHelperImpled : public std::false_type {};

template<typename T>
struct IsDebugHelperImpled<
    T, std::void_t<decltype(DebugDisplayHelper<T>{}(std::declval<T>()))>>
    : std::true_type {};

// common impls
template<>
struct DebugDisplayHelper<std::string> {
  inline std::string operator()(const std::string &s) const {
    return '"' + s + '"';
  }
};

template<typename _Tp>
struct DebugDisplayHelper<_Tp, std::enable_if_t<std::is_integral_v<_Tp>>> {
  inline std::string operator()(const _Tp &s) const {
    return std::to_string(s);
  }
};

}  // namespace display_helper

template<typename T>
constexpr bool is_stringifiable_v =
    display_helper::IsHelperImpled<T>::value || std::is_base_of_v<IDisplay, T>;

template<typename T>
constexpr bool is_debug_stringifiable_v =
    display_helper::IsDebugHelperImpled<T>::value ||
    std::is_base_of_v<IDebugDisplay, T>;

inline std::string IDisplay::Stringify() const {
  std::ostringstream oss;
  Stringify(oss);
  return oss.str();
}

inline std::string IDebugDisplay::DebuggingStringify() const {
  std::ostringstream oss;
  DebuggingStringify(oss);
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

template<typename T, typename = std::enable_if_t<
                         std::is_base_of_v<IDebugDisplay, T> ||
                         display_helper::IsDebugHelperImpled<T>::value>>
void DebugStringify(std::ostream &oss, const T &obj) {
  if constexpr (std::is_base_of_v<IDebugDisplay, T>) {
    static_cast<const IDebugDisplay &>(obj).DebuggingStringify(oss);
  }
  if constexpr (display_helper::IsDebugHelperImpled<T>::value) {
    display_helper::DebugDisplayHelper<T> helper;
    oss << helper(obj);
  }
}

template<typename T, typename = std::enable_if_t<
                         std::is_base_of_v<IDebugDisplay, T> ||
                         display_helper::IsDebugHelperImpled<T>::value>>
std::string DebugStringify(const T &obj) {
  std::ostringstream oss;
  DebugStringify(oss, obj);
  return oss.str();
}

}  // namespace ht

namespace fmt {

template<typename T>
struct formatter<
    T, char,
    std::void_t<std::enable_if_t<ht::is_stringifiable_v<T> ||
                                 ht::is_debug_stringifiable_v<T>>>> {
  bool debug = false;

  template<typename ParseContext>
  constexpr auto parse(ParseContext &ctx) ->  // NOLINT(runtime/references)
      decltype(ctx.begin()) {
    auto it = ctx.begin();
    auto ed = ctx.end();

    if (it != ed && *it == '?') {
      debug = true;
      it++;
    }

    if (it != ed && *it != '}') {
      throw format_error("invalid format");
    }

    return it;
  }

  template<typename FormatContext>
  auto format(const T &v,
              FormatContext &ctx)  // // NOLINT(runtime/references)
      -> decltype(ctx.out()) {
    if (debug) {
      if constexpr (!ht::is_debug_stringifiable_v<T>) {
        throw format_error(
            "invalid format, expect debug stringifiable methods");
      } else {
        return format_to(ctx.out(), "{}", ht::DebugStringify(v));
      }
    } else {
      if constexpr (!ht::is_stringifiable_v<T>) {
        throw format_error(
            "invalid format, expect debug stringifiable methods");
      } else {
        return format_to(ctx.out(), "{}", ht::Stringify(v));
      }
    }
  }
};

}  // namespace fmt

// vim: et sw=2 ts=2
