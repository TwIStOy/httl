// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#include <type_traits>
#include <utility>

#if __GNUC__
#define HT_ALWAYS_INLINE [[gnu::always_inline]] inline
#else
#define HT_ALWAYS_INLINE inline __attribute__((always_inline))
#endif

#define HT_FORWARD(value) std::forward<decltype(value)>(value)
#define HT_TYPE(value)    std::remove_cvref_t<decltype(value)>
