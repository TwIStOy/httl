// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/un.h>

#include <cstddef>
#include <cstdint>

#include <fmt/format.h>
#include <ht/functional/hash.hpp>
#include <ht/network/impl/types/common.hpp>
#include <ht/strings/stringify.hpp>

namespace ht::net {

class ip4_address {
 public:
  explicit ip4_address(host_ordered_ip4 ip = 0, host_ordered_port port = 0)
      : ip_(ip), port_(port) {
  }

  ip4_address(const ip4_address&) = default;
  ip4_address(ip4_address&&)      = default;

  explicit ip4_address(const sockaddr_in& addr)
      : ip_(ntohl(addr.sin_addr.s_addr)), port_(ntohs(addr.sin_port)) {
  }

  explicit inline operator sockaddr_in() const {
    sockaddr_in addr{};

    addr.sin_family      = AF_INET;
    addr.sin_port        = htons(port_.value());
    addr.sin_addr.s_addr = htonl(ip_.value());

    return addr;
  }

  friend inline auto tag_invoke(tag_t<stringify>, const ip4_address& addr,
                                uint16_t, int16_t) {
    sockaddr_in _addr{};
    _addr.sin_addr.s_addr = htonl(addr.ip_.value());

    return fmt::format("{}:{}", inet_ntoa(_addr.sin_addr), addr.port_.value());
  }

  [[nodiscard]] inline auto ip() const {
    return ip_;
  }

  [[nodiscard]] inline auto port() const {
    return port_;
  }

  inline void set_ip(host_ordered_ip4 ip) {
    ip_ = ip;
  }

  inline void set_port(host_ordered_port port) {
    port_ = port;
  }

  auto operator<=>(const ip4_address& rhs) const = default;

 private:
  host_ordered_ip4 ip_;
  host_ordered_port port_;
};

struct ip4_address_hasher {
  inline std::size_t operator()(const ip4_address& addr) const noexcept {
    std::size_t seed;
    _ht_hash_internal::hash_combine(&seed, addr.ip());
    _ht_hash_internal::hash_combine(&seed, addr.port());
    return seed;
  }
};

}  // namespace ht::net

// vim: et sw=2 ts=2
