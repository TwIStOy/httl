// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include <fcntl.h>
#include <linux/tcp.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include <string>

#include <ht/core/result.hpp>
#include <ht/network/socket.hpp>

namespace ht {

inline result<void, std::string> netutil_set_non_blocking(int fd) {
  int flags = fcntl(fd, F_GETFL, 0);
  if (flags < 0) {
    return err(strerror(errno));
  }
  if (fcntl(fd, F_SETFL, flags | O_NONBLOCK) < 0) {
    return err(strerror(errno));
  }
  return ok();
}

inline result<void, std::string> netutil_set_reuse_addr(int fd) {
  int v = 1;
  if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &v, sizeof(int)) < 0) {
    return err(strerror(errno));
  }
  return ok();
}

inline result<void, std::string> netutil_set_reuse_port(int fd) {
  int v = 1;
  if (setsockopt(fd, SOL_SOCKET, SO_REUSEPORT, &v, sizeof(int)) < 0) {
    return err(strerror(errno));
  }
  return ok();
}

inline result<void, std::string> netutil_set_tcp_fastopen(int fd) {
  int v = 5;
  if (setsockopt(fd, IPPROTO_TCP, TCP_FASTOPEN, &v, sizeof(int)) < 0) {
    return err(strerror(errno));
  }
  return ok();
}

inline result<void, std::string> netutil_set_ip4_transparent(int fd) {
  int v = 1;
  if (setsockopt(fd, IPPROTO_TCP, IP_TRANSPARENT, &v, sizeof(v)) < 0) {
    return err(strerror(errno));
  }
  return ok();
}

}  // namespace ht

// vim: et sw=2 ts=2
