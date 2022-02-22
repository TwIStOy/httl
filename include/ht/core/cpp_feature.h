// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#if __GNUC__
#define HT_ALWAYS_INLINE [[gnu::always_inline]] inline
#else
#define HT_ALWAYS_INLINE inline __attribute__((always_inline))
#endif
