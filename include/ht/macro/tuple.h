// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include "ht/macro/expand.hpp"
#include "ht/macro/select.h"

/**
 * HT_IS_TUPLE(a, b, c) 0
 * HT_IS_TUPLE((a, b, c)) 1
 */
#define HT_IS_TUPLE(...) _HT_IS_TUPLE_I(_HT_IS_TUPLE_HELPER __VA_ARGS__)

/**
 * HT_TUPLE_TO_VARS((1, 2, 3)) 1, 2, 3
 */
#define HT_TUPLE_TO_VARS(tuple) HT_EXPAND(_HT_TUPLE_TO_VARS() tuple)

// impl {{{
#define _HT_TUPLE_TO_VARS()      _HT_TUPLE_TO_VARS_I
#define _HT_TUPLE_TO_VARS_I(...) __VA_ARGS__

#define _HT_IS_TUPLE_I(tester, ...) \
  HT_EXPAND(HT_SELECT(1, HT_UNDERLIND_CONCAT(_HT_IS_TUPLE_DEF, tester)))
#define _HT_IS_TUPLE_HELPER(...)             1
#define _HT_IS_TUPLE_DEF_1                   1, PP_EMPTY
#define _HT_IS_TUPLE_DEF__HT_IS_TUPLE_HELPER 0, PP_EMPTY
// }}}

// vim: fdm=marker
