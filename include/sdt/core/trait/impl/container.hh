// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include <concepts>
#include <iterator>
#include <limits>
#include <memory>
#include <type_traits>
#include <vector>

#include <sdt/core/trait/impl/copy_insertable.hh>
#include <sdt/core/trait/impl/erasable.hh>
#include <sdt/core/trait/impl/helpers.hh>
#include <sdt/core/trait/impl/iter_traits.hh>

namespace sdt::core::trait {

namespace details {

template<typename T, typename = void>
struct allocator_type {
  using type = std::allocator<typename T::value_type>;
};

template<typename T>
struct allocator_type<T, std::void_t<typename T::allocator_type>> {
  using type = typename T::allocator_type;
};

}  // namespace details

/// A Container is an object used to store other objects and taking care of the
/// management of the memory used by the objects it contains.
template<typename C>
concept container = requires(C a, C b, C&& rv) {
  typename C::value_type;
  std::is_copy_constructible_v<typename C::value_type>;
  Erasable<typename C::value_type, C>;

  typename C::reference;

  typename C::const_reference;

  typename C::iterator;
  LegacyForwardIterator<typename C::iterator>;

  typename C::const_iterator;
  LegacyForwardIterator<typename C::const_iterator>;

  typename C::difference_type;
  // must be the same as iterator_traits::difference_type for iterator and
  // const_iterator
  std::same_as<
      typename C::difference_type,
      typename std::iterator_traits<typename C::iterator>::difference_type>;

  typename C::size_type;
  // large enough to represent all positive values of difference_type
  helpers::LargeEnough<typename C::difference_type, typename C::size_type>;

  std::is_default_constructible_v<C>;
  std::conditional_t<std::is_move_constructible_v<typename C::value_type>,
                     std::is_move_constructible<C>, std::true_type>::value;
  std::conditional_t<CopyInsertable<typename C::value_type, C>,
                     std::is_copy_constructible<C>, std::true_type>::value;
  { a = b } -> std::same_as<C&>;
  { a = rv } -> std::same_as<C&>;
  std::is_destructible_v<C>;
};

static_assert(container<std::vector<int>>, "vector should be a container");

}  // namespace sdt::core::trait
