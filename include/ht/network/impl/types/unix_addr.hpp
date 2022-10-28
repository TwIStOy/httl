// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include <netinet/in.h>
#include <sys/un.h>
#include <unistd.h>

#include <cstddef>
#include <string>

#include <ht/functional/hash.hpp>
#include <ht/network/impl/types/common.hpp>
#include <ht/strings/stringify.hpp>

namespace ht::net {

class unix_address {
 public:
  explicit unix_address(std::string p) : path_(std::move(p)) {
  }

  explicit unix_address(const sockaddr_un& addr, socklen_t ss_len = 0) {
    constexpr auto offset = offsetof(struct sockaddr_un, sun_path);
    if (ss_len > offset) {
      path_ = std::string(addr.sun_path, ss_len - offset - 1);
    } else {
      path_ = std::string(addr.sun_path);
    }
  }

  ~unix_address() = default;

  [[nodiscard]] inline const auto& path() const {
    return path_;
  }

  friend inline auto tag_invoke(tag_t<stringify>, const unix_address& addr,
                                uint16_t, int16_t) {
    return addr.path_;
  }

  auto operator<=>(const unix_address&) const noexcept = default;

 private:
  std::string path_;
};

struct unix_address_hasher {
  inline auto operator()(const unix_address& addr) const noexcept {
    return std::hash<std::string>{}(addr.path());
  }
};

}  // namespace ht::net

// vim: et sw=2 ts=2
