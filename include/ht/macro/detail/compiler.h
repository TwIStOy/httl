// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#define __VERSION_ENCODE(major, minor, patch) \
  (((major)*1000000) + ((minor)*1000) + (patch))

#if defined(GNUC_VERSION)
#undef GNUC_VERSION
#endif
#if defined(__GNUC__) && defined(__GNUC_PATCHLEVEL__)
#define GNUC_VERSION \
  __VERSION_ENCODE(__GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__)
#elif defined(__GNUC__)
#define GNUC_VERSION __VERSION_ENCODE(__GNUC__, __GNUC_MINOR__, 0)
#endif

#if defined(MSVC_VERSION)
#undef MSVC_VERSION
#endif
#if defined(_MSC_FULL_VER) && (_MSC_FULL_VER >= 140000000) && !defined(__ICL)
#define MSVC_VERSION                                    \
  __VERSION_ENCODE(_MSC_FULL_VER / 10000000,            \
                   (_MSC_FULL_VER % 10000000) / 100000, \
                   (_MSC_FULL_VER % 100000) / 100)
#elif defined(_MSC_FULL_VER) && !defined(__ICL)
#define MSVC_VERSION                                                           \
  __VERSION_ENCODE(_MSC_FULL_VER / 1000000, (_MSC_FULL_VER % 1000000) / 10000, \
                   (_MSC_FULL_VER % 10000) / 10)
#elif defined(_MSC_VER) && !defined(__ICL)
#define MSVC_VERSION __VERSION_ENCODE(_MSC_VER / 100, _MSC_VER % 100, 0)
#endif

#if defined(GNUC_VERSION_GE)
#undef GNUC_VERSION_GE
#endif
#if defined(GNUC_VERSION)
#define GNUC_VERSION_GE(major, minor, patch) \
  (GNUC_VERSION >= __VERSION_ENCODE(major, minor, patch))
#else
#define GNUC_VERSION_GE(major, minor, patch) (0)
#endif

#define MSVC_VERSION_GE(major, minor, patch)
#if defined(MSVC_VERSION_GE)
#undef MSVC_VERSION_GE
#endif
#if !defined(MSVC_VERSION)
#define MSVC_VERSION_GE(major, minor, patch) (0)
#elif defined(_MSC_VER) && (_MSC_VER >= 1400)
#define MSVC_VERSION_GE(major, minor, patch) \
  (_MSC_FULL_VER >= ((major * 10000000) + (minor * 100000) + (patch)))
#elif defined(_MSC_VER) && (_MSC_VER >= 1200)
#define MSVC_VERSION_GE(major, minor, patch) \
  (_MSC_FULL_VER >= ((major * 1000000) + (minor * 10000) + (patch)))
#else
#define MSVC_VERSION_GE(major, minor, patch) \
  (_MSC_VER >= ((major * 100) + (minor)))
#endif

