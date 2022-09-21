// Copyright (c) 2020 - present, Hawtian Wang (twistoy.wang@gmail.com)
//

#pragma once  // NOLINT(build/header_guard)

#include <concepts>
#include <memory>
#include <span>
#include <stdexcept>
#include <tuple>
#include <type_traits>
#include <utility>

#include "ht/core/type_utils.hpp"

namespace ht {

template<typename Ch, std::size_t E, typename... Ts>
  requires((std::is_standard_layout_v<Ts> && std::is_trivial_v<Ts>) && ...)
struct memory_view {
  using layers_pack_t =
      std::conditional_t<std::is_same_v<Ch, std::remove_const_t<Ch>>,
                         std::tuple<Ts...>,
                         std::tuple<std::add_const_t<Ts>...>>;
  using span_t = std::span<Ch, E>;
  using raw_ptr_t =
      std::conditional_t<std::is_same_v<Ch, std::remove_const_t<Ch>>, char *,
                         const char *>;

  static constexpr std::size_t expect_size_v = (sizeof(Ts) + ...);

  explicit memory_view(span_t span) : data_(span) {
    if (span.size_bytes() < expect_size_v) {
      throw std::runtime_error("span is not long enough");
    }
  }

  memory_view()                        = delete;
  memory_view(const memory_view &)     = default;
  memory_view(memory_view &&) noexcept = default;

  template<std::size_t I>
    requires(I <= std::tuple_size_v<layers_pack_t>)
  auto layer() const noexcept {
    auto ptr      = reinterpret_cast<raw_ptr_t>(data_.data());
    using offset  = typename ht::tuple_slice<I, Ts...>::first;
    using layer_t = std::tuple_element_t<I, layers_pack_t>;
    return reinterpret_cast<layer_t *>(ptr + ht::tuple_size_bytes_v<offset>);
  }

  static auto create_buffer() {
    return std::make_unique<char>(expect_size_v);
  }

  span_t data_;
};

template<typename... Ts, typename Ch, std::size_t Extent>
auto view_as(std::span<Ch, Extent> span) {
  using view_t = memory_view<Ch, Extent, Ts...>;
  if (span.size_bytes() < view_t::expect_size_v) {
    throw std::runtime_error("span is not long enough");
  }
  return view_t{span};
}

}  // namespace ht
