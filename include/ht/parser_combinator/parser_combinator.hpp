// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include "ht/parser_combinator/impl/commons/combinator_converter.hpp"
#include "ht/parser_combinator/impl/commons/combinator_many.hpp"
#include "ht/parser_combinator/impl/commons/combinator_option.hpp"
#include "ht/parser_combinator/impl/commons/combinator_or.hpp"
#include "ht/parser_combinator/impl/commons/combinator_plus.hpp"
#include "ht/parser_combinator/impl/commons/char_predict.hpp"
#include "ht/parser_combinator/impl/commons/strings.hpp"
#include "ht/parser_combinator/impl/input_stream.hpp"
#include "ht/parser_combinator/impl/parser.hpp"

namespace ht::parser_combinator {

using input_stream = _parser_combinator_impl::input_stream;

}  // namespace ht::parser_combinator
