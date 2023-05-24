// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include <cstdint>
#include <limits>

namespace sdt::core::trait::helpers {

template<typename T0, typename T1>
inline constexpr bool LargeEnough_v =
    std::numeric_limits<T1>::max() >= std::numeric_limits<T0>::max();

template<typename T0, typename T1>
concept LargeEnough = LargeEnough_v<T0, T1>;

}  // namespace sdt::core::trait::helpers
