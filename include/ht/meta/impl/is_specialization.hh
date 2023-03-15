// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include <type_traits>

namespace ht {

template<typename T, template<typename...> class Template>
struct is_specialization : std::false_type {};

template<template<typename...> class Template, typename... Args>
struct is_specialization<Template<Args...>, Template> : std::true_type {};

}  // namespace ht
