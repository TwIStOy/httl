// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include <ht/macro/select.h>
#include <ht/macro/expand.hpp>

/**
 * IsEmpty
 */
// NOLINTNEXTLINE
#define HT_IS_EMPTY(...) _HT_IS_EMPTY_I(_HT_IS_EMPTY_HELPER __VA_ARGS__(), )

#define _HT_IS_EMPTY_I(test, ...) \
  HT_EXPAND(HT_SELECT(1, HT_UNDERLIND_CONCAT(_HT_IS_EMPTY_DEF, test)))

#define _HT_IS_EMPTY_HELPER()                1
#define _HT_IS_EMPTY_DEF_1                   1, HT_EMPTY
#define _HT_IS_EMPTY_DEF__HT_IS_EMPTY_HELPER 0, HT_EMPTY
