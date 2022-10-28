// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include <arpa/inet.h>
#include <netinet/in.h>

#include <cstring>

#include <fmt/format.h>
#include <ht/functional/hash.hpp>
#include <ht/network/impl/types/common.hpp>
#include <ht/strings/stringify.hpp>

namespace ht::net {

class ip6_address {
 public:
  inline static ip6_address any() {
    static const ip6_address any(in6addr_any, 0);
    return any;
  }

  inline static ip6_address loopback() {
    static const ip6_address loopback(in6addr_loopback, 0);
    return loopback;
  }

  inline ip6_address() {
    ip6_ = IN6ADDR_LOOPBACK_INIT;
  }

  ip6_address(const ip6_address&) = default;
  ip6_address(ip6_address&&)      = default;

  explicit ip6_address(const sockaddr_in6& address)
      : ip6_(address.sin6_addr),
        scope_id_(address.sin6_scope_id),
        port_(ntohs(address.sin6_port)) {
  }

  ip6_address(const struct in6_addr& ip6, host_ordered_port port,
              uint32_t scope_id = 0)
      : ip6_(ip6), scope_id_(scope_id), port_(port) {
  }

  inline explicit operator sockaddr_in6() const {
    sockaddr_in6 addr{};
    ::memset(&addr, 0, sizeof(addr));

    addr.sin6_family   = AF_INET6;
    addr.sin6_addr     = ip6_;
    addr.sin6_scope_id = scope_id_;
    addr.sin6_port     = port_.value();

    return addr;
  }

  [[nodiscard]] inline const auto& ip() const {
    return ip6_;
  }

  [[nodiscard]] inline auto port() const {
    return port_;
  }

  [[nodiscard]] inline auto scope_id() const {
    return scope_id_;
  }

  friend inline auto tag_invoke(tag_t<stringify>, const ip6_address& addr,
                                uint16_t, int16_t) {
    char buf[128];
    inet_ntop(AF_INET6, &addr.ip6_, buf + 1, sizeof(buf));
    return fmt::format("[{}]:{}", buf, addr.port_.value());
  }

  inline bool operator==(const ip6_address& rhs) const noexcept {
    auto *left  = reinterpret_cast<const uint64_t *>(ip6_.s6_addr32);
    auto *right = reinterpret_cast<const uint64_t *>(rhs.ip6_.s6_addr32);
    return left[0] == right[0] && left[1] == right[1] &&
           scope_id_ == rhs.scope_id_ && port_.value() == rhs.port_.value();
  }

  inline bool operator<(const ip6_address& rhs) const noexcept {
    auto *left  = reinterpret_cast<const uint64_t *>(ip6_.s6_addr32);
    auto *right = reinterpret_cast<const uint64_t *>(rhs.ip6_.s6_addr32);

    if (left[0] != right[0]) {
      return left[0] < right[0];
    }

    if (left[1] != right[1]) {
      return left[1] < right[1];
    }

    if (port_.value() != rhs.port_.value()) {
      return port_.value() < rhs.port_.value();
    }

    return scope_id_ < rhs.scope_id_;
  }

 private:
  in6_addr ip6_{};
  uint32_t scope_id_{0};
  host_ordered_port port_;
};

struct ip6_address_hasher {
  inline std::size_t operator()(const ip6_address& addr) const noexcept {
    auto *buf = reinterpret_cast<const uint64_t *>(addr.ip().s6_addr32);

    std::size_t seed;
    _ht_hash_internal::hash_combine(&seed, buf[0]);
    _ht_hash_internal::hash_combine(&seed, buf[1]);
    _ht_hash_internal::hash_combine(&seed, addr.port());
    _ht_hash_internal::hash_combine(&seed, addr.scope_id());
    return seed;
  }
};

}  // namespace ht::net
