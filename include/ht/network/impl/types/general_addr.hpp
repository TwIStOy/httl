// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include <algorithm>
#include <string>
#include <utility>

#include <ht/core/box.hpp>
#include <ht/network/impl/types/ip4_addr.hpp>
#include <ht/network/impl/types/ip6_addr.hpp>
#include "ht/network/impl/types/unix_addr.hpp"

namespace ht::net {

class general_address {
 public:
  enum class address_type {
    kIp4,
    kIp6,
    kUnix,
  };

  inline explicit general_address(ip4_address addr) {
    type_ = address_type::kIp4;
    construct_union_member(&ip4_, std::move(addr));
  }

  inline explicit general_address(ip6_address addr) {
    type_ = address_type::kIp6;
    construct_union_member(&ip6_, std::move(addr));
  }

  inline explicit general_address(unix_address addr) {
    type_ = address_type::kUnix;
    construct_union_member(&unix_, std::move(addr));
  }

  general_address(const general_address&) = default;

  general_address(general_address&&) = default;

  ~general_address() {
    switch (type_) {
      case general_address::address_type::kIp4:
        destruct_union_member(&ip4_);
        break;
      case general_address::address_type::kIp6:
        destruct_union_member(&ip6_);
        break;
      case general_address::address_type::kUnix:
        destruct_union_member(&unix_);
        break;
    }
  }

  [[nodiscard]] address_type get_type() const {
    return type_;
  }

  [[nodiscard]] ip4_address as_ip4() const {
    return ip4_.get();
  }

  [[nodiscard]] ip6_address as_ip6() const {
    return ip6_.get();
  }

  [[nodiscard]] unix_address as_unix() const {
    return unix_.get();
  }

  friend inline auto tag_invoke(tag_t<stringify>, const general_address& addr,
                                uint16_t, int16_t) {
    switch (addr.type_) {
      case general_address::address_type::kIp4:
        return stringify(addr.ip4_.get());
      case general_address::address_type::kIp6:
        return stringify(addr.ip6_.get());
      case general_address::address_type::kUnix:
        return stringify(addr.unix_.get());
    }
    return std::string("");
  }

 private:
  address_type type_;
  union {
    box<ip4_address> ip4_;
    box<ip6_address> ip6_;
    box<unix_address> unix_;
  };
};

}  // namespace ht::net

// vim: et sw=2 ts=2
