// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include <stdexcept>
#include <variant>

namespace ht {

template<typename T, typename U>
class Result {
 public:
  using Value_t = T;
  using Error_t = U;

 private:
  struct __dummy {};

 public:
  static Result Ok(Value_t v);
  static Result Err(Error_t err);

  inline bool IsOk() const {
    return data_.index() == 1;
  }

  inline bool IsError() const {
    return data_.index() == 2;
  }

  Value_t Unwrap() && {
    if (!IsOk()) {
      // TODO(hawtian): use custom error
      throw std::runtime_error("");
    }
    return std::get<1>(std::move(data_));
  }

  template<typename NewError>
  Result<T, NewError> MapError(NewError err) && {
    if (IsOk()) {
      // is ok
      return Result<T, NewError>::Ok(std::get<1>(std::move(data_)));
    } else {
      return Result<T, NewError>::Err(std::move(err));
      // is error
    }
  }

 private:
  std::variant<__dummy, Value_t, Error_t> data_;
};

}  // namespace ht

// vim: et sw=2 ts=2
