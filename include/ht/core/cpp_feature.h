// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#include <type_traits>
#include <utility>

#if __GNUC__ || __clang__
#define HT_ALWAYS_INLINE [[gnu::always_inline]] inline
#else
#define HT_ALWAYS_INLINE inline
#endif

#if __GNUC__ || __clang__
#define HT_COLD [[gnu::cold]]
#else
#define HT_COLD
#endif

#define HT_FORWARD(value) std::forward<decltype(value)>(value)
#define HT_TYPE(value)    std::remove_cvref_t<decltype(value)>

