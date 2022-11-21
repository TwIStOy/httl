// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include <concepts>
#include <string>
#include <string_view>

#include <range/v3/range/concepts.hpp>

#include <ht/core/cpp_feature.h>
#include <ht/core/impl/forward_like.hpp>

namespace ht {

namespace _str_join_impl {

struct DefaultFormatter {
  inline void operator()(std::string *output, const std::string& value) {
    output->append(value);
  }

  inline void operator()(std::string *output, std::string_view value) {
    output->append(value);
  }

  inline void operator()(std::string *output, std::integral auto&& value) {
    output->append(std::to_string(value));
  }
};

}  // namespace _str_join_impl

template<typename Func>
[[nodiscard]] std::string str_join(ranges::sized_range auto&& rng,
                                   std::string_view sep, Func&& func)
  requires std::invocable<
      Func&&, std::string *,
      forward_like_t<HT_TYPE(rng), ranges::range_value_t<HT_TYPE(rng)>>>
{
  auto end = ranges::end(rng);
  std::string output;
  bool first = true;
  for (auto it = ranges::begin(rng); it != end; ++it) {
    if (first) {
      first = false;
    } else {
      output.append(sep);
    }
    std::invoke(std::forward<Func>(func), &output,
                forward_like<HT_TYPE(rng)>(*it));
  }
  return output;
}

template<typename Func>
[[nodiscard]] std::string str_join(ranges::sized_range auto&& rng,
                                   std::string_view sep) {
  return str_join(HT_FORWARD(rng), sep, _str_join_impl::DefaultFormatter{});
}

}  // namespace ht

// vim: et sw=2 ts=2
