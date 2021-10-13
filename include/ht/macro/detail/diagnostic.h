// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include "ht/macro/detail/compiler.h"

#if defined(DIAGNOSTIC_PUSH)
#undef DIAGNOSTIC_PUSH
#endif
#if defined(DIAGNOSTIC_POP)
#undef DIAGNOSTIC_POP
#endif
#if defined(__clang__)
// clang
#define DIAGNOSTIC_PUSH _Pragma("clang diagnostic push")
#define DIAGNOSTIC_POP  _Pragma("clang diagnostic pop")
#elif GNUC_VERSION_GE(4, 6, 0)
#define DIAGNOSTIC_PUSH _Pragma("GCC diagnostic push")
#define DIAGNOSTIC_POP  _Pragma("GCC diagnostic pop")
#elif MSVC_VERSION_GE(15, 0, 0)
#define DIAGNOSTIC_PUSH __pragma(warning(push))
#define DIAGNOSTIC_POP  __pragma(warning(pop))
#else
#define DIAGNOSTIC_PUSH
#define DIAGNOSTIC_POP
#endif
