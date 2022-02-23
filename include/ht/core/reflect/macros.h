// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include <string_view>
#include <tuple>
#include <utility>

#include "ht/core/reflect/helpers.hpp"
#include "ht/macro/expand.hpp"
#include "ht/macro/for.h"
#include "ht/macro/select.h"

#define __HT_REFL_SEP_COMMA(...) ,
#define __HT_REFL_SEP_EMPTY(...)

#define __HT_REFL_INS_PROPERTY_TYPE(cls, property) decltype(cls::property)
#define __HT_REFL_INS_PROPERTY_TYPE_ACTION(idx, cls, ...) \
  __HT_REFL_INS_PROPERTY_TYPE(cls, HT_SELECT(idx, __VA_ARGS__))

#define __HT_REFL_INS_PROPERTY_NAME(p)      __HT_REFL_INS_PROPERTY_NAME_IMPL(p)
#define __HT_REFL_INS_PROPERTY_NAME_IMPL(p) #p
#define __HT_REFL_INS_PROPERTY_NAME_ACTION(idx, cls, ...) \
  __HT_REFL_INS_PROPERTY_NAME(HT_SELECT(idx, __VA_ARGS__))

#define __HT_REFL_INS_PROPERTY_REF(c, p) &c::p
#define __HT_REFL_INS_PROPERTY_REF_ACTION(idx, cls, ...) \
  __HT_REFL_INS_PROPERTY_REF(cls, HT_SELECT(idx, __VA_ARGS__))

#define HT_REFL_INS_DECL(cls, ...)                                            \
  struct __ht_refl_info {                                                     \
    static constexpr std::string_view get_name() { return #cls; }             \
    static consteval uint32_t num_properties() {                              \
      return HT_COUNT_ARG(__VA_ARGS__);                                       \
    }                                                                         \
    using property_type [[maybe_unused]] = std::tuple<HT_FOR(                 \
        HT_COUNT_ARG(__VA_ARGS__), __HT_REFL_INS_PROPERTY_TYPE_ACTION,        \
        __HT_REFL_SEP_COMMA, cls, __VA_ARGS__)>;                              \
    static constexpr std::array<std::string_view, HT_COUNT_ARG(__VA_ARGS__)>  \
    property_name() {                                                         \
      return {HT_FOR(HT_COUNT_ARG(__VA_ARGS__),                               \
                     __HT_REFL_INS_PROPERTY_NAME_ACTION, __HT_REFL_SEP_COMMA, \
                     cls, __VA_ARGS__)};                                      \
    }                                                                         \
    static constexpr auto property_ref() {                                    \
      return std::make_tuple(HT_FOR(HT_COUNT_ARG(__VA_ARGS__),                \
                                    __HT_REFL_INS_PROPERTY_REF_ACTION,        \
                                    __HT_REFL_SEP_COMMA, cls, __VA_ARGS__));  \
    }                                                                         \
  };
