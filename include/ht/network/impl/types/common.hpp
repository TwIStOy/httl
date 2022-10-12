// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include <ht/container/named_wrapper.hpp>

namespace ht {

using host_ordered_ip4 = named_wrapper<uint32_t, struct host_ordered_ip4_tag,
                                       named_wrapper_skills::hashable,
                                       named_wrapper_skills::comparable>;

using host_ordered_port = named_wrapper<uint16_t, struct host_ordered_port_tag,
                                        named_wrapper_skills::hashable,
                                        named_wrapper_skills::comparable>;

}  // namespace ht

// vim: et sw=2 ts=2
