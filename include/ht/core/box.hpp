// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include <concepts>
#include <iostream>
#include <memory>
#include <new>
#include <type_traits>
#include <utility>

#include <ht/core/scope_guard.hpp>

namespace ht {

/// A value type that can be used to store a value in union.
template<typename T>
class box {
  static_assert(std::is_nothrow_destructible_v<T>);

 public:
  using value_type = T;
  using reference  = value_type&;

  box() noexcept = default;

  template<typename... Args>
  reference construct(Args&&...args) noexcept(
      std::is_nothrow_constructible_v<T, Args...>) {
    return *::new (static_cast<void *>(std::addressof(storage_)))
        value_type(std::forward<Args>(args)...);
  }

  template<typename Func>
  reference construct_from(Func&& func) noexcept(
      std::is_nothrow_invocable_v<Func>) {
    return *::new (static_cast<void *>(std::addressof(storage_)))
        T(std::forward<Func>(func)());
  }

  void destruct() noexcept {
    reinterpret_cast<T *>(std::addressof(storage_))->~T();
  }

  T *ptr() {
    return reinterpret_cast<T *>(std::addressof(storage_));
  }

  const T *ptr() const {
    return reinterpret_cast<const T *>(std::addressof(storage_));
  }

  reference get() & noexcept {
    return *ptr();
  }

  T&& get() && noexcept {
    return std::move(*ptr());
  }

  const T& get() const& noexcept {
    return *ptr();
  }

  const T&& get() const&& noexcept {
    return std::move(*ptr());
  }

 private:
  std::aligned_storage_t<sizeof(T), alignof(T)> storage_;
};

template<typename T>
class box<T&> {
 public:
  using value_type = T&;
  using reference  = value_type;

  box() noexcept = default;

  ~box() = default;

  reference construct(T& value) noexcept {
    storage_ = std::addressof(value);
    return value;
  }

  template<typename Func>
    requires std::is_same_v<std::invoke_result_t<Func>, value_type>
  reference construct_from(Func&& func) noexcept(
      std::is_nothrow_invocable_v<Func>) {
    storage_ = std::addressof(std::forward<Func>(func)());
    return get();
  }

  void destruct() noexcept {
  }

  reference get() const noexcept {
    return *storage_;
  }

 private:
  T *storage_{nullptr};
};

template<typename T>
class box<T&&> {
 public:
  using value_type = T&&;
  using reference  = value_type;

  box() noexcept = default;

  ~box() = default;

  T&& construct(T&& value) noexcept {
    storage_ = std::addressof(value);
    return std::move(value);
  }

  template<typename Func>
    requires std::is_same_v<std::invoke_result_t<Func>, value_type>
  reference construct_from(Func&& func) noexcept(std::is_invocable_v<Func>) {
    storage_ = std::addressof(std::forward<Func>(func)());
    return get();
  }

  void destruct() noexcept {
  }

  T&& get() const noexcept {
    return std::move(*storage_);
  }

 private:
  T *storage_{nullptr};
};

template<>
class box<void> {
 public:
  box() noexcept = default;
  ~box()         = default;

  void construct() noexcept {
  }

  template<typename Func>
    requires std::is_void_v<std::invoke_result_t<Func>>
  void construct_from(Func&& func) noexcept(std::is_invocable_v<Func>) {
    std::forward<Func>(func)();
  }

  void destruct() noexcept {
  }

  void get() const noexcept {
  }
};

template<>
class box<void const> : public box<void> {};

template<typename T, typename... Args>
T& construct_union_member(box<T> *buffer, Args&&...args) noexcept(
    std::is_nothrow_constructible_v<T, Args...>) {
  auto p = ::new (buffer) box<T>{};

  auto guard = scope_guard([p]() noexcept {
    p->~box();
  });

  auto& t = p->construct(std::forward<Args>(args)...);
  guard.release();
  return t;
}

inline void construct_union_member(box<void> *buffer) noexcept {
  auto p = ::new (buffer) box<void>{};
  p->construct();
}

template<typename T, typename Func>
T& construct_union_member_from(box<T> *buffer, Func&& func) noexcept(
    std::is_nothrow_invocable_v<Func>) {
  auto p = ::new (buffer) box<T>{};

  auto guard = scope_guard([p]() {
    p->~box();
  });

  auto& t = p->construct_from(std::forward<Func>(func));
  guard.release();
  return t;
}

template<typename T>
void destruct_union_member(box<T> *b) noexcept {
  b->destruct();
  b->~box();
}

}  // namespace ht

// vim: et sw=2 ts=2
