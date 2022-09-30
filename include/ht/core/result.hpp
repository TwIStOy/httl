// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include <fmt/format.h>

#include <concepts>
#include <iostream>
#include <stdexcept>
#include <type_traits>
#include <utility>
#include <variant>

// ---

#include <ht/core/cpp_feature.h>

#include <ht/core/box.hpp>

namespace ht {

struct result_unwrap_error : public std::runtime_error {
  template<typename... Args>
  explicit result_unwrap_error(fmt::format_string<Args...> fmt, Args &&...args)
      : runtime_error(fmt::format(fmt, std::forward<Args>(args)...)) {
  }
};

namespace __impl {

struct value_tag;
struct error_tag;

template<typename Tag, typename T>
struct temp_wrapper {
  T value;
};

template<typename Tag>
struct temp_wrapper<Tag, void> {};

template<typename T, typename D>
struct value_result_base {
  using value_type   = T;
  using derived_type = D;

  HT_ALWAYS_INLINE value_type &unwrap() const & {
  }

  box<value_type> value_;
};

enum class _result_state { empty, value, error };

}  // namespace __impl

template<typename VT, typename ET>
struct result {
  using value_type = VT;
  using error_type = ET;

  template<typename U, typename V>
  friend struct result;

 private:
  enum class _state { empty, value, error };
  _state state_{_state::empty};
  union {
    box<value_type> value_;
    box<error_type> error_;
  };
  static constexpr auto box_size = sizeof(box<value_type>) >
                                           sizeof(box<error_type>)
                                       ? sizeof(box<value_type>)
                                       : sizeof(box<error_type>);

  void reset() {
    auto old = std::exchange(state_, _state::empty);
    switch (old) {
      case _state::value:
        destruct_union_member(&value_);
        break;
      case _state::error:
        destruct_union_member(&error_);
        break;
      case _state::empty:
        break;
    }
  }

  template<typename U = value_type, typename V = error_type>
    requires std::is_trivially_copy_constructible_v<U> &&
             std::is_trivially_copy_constructible_v<V>
  result(const result &rhs, int = 0) : state_(rhs.state_) {  // NOLINT
    memcpy(&value_, &rhs.value_, box_size);
  }

  template<typename U = value_type, typename V = error_type>
    requires(std::copy_constructible<U> && std::copy_constructible<V>) &&
            (!std::is_trivially_copy_constructible_v<U> ||
             !std::is_trivially_copy_constructible_v<V>)
  result(const result &rhs, int = 0) : state_(rhs.state_) {  // NOLINT
    switch (state_) {
      case _state::value:
        if constexpr (!std::is_void_v<value_type>) {
          construct_union_member(&value_, rhs.value_.get());
        } else {
          construct_union_member(&value_);
        }
        break;
      case _state::error:
        if constexpr (!std::is_void_v<error_type>) {
          construct_union_member(&error_, rhs.error_.get());
        } else {
          construct_union_member(&error_);
        }
        break;
      case _state::empty:
        break;
    }
  }

  template<typename U = value_type, typename V = error_type>
    requires std::move_constructible<U> && std::move_constructible<V>
  result(result &&rhs, int = 0) noexcept : state_(rhs.state_) {  // NOLINT
    switch (state_) {
      case _state::value:
        if constexpr (!std::is_void_v<value_type>) {
          construct_union_member(&value_, std::move(rhs.value_).get());
        } else {
          construct_union_member(&value_);
        }
        break;
      case _state::error:
        if constexpr (!std::is_void_v<error_type>) {
          construct_union_member(&error_, std::move(rhs.error_).get());
        } else {
          construct_union_member(&error_);
        }
        break;
      case _state::empty:
        break;
    }
  }

  template<typename F, bool>
  struct map_value_t;

  template<typename F>
  struct map_value_t<F, true> {
    using type = std::invoke_result_t<F>;
  };

  template<typename F>
  struct map_value_t<F, false> {
    using type = std::invoke_result_t<F, value_type &&>;
  };

  template<typename F, bool>
  struct map_error_t;

  template<typename F>
  struct map_error_t<F, true> {
    using type = std::invoke_result_t<F>;
  };

  template<typename F>
  struct map_error_t<F, false> {
    using type = std::invoke_result_t<F, error_type &&>;
  };

 public:
  result() = default;

  [[nodiscard]] HT_ALWAYS_INLINE bool is_empty() const {
    return state_ == _state::empty;
  }

  template<typename U>
    requires std::convertible_to<U, value_type>
  result &set(__impl::temp_wrapper<__impl::value_tag, U> v) {
    reset();
    if constexpr (std::is_void_v<U>) {
      construct_union_member(&value_);
    } else {
      construct_union_member(&value_, std::move(v.value));
    }
    state_ = _state::value;
    return *this;
  }

  template<typename... Args>
    requires(std::constructible_from<value_type, Args...> ||
             (std::same_as<value_type, void> && sizeof...(Args) == 0))
  result &set_value(Args &&...args) {
    reset();
    construct_union_member(&value_, std::forward<Args>(args)...);
    state_ = _state::value;
    return *this;
  }

