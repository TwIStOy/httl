// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include <concepts>
#include <functional>
#include <type_traits>
#include <utility>

#include <ht/strings/stringify.hpp>

namespace ht {

template<typename T, typename Tag, template<typename> class... Skills>
struct named_wrapper : public Skills<named_wrapper<T, Tag, Skills...>>... {
  using value_type = T;

 private:
  value_type value_;

 public:
  template<typename _U = T>
    requires std::is_default_constructible_v<_U>
  named_wrapper() : value_{} {
  }

  template<typename _U = T>
    requires std::is_copy_constructible_v<_U>
  named_wrapper(const named_wrapper& rhs) : value_{rhs.value_} {  // NOLINT
  }

  template<typename _U = T>
    requires std::is_move_constructible_v<_U>
  named_wrapper(named_wrapper&& rhs)  // NOLINT
      : value_{std::move(rhs.value_)} {
  }

  template<typename... Args>
    requires std::is_constructible_v<value_type, Args...>
  named_wrapper(Args&&...args)  // NOLINT
      : value_{std::forward<Args>(args)...} {
  }

  template<typename _U = T>
    requires std::is_copy_assignable_v<_U>
  named_wrapper& operator=(const named_wrapper& rhs) {
    value_ = rhs.value_;
    return *this;
  }

  template<typename _U = T>
    requires std::is_move_assignable_v<_U>
  named_wrapper& operator=(named_wrapper&& rhs) {
    value_ = std::move(rhs.value_);
    return *this;
  }

  explicit operator value_type &() & {
    return value_;
  }

  explicit operator value_type &&() && {
    return std::move(value_);
  }

  explicit operator const value_type &() const& {
    return value_;
  }

  explicit operator const value_type &&() const&& {
    return std::move(value_);
  }

  value_type& value() & {
    return value_;
  }

  const value_type& value() const& {
    return value_;
  }

  value_type&& value() && {
    return std::move(value_);
  }

  const value_type&& value() const&& {
    return std::move(value_);
  }

  using ref_type = named_wrapper<value_type&, Tag, Skills...>;
  ref_type ref() & {
    return ref_type{value_};
  }

  template<typename _U = T>
    requires tag_invocable<tag_t<stringify>, _U, uint16_t, int16_t>
  auto tag_invoke(tag_t<stringify>, const named_wrapper& value, uint16_t level,
                  int16_t indent) {
    return stringify(value.value_, level, indent);
  }

  struct argument {
    template<typename _U>
    named_wrapper operator=(_U&& v) const {  // NOLINT
      return named_wrapper{std::forward<_U>(v)};
    }
  };
};

namespace named_wrapper_skills {

namespace __detail {

template<typename T, template<typename> class>
struct crtp_helper {
  T& __downcast() {
    return *static_cast<T *>(this);
  }

  const T& __downcast() const {
    return *static_cast<const T *>(this);
  }
};

}  // namespace __detail

#define __HT_SELF  (this->__downcast())
#define __HT_VALUE (this->__downcast().value())

template<typename T>
struct incrementable : __detail::crtp_helper<T, incrementable> {
  T& operator+=(const T& rhs) {
    __HT_VALUE += rhs.value();
    return __HT_SELF;
  }
};

template<typename T>
struct pre_incrementable : __detail::crtp_helper<T, pre_incrementable> {
  T& operator++() {
    ++__HT_VALUE;
    return __HT_SELF;
  }
};

template<typename T>
struct addable : __detail::crtp_helper<T, addable> {
  T operator+(T const& rhs) const {
    return T(__HT_VALUE + rhs.value());
  }
};

template<typename T>
struct subtractable : __detail::crtp_helper<T, subtractable> {
  T operator-(T const& rhs) const {
    return T(__HT_VALUE - rhs.value());
  }
};

template<typename T>
struct multiplicable : __detail::crtp_helper<T, multiplicable> {
  T operator*(T const& rhs) const {
    return T(__HT_VALUE * rhs.value());
  }
};

template<typename T>
struct negatable : __detail::crtp_helper<T, negatable> {
  T operator-() const {
    return T(-__HT_VALUE);
  }
};

template<typename T>
struct hashable : __detail::crtp_helper<T, hashable> {};

#undef __HT_SELF
#undef __HT_VALUE

}  // namespace named_wrapper_skills

}  // namespace ht

namespace std {

template<typename T, typename Tag, template<typename> class... Skills>
  requires(std::same_as<Skills<T>, ht::named_wrapper_skills::hashable<T>> ||
           ...)
struct hash<ht::named_wrapper<T, Tag, Skills...>> {  // NOLINT
  using value_type = ht::named_wrapper<T, Tag, Skills...>;
  auto operator()(const value_type& v) const {
    return std::hash<T>{}(v.value());
  }
};

}  // namespace std

// vim: et sw=2 ts=2
