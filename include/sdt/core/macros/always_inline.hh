// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#if __GNUC__ || __clang__
#define SDT_ALWAYS_INLINE [[gnu::always_inline]] inline
#else
#define SDT_ALWAYS_INLINE inline __forceinline
#endif