  template<typename U>
    requires std::convertible_to<U, error_type>
  result &set(__impl::temp_wrapper<__impl::error_tag, U> v) {
    reset();
    if constexpr (std::is_void_v<U>) {
      construct_union_member(&error_);
    } else {
      construct_union_member(&error_, std::move(v.value));
    }
    state_ = _state::error;
    return *this;
  }

  template<typename... Args>
    requires(std::constructible_from<error_type, Args...> ||
             (std::same_as<error_type, void> && sizeof...(Args) == 0))
  result &set_error(Args &&...args) {
    reset();
    construct_union_member(&error_, std::forward<Args>(args)...);
    state_ = _state::error;
    return *this;
  }

  template<typename U>
    requires std::convertible_to<U, value_type>
  result(__impl::temp_wrapper<__impl::value_tag, U> v) {  // NOLINT
    set(std::move(v));
  }

  template<typename U>
    requires std::convertible_to<U, error_type>
  result(__impl::temp_wrapper<__impl::error_tag, U> v) {  // NOLINT
    set(std::move(v));
  }

  result(const result &rhs) : result(rhs, 0) {
  }

  result(result &&rhs) noexcept : result(std::move(rhs), 0) {
  }

  template<typename T, typename U>
    requires std::convertible_to<U, value_type> &&
             (std::same_as<T, __impl::value_tag> ||
              std::same_as<T, __impl::error_tag>)
  result &operator=(__impl::temp_wrapper<T, U> v) {
    set(std::move(v));
    return *this;
  }

  result &operator=(const result &rhs) {
    static_assert(std::copy_constructible<value_type> ||
                  (std::is_default_constructible_v<value_type> &&
                   std::is_copy_assignable_v<value_type>));
    static_assert(std::copy_constructible<error_type> ||
                  (std::is_default_constructible_v<error_type> &&
                   std::is_copy_assignable_v<error_type>));

    reset();

    state_ = rhs.state_;

    if (state_ == _state::value) {
      if constexpr (std::is_default_constructible_v<value_type> &&
                    std::is_copy_assignable_v<value_type>) {
        construct_union_member(&value_);

        if constexpr (!std::is_void_v<value_type>) {
          value_.get() = rhs.value_.get();
        }
      } else if constexpr (std::copy_constructible<value_type>) {
        if constexpr (!std::is_void_v<value_type>) {
          construct_union_member(&value_, rhs.value_.get());
        } else {
          construct_union_member(&value_);
        }
      }
    } else if (state_ == _state::error) {
      if constexpr (std::is_default_constructible_v<error_type> &&
                    std::is_copy_assignable_v<error_type>) {
        construct_union_member(&error_);

        if constexpr (!std::is_void_v<error_type>) {
          error_.get() = rhs.error_.get();
        }
      } else if constexpr (std::copy_constructible<error_type>) {
        if constexpr (!std::is_void_v<error_type>) {
          construct_union_member(&error_, rhs.error_.get());
        } else {
          construct_union_member(&error_);
        }
      }
    }

    return *this;
  }

  result &operator=(result &&rhs) noexcept {
    static_assert(std::move_constructible<value_type> ||
                  (std::is_default_constructible_v<value_type> &&
                   std::is_move_assignable_v<value_type>));
    static_assert(std::move_constructible<error_type> ||
                  (std::is_default_constructible_v<error_type> &&
                   std::is_move_assignable_v<error_type>));

    reset();

    state_ = rhs.state_;

    if (state_ == _state::value) {
      if constexpr (std::is_default_constructible_v<value_type> &&
                    std::is_move_assignable_v<value_type>) {
        construct_union_member(&value_);

        if constexpr (!std::is_void_v<value_type>) {
          value_.get() = std::move(rhs.value_).get();
        }
      } else if constexpr (std::move_constructible<value_type>) {
        if constexpr (!std::is_void_v<value_type>) {
          construct_union_member(&value_, std::move(rhs.value_).get());
        } else {
          construct_union_member(&value_);
        }
      }
    } else if (state_ == _state::error) {
      if constexpr (std::is_default_constructible_v<error_type> &&
                    std::is_move_assignable_v<error_type>) {
        construct_union_member(&error_);

        if constexpr (!std::is_void_v<error_type>) {
          error_.get() = std::move(rhs.error_).get();
        }
      } else if constexpr (std::move_constructible<error_type>) {
        if constexpr (!std::is_void_v<error_type>) {
          construct_union_member(&error_, std::move(rhs.error_).get());
        } else {
          construct_union_member(&error_);
        }
      }
    }

    return *this;
  }

  auto operator->() & {
    return &unwrap();
  }

  template<typename F, typename new_value_type = typename map_value_t<
                           F, std::is_void_v<value_type>>::type>
  result<new_value_type, error_type> map(F func) && {
    result<new_value_type, error_type> res;
    res.state_ = static_cast<decltype(res.state_)>(state_);

    switch (state_) {
      case _state::value:
        if constexpr (std::is_void_v<value_type>) {
          construct_union_member(&res.value_, std::forward<F>(func)());
        } else {
          construct_union_member(
              &res.value_, std::forward<F>(func)(std::move(value_).get()));
        }
        break;
      case _state::error:
        construct_union_member(&res.error_, std::move(error_).get());
        break;
      case _state::empty:
        break;
    }

    return res;
  }

