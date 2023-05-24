// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include <array>
#include <concepts>
#include <deque>
#include <forward_list>
#include <initializer_list>
#include <iterator>
#include <limits>
#include <list>
#include <map>
#include <memory>
#include <set>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
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

template<typename T>
struct is_forward_list : std::false_type {};

template<typename T, typename A>
struct is_forward_list<std::forward_list<T, A>> : std::true_type {};

template<typename T>
concept expect_size = requires(T a) {
  { a.size() } -> std::same_as<typename T::size_type>;
};

template<typename T>
struct expect_size_t : std::bool_constant<expect_size<T>> {};

}  // namespace details

/// A Container is an object used to store other objects and taking care of the
/// management of the memory used by the objects it contains.
template<typename C>
concept Container = requires(C a, C b, C&& rv, const C& cv) {
  typename C::value_type;
  requires std::is_copy_constructible_v<typename C::value_type>;
  requires Erasable<typename C::value_type, C>;

  typename C::reference;

  typename C::const_reference;

  typename C::iterator;
  requires LegacyForwardIterator<typename C::iterator>;

  typename C::const_iterator;
  requires LegacyForwardIterator<typename C::const_iterator>;

  typename C::difference_type;
  // must be the same as iterator_traits::difference_type for iterator and
  // const_iterator
  requires std::same_as<
      typename C::difference_type,
      typename std::iterator_traits<typename C::iterator>::difference_type>;

  typename C::size_type;
  // large enough to represent all positive values of difference_type
  requires helpers::LargeEnough<typename C::difference_type,
                                typename C::size_type>;

  requires std::is_default_constructible_v<C>;
  requires std::conditional_t<
      std::is_move_constructible_v<typename C::value_type>,
      std::is_move_constructible<C>, std::true_type>::value;
  requires std::conditional_t<CopyInsertable<typename C::value_type, C>,
                              std::is_copy_constructible<C>,
                              std::true_type>::value;
  { a = b } -> std::same_as<C&>;
  { a = rv } -> std::same_as<C&>;
  requires std::is_destructible_v<C>;

  { a.begin() } -> std::same_as<typename C::iterator>;
  { a.end() } -> std::same_as<typename C::iterator>;
  { cv.begin() } -> std::same_as<typename C::const_iterator>;
  { cv.end() } -> std::same_as<typename C::const_iterator>;
  { a.cbegin() } -> std::same_as<typename C::const_iterator>;
  { a.cend() } -> std::same_as<typename C::const_iterator>;

  { a == b } -> std::convertible_to<bool>;
  { a != b } -> std::convertible_to<bool>;

  { a.swap(b) } -> std::same_as<void>;
  { swap(a, b) } -> std::same_as<void>;

  requires std::conditional_t<details::is_forward_list<C>::value,
                              std::true_type, details::expect_size_t<C>>::value;

  { a.max_size() } -> std::same_as<typename C::size_type>;
  { a.empty() } -> std::convertible_to<bool>;
};

// A ReversibleContainer is a Container that has iterators that meet the
// requirements of either LegacyBidirectionalIterator or
// LegacyRandomAccessIterator. Such iterators allow a ReversibleContainer to be
// iterated over in reverse.
template<typename C>
concept ReversibleContainer = Container<C> && requires(C a) {
  typename C::reverse_iterator;
  typename C::const_reverse_iterator;

  requires(LegacyBidirectionalIterator<typename C::iterator> ||
           LegacyRandomAccessIterator<typename C::iterator>);

  { a.rbegin() } -> std::same_as<typename C::reverse_iterator>;
  { a.rend() } -> std::same_as<typename C::reverse_iterator>;
  { a.crbegin() } -> std::same_as<typename C::const_reverse_iterator>;
  { a.crend() } -> std::same_as<typename C::const_reverse_iterator>;
};

/// An AllocatorAwareContainer is a Container that holds an instance of an
/// Allocator and uses that instance in all its member functions to allocate and
/// deallocate memory and to construct and destroy objects in that memory (such
/// objects may be container elements, nodes, or, for unordered containers,
/// bucket arrays), except that std::basic_string specializations do not use the
/// allocators for construction/destruction of their elements (since C++23).
template<typename C>
concept AllocatorAwareContainer = Container<C> && requires(C a) {
  typename C::allocator_type;
  requires std::same_as<typename C::allocator_type::value_type,
                        typename C::value_type>;

  { a.get_allocator() } -> std::same_as<typename C::allocator_type>;
};

template<typename C, typename T = typename C::value_type,
         typename A = typename details::allocator_type<C>::type>
concept SequenceContainer =
    Container<C> && requires(C&& a, C::value_type n, T& t, C::iterator i,
                             C::iterator j, std::initializer_list<T> il) {
      { C(n, t) };
      { C(i, j) };
      { C(il) };
      { a = il } -> std::same_as<C&>;
    };

static_assert(ReversibleContainer<std::array<int, 10>>);
static_assert(ReversibleContainer<std::deque<int>>);
static_assert(ReversibleContainer<std::list<int>>);
static_assert(ReversibleContainer<std::vector<int>>);
static_assert(ReversibleContainer<std::map<int, int>>);
static_assert(ReversibleContainer<std::multimap<int, int>>);
static_assert(ReversibleContainer<std::set<int>>);
static_assert(ReversibleContainer<std::multiset<int>>);

static_assert(AllocatorAwareContainer<std::string>);
static_assert(AllocatorAwareContainer<std::deque<int>>);
static_assert(AllocatorAwareContainer<std::list<int>>);
static_assert(AllocatorAwareContainer<std::forward_list<int>>);
static_assert(AllocatorAwareContainer<std::vector<int>>);
static_assert(AllocatorAwareContainer<std::map<int, int>>);
static_assert(AllocatorAwareContainer<std::multimap<int, int>>);
static_assert(AllocatorAwareContainer<std::set<int>>);
static_assert(AllocatorAwareContainer<std::multiset<int>>);
static_assert(AllocatorAwareContainer<std::unordered_map<int, int>>);
static_assert(AllocatorAwareContainer<std::unordered_multimap<int, int>>);
static_assert(AllocatorAwareContainer<std::unordered_set<int>>);
static_assert(AllocatorAwareContainer<std::unordered_multiset<int>>);

static_assert(SequenceContainer<std::vector<int>>);
static_assert(SequenceContainer<std::array<int, 10>>);

}  // namespace sdt::core::trait
