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

namespace ht {

struct Socket {
  Socket(int fd, void *io_context);

  int fd{-1};
  void *io_context{nullptr};

  HT_REFL_INS_DECL(Socket, fd, io_context);

 private:
  void free();
};

HT_ALWAYS_INLINE void Socket::free() {
  if (fd > 0) {
    ::close(fd);
  }
}

}  // namespace ht

namespace fmt {

template<>
struct formatter<ht::Socket> {
  using ValueType = ht::Socket;
  template<typename ParseContext>
  auto parse(ParseContext &ctx) ->  // NOLINT(runtime/references)
      typename ParseContext::iterator {
    return ctx.begin();
  }

  template<typename FormatContext>
  auto format(const ValueType &v,
              FormatContext &ctx)  // NOLINT(runtime/references)
      -> decltype(ctx.out()) {
    return format_to(ctx.out(), "Socket{{fd = {}, io_context = {:p}}}", v.fd,
                     v.io_context);
  }
};

}  // namespace fmt

// vim: et sw=2 ts=2
