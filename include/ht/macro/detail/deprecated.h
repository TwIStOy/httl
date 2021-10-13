// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include "ht/macro/detail/compiler.h"
#include "ht/macro/detail/diagnostic.h"
#include "ht/macro/detail/warning.h"

#if defined(IGNORE_DEPRCATED_START)
#undef IGNORE_DEPRCATED_START
#endif
#if defined(IGNORE_DEPRCATED_END)
#undef IGNORE_DEPRCATED_END
#endif

#if defined(__clang__)
// clang
#define IGNORE_DEPRCATED_START                          \
  DIAGNOSTIC_PUSH;                                      \
  _Pragma("clang diagnostic ignored \"-Wdeprecated\""); \
  DIAGNOSTIC_PUSH;                                      \
  _Pragma("clang diagnostic ignored \"-Wdeprecated-declarations\"");
#elif GNUC_VERSION_GE(4, 3, 0)
#define IGNORE_DEPRCATED_START                        \
  DIAGNOSTIC_PUSH;                                    \
  _Pragma("GCC diagnostic ignored \"-Wdeprecated\""); \
  DIAGNOSTIC_PUSH;                                    \
  _Pragma("GCC diagnostic ignored \"-Wdeprecated-declarations\"");
#elif MSVC_VERSION_GE(15, 0, 0)
#define IGNORE_DEPRCATED_START       \
  __pragma(warning(disable : 4996)); \
  __pragma(warning(disable : 4995));
#else
#define IGNORE_DEPRCATED_START
#endif

#if defined(__clang__) || GNUC_VERSION_GE(4, 3, 0)
#define IGNORE_DEPRCATED_END \
  DIAGNOSTIC_POP;            \
  DIAGNOSTIC_POP;
#elif MSVC_VERSION_GE(15, 0, 0)
#define IGNORE_DEPRCATED_END        \
  __pragma(warning(enable : 4996)); \
  __pragma(warning(enable : 4995));
#else
#define DIAGNOSTIC_DISABLE_DEPRCATED
#endif

#if defined(DEPRECATED)
#undef DEPRECATED
#endif
#if defined(DEPRECATED_NO_MSG)
#undef DEPRECATED_NO_MSG
#endif

#ifndef COMPILER_RELAX_CHECK
// msvc
#if !defined(DEPRECATED) && defined(MSVC_VERSION)
#if MSVC_VERSION_GE(14, 0, 0)
#define DEPRECATED(msg)   __declspec(deprecated(msg))
#define DEPRECATED_NO_MSG __declspec(deprecated)
#else
// MSVC 7.1 only supports the attribute without a message
#define DEPRECATED(msg)
#define DEPRECATED_NO_MSG __declspec(deprecated)
#endif
#endif

#if !defined(DEPRECATED) && __cplusplus >= 201402L
// after C++14, attribute deprecated should be supported
#define DEPRECATED(msg) [[deprecated(msg)]]
// NOLINTNEXTLINE
#define DEPRECATED_NO_MSG [[deprecated]]
#endif

#if !defined(DEPRECATED) && defined(GNUC_VERSION)
// gcc since 4.5 supports deprecated attribute with a message; older versions
// only support the attribute without a message.
#if GNUC_VERSION_GE(4, 5, 0)
#define DEPRECATED(msg)   __attribute__((deprecated(msg)))
#define DEPRECATED_NO_MSG __attribute__((deprecated))
#else
#define DEPRECATED(msg)
#define DEPRECATED_NO_MSG __attribute__((deprecated))
#endif
#endif
#else
// relax mode
#define DEPRECATED(msg)
#define DEPRECATED_NO_MSG
#endif
