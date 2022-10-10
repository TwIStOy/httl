// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include <concepts>
#include <functional>
#include <map>
#include <optional>
#include <set>
#include <sstream>
#include <string>
#include <string_view>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <variant>
#include <vector>

#include <ht/core/impl/demangle.hpp>
#include <ht/core/impl/type_tag.hpp>
#include <ht/core/type_utils.hpp>
#include <ht/strings/string_utility.hpp>

namespace ht {

template<typename T>
struct readable_typename {};

}  // namespace ht

namespace ht::_typename_impl {

using std::operator""sv;

template<typename T>
consteval auto _typename_without_rtti() -> std::string_view {
#if defined(__clang__)
  constexpr auto prefix   = std::string_view{"[T = "};
  constexpr auto suffix   = "]";
  constexpr auto function = std::string_view{__PRETTY_FUNCTION__};
#elif defined(__GNUC__)
  constexpr auto prefix   = std::string_view{"with T = "};
  constexpr auto suffix   = "; ";
  constexpr auto function = std::string_view{__PRETTY_FUNCTION__};
#elif defined(_MSC_VER)
  constexpr auto prefix   = std::string_view{"get_type_name<"};
  constexpr auto suffix   = ">(void)";
  constexpr auto function = std::string_view{__FUNCSIG__};
#else
#error Unsupported compiler
#endif

  const auto start = function.find(prefix) + prefix.size();
  const auto end   = function.find(suffix);
  const auto size  = end - start;

  return function.substr(start, size);
}

constexpr auto _strip_template_arguments(std::string_view name) {
  const auto end = name.find('<');
  return name.substr(0, end);
}

template<typename... Args>
struct first_type;

template<typename F, typename... Args>
struct first_type<F, Args...> {
  using type = F;
};

template<>
struct first_type<> {};

template<typename T>
consteval std::string_view get_readable_typename();

template<typename T>
struct pretty_typename;

// builtin types should use simple name
#define __HT_DEFINE_GET_NAME_FN(type)        \
  template<>                                 \
  struct pretty_typename<type> {             \
    static constexpr auto value = #type##sv; \
  };

__HT_DEFINE_GET_NAME_FN(int16_t);
__HT_DEFINE_GET_NAME_FN(uint16_t);
__HT_DEFINE_GET_NAME_FN(int32_t);
__HT_DEFINE_GET_NAME_FN(uint32_t);
__HT_DEFINE_GET_NAME_FN(int64_t);
__HT_DEFINE_GET_NAME_FN(uint64_t);
__HT_DEFINE_GET_NAME_FN(std::string);
__HT_DEFINE_GET_NAME_FN(std::string_view);

static constexpr auto _left_angle_bracket  = "<"sv;
static constexpr auto _right_angle_bracket = ">"sv;
static constexpr auto _comma               = ", "sv;
static constexpr auto _empty               = ""sv;

#define __HT_DEFINE_STD_PREFIX(name) \
  static constexpr auto _std_##name##_prefix = "std::" #name##sv;

// static constexpr auto _std_vector_prefix = "std::vector"sv;
__HT_DEFINE_STD_PREFIX(vector);
__HT_DEFINE_STD_PREFIX(map);
__HT_DEFINE_STD_PREFIX(unordered_map);
__HT_DEFINE_STD_PREFIX(multimap);
__HT_DEFINE_STD_PREFIX(unordered_multimap);
__HT_DEFINE_STD_PREFIX(set);
__HT_DEFINE_STD_PREFIX(unordered_set);
__HT_DEFINE_STD_PREFIX(multiset);
__HT_DEFINE_STD_PREFIX(unordered_multiset);
__HT_DEFINE_STD_PREFIX(pair);
__HT_DEFINE_STD_PREFIX(tuple);
__HT_DEFINE_STD_PREFIX(optional);
__HT_DEFINE_STD_PREFIX(variant);

#define __HT_DEFINE_SIMPLE_BUILTIN_FN(name)                                \
  template<typename T>                                                     \
  struct pretty_typename<std::name<T>> {                                   \
    static constexpr auto value =                                          \
        concat_sv<_std_##name##_prefix, _left_angle_bracket,               \
                  pretty_typename<T>::value, _right_angle_bracket>::value; \
  };

__HT_DEFINE_SIMPLE_BUILTIN_FN(vector);
__HT_DEFINE_SIMPLE_BUILTIN_FN(optional);

template<const std::string_view& First, const std::string_view&...Rest>
struct _merge_type_list {
  static constexpr auto impl() noexcept {
    if constexpr (sizeof...(Rest) == 0) {
      return First;
    } else {
      return concat_sv<First, _comma, _merge_type_list<Rest...>::value>::value;
    }
  }
  static constexpr auto value = impl();
};

template<typename Key, typename Hash>
static constexpr auto _is_default_hash_v = [] {
  if constexpr (!std::same_as<Hash, std::hash<Key>>) {
    return concat_sv<_comma, pretty_typename<Hash>::value>::value;
  }
  return _empty;
}();

template<typename Key, typename Eq>
static constexpr auto _is_default_eq_v = [] {
  if constexpr (!std::same_as<Eq, std::equal_to<Key>> &&
                !std::same_as<Eq, std::equal_to<>>) {
    return concat_sv<_comma, pretty_typename<Eq>::value>::value;
  }
  return _empty;
}();

template<typename Key, typename Cmp>
static constexpr auto _is_default_cmp_v = [] {
  if constexpr (!std::same_as<Cmp, std::less<Key>> &&
                !std::same_as<Cmp, std::less<>>) {
    return concat_sv<_comma, pretty_typename<Cmp>::value>::value;
  }
  return _empty;
}();

#define __HT_DEFINE_HASH_MAP_BUILTIN_FN(name)                             \
  template<class K, class V, class Hash, class Eq, class A>               \
  struct pretty_typename<std::name<K, V, Hash, Eq, A>> {                  \
    static constexpr auto value =                                         \
        concat_sv<_std_##name##_prefix, _left_angle_bracket,              \
                  pretty_typename<K>::value, _comma,                      \
                  pretty_typename<V>::value, _is_default_hash_v<K, Hash>, \
                  _is_default_eq_v<K, Eq>, _right_angle_bracket>::value;  \
  };
__HT_DEFINE_HASH_MAP_BUILTIN_FN(unordered_map);
__HT_DEFINE_HASH_MAP_BUILTIN_FN(unordered_multimap);

#define __HT_DEFINE_HASH_SET_BUILTIN_FN(name)                             \
  template<class K, class Hash, class Eq, class A>                        \
  struct pretty_typename<std::name<K, Hash, Eq, A>> {                     \
    static constexpr auto value =                                         \
        concat_sv<_std_##name##_prefix, _left_angle_bracket,              \
                  pretty_typename<K>::value, _is_default_hash_v<K, Hash>, \
                  _is_default_eq_v<K, Eq>, _right_angle_bracket>::value;  \
  };
__HT_DEFINE_HASH_SET_BUILTIN_FN(unordered_set);
__HT_DEFINE_HASH_SET_BUILTIN_FN(unordered_multiset);

#define __HT_DEFINE_COMPARE_MAP_BUILTIN_FN(name)                        \
  template<typename K, typename V, typename Cmp, typename A>            \
  struct pretty_typename<std::name<K, V, Cmp, A>> {                     \
    static constexpr auto value =                                       \
        concat_sv<_std_##name##_prefix, _left_angle_bracket,            \
                  pretty_typename<K>::value, _comma,                    \
                  pretty_typename<V>::value, _is_default_cmp_v<K, Cmp>, \
                  _right_angle_bracket>::value;                         \
  }
__HT_DEFINE_COMPARE_MAP_BUILTIN_FN(map);
__HT_DEFINE_COMPARE_MAP_BUILTIN_FN(multimap);

#define __HT_DEFINE_COMPARE_SET_BUILTIN_FN(name)                        \
  template<typename K, typename Cmp, typename A>                        \
  struct pretty_typename<std::name<K, Cmp, A>> {                        \
    static constexpr auto value =                                       \
        concat_sv<_std_##name##_prefix, _left_angle_bracket,            \
                  pretty_typename<K>::value, _is_default_cmp_v<K, Cmp>, \
                  _right_angle_bracket>::value;                         \
  }

__HT_DEFINE_COMPARE_SET_BUILTIN_FN(set);
__HT_DEFINE_COMPARE_SET_BUILTIN_FN(multiset);

#define __HT_DEFINE_COMBINATION_TYPE_BUILTIN_FN(name)                       \
  template<typename... Args>                                                \
  struct pretty_typename<std::name<Args...>> {                              \
    static constexpr auto value =                                           \
        concat_sv<_std_##name##_prefix, _left_angle_bracket,                \
                  _merge_type_list<pretty_typename<Args>::value...>::value, \
                  _right_angle_bracket>::value;                             \
  }
__HT_DEFINE_COMBINATION_TYPE_BUILTIN_FN(pair);
__HT_DEFINE_COMBINATION_TYPE_BUILTIN_FN(variant);
__HT_DEFINE_COMBINATION_TYPE_BUILTIN_FN(tuple);

// pretty defined
template<typename T>
  requires requires {
             { readable_typename<T>::value } -> std::same_as<std::string_view>;
           }
struct pretty_typename<T> {
  static constexpr auto value = readable_typename<T>::value;
};

static constexpr auto _volatile = "volatile"sv;
static constexpr auto _const    = "const"sv;
static constexpr auto _space    = " "sv;
static constexpr auto _star     = "*"sv;
static constexpr auto _ref      = "&"sv;

template<typename T>
consteval std::string_view get_readable_typename() {
  if constexpr (std::is_volatile_v<T>) {
    if constexpr (std::is_pointer_v<T>) {
      return concat_sv<pretty_typename<std::remove_volatile_t<T>>::value,
                       _space, _volatile>::value;

    } else {
      return concat_sv<
          _volatile, _space,
          pretty_typename<std::remove_volatile_t<T>>::value>::value;
    }
  } else if constexpr (std::is_const_v<T>) {
    if constexpr (std::is_pointer_v<T>) {
      return concat_sv<pretty_typename<std::remove_volatile_t<T>>::value,
                       _space, _const>::value;

    } else {
      return concat_sv<
          _const, _space,
          pretty_typename<std::remove_volatile_t<T>>::value>::value;
    }
  } else if constexpr (std::is_pointer_v<T>) {
    return concat_sv<pretty_typename<std::remove_pointer_t<T>>::value,
                     _star>::value;
  } else if constexpr (std::is_lvalue_reference_v<T>) {
    return concat_sv<pretty_typename<std::remove_reference_t<T>>::value,
                     _ref>::value;
  } else if constexpr (std::is_rvalue_reference_v<T>) {
    return concat_sv<pretty_typename<std::remove_reference_t<T>>::value, _ref,
                     _ref>::value;
  } else {
    return _typename_without_rtti<T>();
  }
}

#undef __HT_DEFINE_SIMPLE_BUILTIN_FN
#undef __HT_DEFINE_GET_NAME_FN
#undef __HT_DEFINE_STD_PREFIX
#undef __HT_DEFINE_HASH_CONTAINER_BUILTIN_FN
#undef __HT_DEFINE_COMPARE_CONTAINER_BUILTIN_FN
#undef __HT_DEFINE_COMBINATION_TYPE_BUILTIN_FN

template<typename T>
struct pretty_typename {
  static constexpr auto value = get_readable_typename<T>();
};

}  // namespace ht::_typename_impl

namespace ht {
using _typename_impl::pretty_typename;
}  // namespace ht

// vim: et sw=2 ts=2
