// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include <memory>
#include <type_traits>
#include <vector>

#include <sdt/core/trait/impl/value.hh>

namespace sdt::core::trait {

template<class I>
concept LegacyIterator = requires(I i) {
  { *i } -> Referenceable;
  { ++i } -> std::same_as<I&>;
  { *i++ } -> Referenceable;
} && std::copyable<I>;

template<class I>
concept LegacyInputIterator =
    LegacyIterator<I> && std::equality_comparable<I> && requires(I i) {
      typename std::incrementable_traits<I>::difference_type;
      typename std::indirectly_readable_traits<I>::value_type;
      typename std::common_reference_t<
          std::iter_reference_t<I>&&,
          typename std::indirectly_readable_traits<I>::value_type&>;
      *i++;
      typename std::common_reference_t<
          decltype(*i++)&&,
          typename std::indirectly_readable_traits<I>::value_type&>;
      requires std::signed_integral<
          typename std::incrementable_traits<I>::difference_type>;
    };

template<class It>
concept LegacyForwardIterator =
    LegacyInputIterator<It> && std::constructible_from<It> &&
    std::is_reference_v<std::iter_reference_t<It>> &&
    std::same_as<std::remove_cvref_t<std::iter_reference_t<It>>,
                 typename std::indirectly_readable_traits<It>::value_type> &&
    requires(It it) {
      { it++ } -> std::convertible_to<const It&>;
      { *it++ } -> std::same_as<std::iter_reference_t<It>>;
    };

}  // namespace sdt::core::trait