  template<typename F, typename new_error_type = typename map_error_t<
                           F, std::is_void_v<error_type>>::type>
  result<value_type, new_error_type> map_err(F func) && {
    result<value_type, new_error_type> res;
    res.state_ = static_cast<decltype(res.state_)>(state_);

    switch (state_) {
      case _state::value:
        construct_union_member(&res.value_, std::move(value_).get());

        break;
      case _state::error:
        if constexpr (std::is_void_v<value_type>) {
          construct_union_member(&res.error_, std::forward<F>(func)());
        } else {
          construct_union_member(
              &res.error_, std::forward<F>(func)(std::move(error_).get()));
        }
        break;
      case _state::empty:
        break;
    }

    return res;
  }

  ~result() {
    reset();
  }

  [[nodiscard]] HT_ALWAYS_INLINE bool is_ok() const noexcept {
    return state_ == _state::value;
  }

  template<typename Func>
    requires std::is_invocable_v<Func, value_type>
  [[nodiscard]] HT_ALWAYS_INLINE bool is_ok_and(Func &&func) const
      noexcept(std::is_nothrow_invocable_v<Func, value_type>) {
    return is_ok() && std::forward<Func>(func)(value_.get());
  }

  HT_ALWAYS_INLINE operator bool() const {  // NOLINT
    return is_ok();
  }

  [[nodiscard]] HT_ALWAYS_INLINE bool is_err() const noexcept {
    return state_ == _state::error;
  }

  template<typename Func>
    requires std::is_invocable_v<Func, error_type>
  [[nodiscard]] HT_ALWAYS_INLINE bool is_err_and(Func &&func) const
      noexcept(std::is_nothrow_invocable_v<Func, error_type>) {
    return is_err() && std::forward<Func>(func)(error_.get());
  }

  HT_ALWAYS_INLINE decltype(auto) unwrap() & {
    if (!is_ok()) {
      throw result_unwrap_error{"unwrap failed"};
    }

    if constexpr (std::is_void_v<value_type>) {
      return;
    } else {
      return value_.get();
    }
  }

  HT_ALWAYS_INLINE decltype(auto) unwrap() const & {
    if (!is_ok()) {
      throw result_unwrap_error{"unwrap failed"};
    }

    if constexpr (std::is_void_v<value_type>) {
      return;
    } else {
      return value_.get();
    }
  }

  HT_ALWAYS_INLINE decltype(auto) unwrap() && {
    if (!is_ok()) {
      throw result_unwrap_error{"unwrap failed"};
    }

    if constexpr (std::is_void_v<value_type>) {
      return;
    } else {
      return std::move(value_).get();
    }
  }

  HT_ALWAYS_INLINE decltype(auto) unwrap() const && {
    if (!is_ok()) {
      throw result_unwrap_error{"unwrap failed"};
    }

    if constexpr (std::is_void_v<value_type>) {
      return;
    } else {
      return std::move(value_).get();
    }
  }

  HT_ALWAYS_INLINE decltype(auto) unwrap_err() & {
    if (!is_err()) {
      throw result_unwrap_error{"unwrap failed"};
    }

    if constexpr (std::is_void_v<error_type>) {
      return;
    } else {
      return error_.get();
    }
  }

  HT_ALWAYS_INLINE decltype(auto) unwrap_err() && {
    if (!is_err()) {
      throw result_unwrap_error{"unwrap failed"};
    }

    if constexpr (std::is_void_v<error_type>) {
      return;
    } else {
      return std::move(error_).get();
    }
  }

  HT_ALWAYS_INLINE decltype(auto) unwrap_err() const & {
    if (!is_err()) {
      throw result_unwrap_error{"unwrap failed"};
    }

    if constexpr (std::is_void_v<error_type>) {
      return;
    } else {
      return error_.get();
    }
  }

  HT_ALWAYS_INLINE decltype(auto) unwrap_err() const && {
    if (!is_err()) {
      throw result_unwrap_error{"unwrap failed"};
    }

    if constexpr (std::is_void_v<error_type>) {
      return;
    } else {
      return std::move(error_).get();
    }
  }
};

template<typename T>
HT_ALWAYS_INLINE __impl::temp_wrapper<__impl::value_tag, T> ok(T value) {
  return {std::move(value)};
}

HT_ALWAYS_INLINE __impl::temp_wrapper<__impl::value_tag, void> ok() {
  return {};
}

template<typename T>
HT_ALWAYS_INLINE __impl::temp_wrapper<__impl::error_tag, T> err(T value) {
  return {std::move(value)};
}

HT_ALWAYS_INLINE __impl::temp_wrapper<__impl::error_tag, void> err() {
  return {};
}

template<typename T>
inline constexpr bool is_result_v = false;

template<typename T, typename U>
inline constexpr bool is_result_v<result<T, U>> = true;

}  // namespace ht

// vim: et sw=2 ts=2
