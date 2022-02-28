// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include <string>

#include "ht/core/result.hpp"

namespace ht {

Result<void, std::string> netutil_set_non_blocking(int fd);

Result<void, std::string> netutil_set_reuse_addr(int fd);

Result<void, std::string> netutil_set_reuse_port(int fd);

Result<void, std::string> netutil_set_tcp_fastopen(int fd);

Result<void, std::string> netutil_set_ip4_transparent(int fd);

}  // namespace ht

// vim: et sw=2 ts=2
