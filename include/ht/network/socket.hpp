// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include <fmt/format.h>

#include "ht/core/cpp_feature.h"
#include "ht/core/reflect/macros.h"
#include "ht/strings/stringify.hpp"

namespace ht {

struct socket {
  HT_ALWAYS_INLINE socket(int _fd, void *_io_context)
      : fd_(_fd), io_context_(_io_context) {
  }

  socket(const socket &) = delete;

  socket(socket &&rhs) noexcept : fd_(rhs.fd_), io_context_(rhs.io_context_) {
    rhs.fd_ = -1;
  }

  HT_ALWAYS_INLINE ~socket() {
    free();
  }

  HT_ALWAYS_INLINE friend auto tag_invoke(ht::tag_t<ht::debug_stringify>,
                                          const socket &skt, uint16_t,
                                          uint16_t) {
    return fmt::format("Socket{{fd = {}, io_context = {:p}}}", skt.fd_,
                       skt.io_context_);
  }

  [[nodiscard]] HT_ALWAYS_INLINE int fd() const {
    return fd_;
  }

  [[nodiscard]] HT_ALWAYS_INLINE void *io_context() const {
    return io_context_;
  }

 private:
  void free();

  int fd_{-1};
  void *io_context_{nullptr};
};

HT_ALWAYS_INLINE void socket::free() {
  if (fd_ > 0) {
    ::close(fd_);
  }
  fd_ = -1;
}

}  // namespace ht

// vim: et sw=2 ts=2
