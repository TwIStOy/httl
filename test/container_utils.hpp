// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include "container_traits.hpp"

namespace __ht_test {

// Compile-time typedef testing.
template<typename _Tp>
struct basic_types {
  using test_type       = _Tp;
  using value_type      = typename test_type::value_type;
  using pointer         = typename test_type::pointer;
  using const_pointer   = typename test_type::const_pointer;
  using reference       = typename test_type::reference;
  using const_reference = typename test_type::const_reference;
  using iterator        = typename test_type::iterator;
  using const_iterator  = typename test_type::const_iterator;
  using size_type       = typename test_type::size_type;
  using difference_type = typename test_type::difference_type;
};

template<typename _Tp>
struct reversible_types {
  using test_type              = _Tp;
  using reverse_iterator       = typename test_type::reverse_iterator;
  using const_reverse_iterator = typename test_type::const_reverse_iterator;
};

/*
 * template<typename _Tp>
 * struct conversion {
 *   using test_type      = _Tp;
 *   using iterator       = typename _Tp::iterator;
 *   using const_iterator = typename _Tp::const_iterator;
 *
 *   static void iterator_to_const_iterator() {
 *   }
 * };
 */

template<typename _Tp, bool = container_traits<_Tp>::is_allocator_aware>
struct allocator_aware_types {
  // _Alloc-aware requirements (table 82)
  using test_type      = _Tp;
  using allocator_type = typename test_type::allocator_type;
};

template<typename _Tp>
struct allocator_aware_types<_Tp, false>;

template<typename _Tp, bool = container_traits<_Tp>::is_associative>
struct associative_types {
  // Associative container requirements (table 85)
  using test_type     = _Tp;
  using key_type      = typename test_type::key_type;
  using key_compare   = typename test_type::key_compare;
  using value_compare = typename test_type::value_compare;
};

template<typename _Tp>
struct associative_types<_Tp, false> {};

template<typename _Tp, bool = container_traits<_Tp>::is_unordered>
struct unordered_types {
  // Unordered associative container requirements (table 87)
  using test_type            = _Tp;
  using key_type             = typename test_type::key_type;
  using hasher               = typename test_type::hasher;
  using key_equal            = typename test_type::key_equal;
  using local_iterator       = typename test_type::local_iterator;
  using const_local_iterator = typename test_type::const_local_iterator;
};

template<typename _Tp>
struct unordered_types<_Tp, false> {};

template<typename _Tp, bool = container_traits<_Tp>::is_mapped>
struct mapped_types {
  using test_type   = _Tp;
  using mapped_type = typename test_type::mapped_type;
};

template<typename _Tp>
struct mapped_types<_Tp, false> {};

template<typename _Tp, bool = container_traits<_Tp>::is_adaptor>
struct adaptor_types {
  // Container adaptor requirements.
  using test_type       = _Tp;
  using value_type      = typename test_type::value_type;
  using reference       = typename test_type::reference;
  using const_reference = typename test_type::const_reference;
  using size_type       = typename test_type::size_type;
  using container_type  = typename test_type::container_type;
};

template<typename _Tp>
struct adaptor_types<_Tp, false> {};

// Primary template.
template<typename _Tp>
struct types : basic_types<_Tp>,
               adaptor_types<_Tp>,
               reversible_types<_Tp>,
               allocator_aware_types<_Tp>,
               associative_types<_Tp>,
               unordered_types<_Tp>,
               mapped_types<_Tp> {};

// Run-time test for constant_iterator requirements.
template<typename _Tp, bool = container_traits<_Tp>::is_allocator_aware>
struct populate {
  populate(_Tp &container) {
    // Avoid uninitialized warnings, requires DefaultContructible.
    using value_type = typename _Tp::value_type;
    container.insert(container.begin(), value_type());
    container.insert(container.begin(), value_type());
  }
};

template<typename _Tp>
struct populate<_Tp, false> {
  populate(_Tp &container) {
  }
};

template<typename _Tp, bool = container_traits<_Tp>::is_reversible>
struct reverse_members {
  reverse_members(_Tp &container) {
    REQUIRE(container.crbegin() == container.rbegin());
    REQUIRE(container.crend() == container.rend());
    REQUIRE(container.crbegin() != container.crend());
  }
};

template<typename _Tp>
struct reverse_members<_Tp, false> {
  reverse_members(_Tp &) {
  }
};

/*
 * template<typename _Iterator, bool _Mutable,
 *          typename = typename
 * std::iterator_traits<_Iterator>::iterator_category> struct
 * iterator_concept_checks;
 *
 * template<typename _Tp>
 * struct forward_members_unordered {
 *   forward_members_unordered(const typename _Tp::value_type &v) {
 *     // Make sure that even if rel_ops is injected there is no ambiguity
 *     // when comparing iterators.
 *     using namespace std::rel_ops;
 *
 *     typedef _Tp test_type;
 *     test_type container;
 *     container.insert(v);
 *
 *     iterator_concept_checks<typename _Tp::local_iterator, false> cc;
 *     iterator_concept_checks<typename _Tp::const_local_iterator, false> ccc;
 *
 *     assert(container.cbegin(0) == container.begin(0));
 *     assert(container.cend(0) == container.end(0));
 *     const auto bn = container.bucket(1);
 *     auto clit     = container.cbegin(bn);
 *     assert(clit != container.cend(bn));
 *     assert(clit != container.end(bn));
 *     assert(clit++ == container.cbegin(bn));
 *     assert(clit == container.end(bn));
 *
 *     clit = container.cbegin(bn);
 *     assert(++clit == container.cend(bn));
 *
 *     assert(container.begin(bn) != container.cend(bn));
 *   }
 * };
 *
 * template<typename _Iterator>
 * struct iterator_concept_checks<_Iterator, false, std::forward_iterator_tag> {
 *   iterator_concept_checks() {
 *     using namespace __gnu_cxx;
 *     __function_requires<_ForwardIteratorConcept<_Iterator>>();
 *   }
 * };
 *
 * template<typename _Iterator>
 * struct iterator_concept_checks<_Iterator, true, std::forward_iterator_tag> {
 *   iterator_concept_checks() {
 *     using namespace __gnu_cxx;
 *     __function_requires<_Mutable_ForwardIteratorConcept<_Iterator>>();
 *   }
 * };
 *
 * template<typename _Iterator>
 * struct iterator_concept_checks<_Iterator, false,
 *                                std::bidirectional_iterator_tag> {
 *   iterator_concept_checks() {
 *     using namespace __gnu_cxx;
 *     __function_requires<_BidirectionalIteratorConcept<_Iterator>>();
 *   }
 * };
 *
 * template<typename _Iterator>
 * struct iterator_concept_checks<_Iterator, true,
 *                                std::bidirectional_iterator_tag> {
 *   iterator_concept_checks() {
 *     using namespace __gnu_cxx;
 *     __function_requires<_Mutable_BidirectionalIteratorConcept<_Iterator>>();
 *   }
 * };
 *
 * template<typename _Iterator>
 * struct iterator_concept_checks<_Iterator, false,
 *                                std::random_access_iterator_tag> {
 *   iterator_concept_checks() {
 *     using namespace __gnu_cxx;
 *     __function_requires<_RandomAccessIteratorConcept<_Iterator>>();
 *   }
 * };
 *
 * template<typename _Iterator>
 * struct iterator_concept_checks<_Iterator, true,
 *                                std::random_access_iterator_tag> {
 *   iterator_concept_checks() {
 *     using namespace __gnu_cxx;
 *     __function_requires<_Mutable_RandomAccessIteratorConcept<_Iterator>>();
 *   }
 * };
 *
 * template<typename _Tp>
 * struct forward_members {
 *   forward_members(_Tp &container) {
 *     // Make sure that even if rel_ops is injected there is no ambiguity
 *     // when comparing iterators.
 *     using namespace std::rel_ops;
 *
 *     typedef traits<_Tp> traits_type;
 *     iterator_concept_checks<typename _Tp::iterator,
 *                             !(traits_type::is_associative::value ||
 *                               traits_type::is_unordered::value)>
 *         cc;
 *     iterator_concept_checks<typename _Tp::const_iterator, false> ccc;
 *
 *     assert(container.cbegin() == container.begin());
 *     assert(container.end() == container.cend());
 *     assert(container.cbegin() != container.cend());
 *     assert(container.cbegin() != container.end());
 *     assert(container.begin() != container.cend());
 *   }
 * };
 *
 * template<typename _Tp, typename = typename std::iterator_traits<
 *                            typename _Tp::iterator>::iterator_category>
 * struct category_members : forward_members<_Tp> {
 *   category_members(_Tp &container) : forward_members<_Tp>(container){};
 * };
 *
 * template<typename _Tp>
 * struct category_members<_Tp, std::random_access_iterator_tag>
 *     : forward_members<_Tp> {
 *   category_members(_Tp &container) : forward_members<_Tp>(container) {
 *     // Make sure that even if rel_ops is injected there is no ambiguity
 *     // when comparing iterators.
 *     using namespace std::rel_ops;
 *
 *     assert(!(container.begin() < container.begin()));
 *     assert(!(container.cbegin() < container.cbegin()));
 *     assert(!(container.cbegin() < container.begin()));
 *     assert(!(container.begin() < container.cbegin()));
 *     assert(container.begin() <= container.begin());
 *     assert(container.cbegin() <= container.cbegin());
 *     assert(container.cbegin() <= container.begin());
 *     assert(container.begin() <= container.cbegin());
 *
 *     assert(!(container.begin() > container.begin()));
 *     assert(!(container.cbegin() > container.cbegin()));
 *     assert(!(container.cbegin() > container.begin()));
 *     assert(!(container.begin() > container.cbegin()));
 *     assert(container.begin() >= container.begin());
 *     assert(container.cbegin() >= container.cbegin());
 *     assert(container.cbegin() >= container.begin());
 *     assert(container.begin() >= container.cbegin());
 *
 *     assert(container.begin() - container.begin() == 0);
 *     assert(container.cbegin() - container.cbegin() == 0);
 *     assert(container.cbegin() - container.begin() == 0);
 *     assert(container.begin() - container.cbegin() == 0);
 *
 *     assert(container.begin() + 0 == container.begin());
 *     assert(container.cbegin() + 0 == container.cbegin());
 *     assert(0 + container.begin() == container.begin());
 *     assert(0 + container.cbegin() == container.cbegin());
 *     assert(container.begin() - 0 == container.begin());
 *     assert(container.cbegin() - 0 == container.cbegin());
 *   }
 * };
 *
 * template<typename _Tp>
 * struct citerator {
 *   typedef _Tp test_type;
 *   typedef traits<test_type> traits_type;
 *   typedef typename test_type::value_type value_type;
 *
 *   static test_type _S_container;
 *
 *   // Unconditional.
 *   struct members : category_members<_Tp> {
 *     members() : category_members<_Tp>(_S_container) {
 *     }
 *   };
 *
 *   // Run test.
 *   citerator() {
 *     populate<test_type> p(_S_container);
 *     members m1;
 *     reverse_members<test_type> m2(_S_container);
 *   }
 * };
 *
 * template<typename _Tp>
 * _Tp citerator<_Tp>::_S_container;
 *
 * // DR 130 vs. C++98 vs. C++11.
 * // Defined in testsuite_shared.cc.
 * void erase_external(std::set<int> &s);
 *
 * void erase_external(std::multiset<int> &s);
 *
 * void erase_external(std::map<int, int> &s);
 *
 * void erase_external(std::multimap<int, int> &s);
 *
 * void erase_external_iterators(std::set<int> &s);
 *
 * void erase_external_iterators(std::multiset<int> &s);
 *
 * void erase_external_iterators(std::map<int, int> &s);
 *
 * void erase_external_iterators(std::multimap<int, int> &s);
 *
 * #if __cplusplus < 201103L
 * #error "must be compiled with C++11 (or later)"
 * #else
 * template<typename _Tp>
 * void linkage_check_cxx98_cxx11_erase(_Tp &container) {
 *   // Crashing when external reference and internal reference symbols are
 *   // equivalently mangled but have different size return types in C++98
 *   // and C++11 signatures.
 *   erase_external(container);           // C++98
 *   container.erase(container.begin());  // C++11
 * }
 *
 * template<typename _Tp>
 * void linkage_check_cxx98_cxx11_erase_iterators(_Tp &container) {
 *   // Crashing when external reference and internal reference symbols are
 *   // equivalently mangled but have different size return types in C++98
 *   // and C++11 signatures.
 *   erase_external_iterators(container);  // C++98
 *
 *   auto iter = container.begin();
 *   container.erase(iter, ++iter);  // C++11
 * }
 * #endif
 */

}  // namespace __ht_test

// vim: et sw=2 ts=2
