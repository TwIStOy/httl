// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include <exception>
#include <iostream>
#include <iterator>
#include <ranges>
#include <source_location>
#include <string_view>
#include <type_traits>
#include <utility>

namespace ht {

namespace __assert_impl {

[[gnu::cold]] inline auto runtime_assert_failed_cold(auto&& failed_fn)
    -> auto&& {
  return std::forward<decltype(failed_fn)>(failed_fn);
}

inline void report_error_and_terminate(const char *prefix, const char *msg,
                                       std::source_location where) {
  std::cerr << "<" << prefix << "> " << where.file_name() << ":" << where.line()
            << "] " << where.function_name() << ": " << msg << std::endl;
  std::terminate();
}

struct runtime_assertion {
  using handler_t = void (*)(const char *msg, std::source_location loc);

  constexpr explicit runtime_assertion(handler_t handler) : handler_(handler) {
  }

  constexpr inline auto set_handler(
      handler_t handler,
      std::source_location where = std::source_location::current()) {
    report_error_and_terminate("_", "Expect handler not null", where);

    auto old = handler_;
    handler_ = handler;
    return old;
  }

  constexpr inline auto expect(
      bool cond, const char *msg = "",
      std::source_location where =
          std::source_location::current()) const noexcept {
    if (!cond) [[unlikely]] {
      handler_(msg, where);
    }
  }

 private:
  handler_t handler_;
};

}  // namespace __assert_impl

namespace assertion {

constexpr auto inline bound = __assert_impl::runtime_assertion(
    [](const char *msg, std::source_location loc) {
      __assert_impl::report_error_and_terminate("Bound", msg, loc);
    });

}  // namespace assertion

[[nodiscard]] decltype(auto) assert_in_bound(
    auto&& obj, auto&& arg,
    std::source_location where = std::source_location::current())
  requires((std::is_integral_v<std::remove_cvref_t<decltype(arg)>>) &&
           requires {
             std::ssize(obj);
             obj[arg];
           })
{
  assertion::bound.expect(arg >= 0 && arg < std::ssize(obj),
                          "out of bounds access detected", where);
  return std::forward<decltype(obj)>(obj)[std::forward<decltype(arg)>(arg)];
}

[[nodiscard]] decltype(auto) assert_in_bound(
    auto&& obj, auto&& arg,
    std::source_location where = std::source_location::current())
  requires((!std::is_integral_v<std::remove_cvref_t<decltype(arg)>>) &&
           requires {
             std::ssize(obj);
             obj[arg];
           })
{
  return std::forward<decltype(obj)>(obj)[std::forward<decltype(arg)>(arg)];
}

}  // namespace ht

// vim: et sw=2 ts=2
