// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include <fmt/format.h>

#include <stdexcept>
#include <variant>

#include "ht/core/cpp_feature.h"

namespace ht {

struct ResultUnwrapError : public std::runtime_error {
  template<typename... Args>
  ResultUnwrapError(fmt::format_string<Args...> fmt, Args &&...args)
      : runtime_error(fmt::format(fmt, std::forward<Args>(args)...)) {
  }
};

namespace __details {

template<typename T>
struct __result_result_type {
  template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
  explicit __result_result_type(__result_result_type<U> &&u)
      : v(std::move(u.v)) {
  }

  explicit __result_result_type(T v) : v(std::move(v)) {
  }

  T v;
};

template<>
struct __result_result_type<void> {
  __result_result_type() = default;

  template<typename U>
  explicit __result_result_type(__result_result_type<U> &&u) {
    (void)u;
  }
};

template<typename T>
struct __result_error_type {
  template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
  explicit __result_error_type(__result_error_type<U> &&u) : v(std::move(u.v)) {
  }

  explicit __result_error_type(T v) : v(std::move(v)) {
  }

  T v;
};

template<>
struct __result_error_type<void> {
  __result_error_type() = default;

  template<typename U>
  explicit __result_error_type(__result_error_type<U> &&u) {
    (void)u;
  }
};

template<typename Derived, typename result_t>
struct __result_ok_base {
  HT_ALWAYS_INLINE
  static Derived Ok(result_t v) {
    return Derived{__result_result_type<result_t>{std::move(v)}};
  }

  HT_ALWAYS_INLINE result_t unwrap() const & {
    if (!static_cast<Derived *>(this)->IsOk()) {
      throw ResultUnwrapError("Failed to unwrap!");
    }
    return std::get<__result_result_type<result_t>>(
               static_cast<Derived *>(this)->storage_)
        .v;
  }

  HT_ALWAYS_INLINE result_t &unwrap() & {
    if (!static_cast<Derived *>(this)->IsOk()) {
      throw ResultUnwrapError("Failed to unwrap!");
    }
    return std::get<__result_result_type<result_t>>(
               static_cast<Derived *>(this)->storage_)
        .v;
  }

  HT_ALWAYS_INLINE result_t &&unwrap() && {
    if (!static_cast<Derived *>(this)->IsOk()) {
      throw ResultUnwrapError("Failed to unwrap!");
    }
    return std::move(std::get<__result_result_type<result_t>>(
                         static_cast<Derived *>(this)->storage_)
                         .v);
  }
};

template<typename Derived>
struct __result_ok_base<Derived, void> {
  HT_ALWAYS_INLINE static Derived Ok() {
    return Derived{__result_result_type<void>{}};
  }

  HT_ALWAYS_INLINE void unwrap() const {
    if (!static_cast<Derived *>(this)->IsOk()) {
      throw ResultUnwrapError("Failed to unwrap!");
    }
  }

  HT_ALWAYS_INLINE void unwrap() {
    if (!static_cast<Derived *>(this)->IsOk()) {
      throw ResultUnwrapError("Failed to unwrap!");
    }
  }
};

template<typename Derived, typename error_t>
struct __result_err_base {
  HT_ALWAYS_INLINE static Derived Err(error_t v) {
    return Derived{__result_error_type<error_t>{std::move(v)}};
  }
};

template<typename T>
struct __temp_ok_object {
  __result_result_type<T> v;
};

template<typename T>
struct __temp_err_object {
  __result_error_type<T> v;
};

}  // namespace __details

template<typename T>
HT_ALWAYS_INLINE __details::__temp_ok_object<T> Ok(T v);

HT_ALWAYS_INLINE __details::__temp_ok_object<void> Ok();

template<typename T>
HT_ALWAYS_INLINE __details::__temp_err_object<T> Err(T v);

HT_ALWAYS_INLINE __details::__temp_err_object<void> Err();

template<typename ResultType, typename ErrorType>
class Result
    : public __details::__result_ok_base<Result<ResultType, ErrorType>,
                                         ResultType>,
      public __details::__result_err_base<Result<ResultType, ErrorType>,
                                          ErrorType> {
 public:
  using result_t = ResultType;
  using error_t  = ErrorType;

  template<typename T>
  Result(__details::__temp_ok_object<T> v) {
    (void)v;
    if constexpr (std::is_same_v<result_t, void>) {
      storage_ = __details::__result_result_type<void>{};
    } else {
      storage_ =
          __details::__result_result_type<result_t>{result_t{std::move(v.v.v)}};
    }
  }

  template<typename T>
  Result(__details::__temp_err_object<T> v) {
    (void)v;
    if constexpr (std::is_same_v<error_t, void>) {
      storage_ = __details::__result_error_type<void>{};
    } else {
      storage_ =
          __details::__result_error_type<error_t>{error_t{std::move(v.v.v)}};
    }
  }

 private:
  struct __none {};

  using storage_t =
      std::variant<__none, __details::__result_result_type<result_t>,
                   __details::__result_error_type<error_t>>;

  friend __details::__result_ok_base<Result<ResultType, ErrorType>, ResultType>;
  friend __details::__result_err_base<Result<ResultType, ErrorType>, ErrorType>;

 private:
  explicit Result(storage_t storage) : storage_(std::move(storage)) {
  }

  template<typename T>
  friend __details::__temp_ok_object<T> Ok(T v);
  friend __details::__temp_ok_object<void> Ok();

  template<typename T>
  friend __details::__temp_err_object<T> Err(T v);
  friend __details::__temp_err_object<void> Err();

 public:
  HT_ALWAYS_INLINE bool IsOk() const {
    return storage_.index() == 1;
  }

  HT_ALWAYS_INLINE bool IsErr() const {
    return storage_.index() == 2;
  }

  HT_ALWAYS_INLINE operator bool() const {
    return IsOk();
  }

 private:
  storage_t storage_;
};

template<typename T>
HT_ALWAYS_INLINE __details::__temp_ok_object<T> Ok(T v) {
  return __details::__temp_ok_object<T>{
      __details::__result_result_type<T>{std::move(v)}};
}

HT_ALWAYS_INLINE __details::__temp_ok_object<void> Ok() {
  return __details::__temp_ok_object<void>{};
}

template<typename T>
HT_ALWAYS_INLINE __details::__temp_err_object<T> Err(T v) {
  return __details::__temp_err_object<T>{
      __details::__result_error_type<T>{std::move(v)}};
}

HT_ALWAYS_INLINE __details::__temp_err_object<void> Err() {
  return __details::__temp_err_object<void>{};
}

}  // namespace ht

// vim: et sw=2 ts=2
