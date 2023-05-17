// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include <type_traits>

namespace sdt::core::trait {

/// The `Send` trait indicates that a value of this type is safe to send from
/// one thread to another.
template<typename T>
concept Send = false;

namespace mark {
/// Specialize this template to mark that the type satisfied trait `Send`.
template<typename T>
struct impl_send : std::false_type {};
}  // namespace mark

}  // namespace sdt::core::trait
