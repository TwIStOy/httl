// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include <utility>

#include <ht/macro/for.h>
#include <ht/macro/is_empty.h>
#include <ht/macro/select.h>
#include <ht/macro/tuple.h>
#include <ht/macro/expand.hpp>

#define STEAL_FIELD(...)        (_STEAL_FIELD, __VA_ARGS__)
#define STEAL_METHOD(...)       (_STEAL_METHOD, _STALER_EMPTY(), __VA_ARGS__)
#define STEAL_CONST_METHOD(...) (_STEAL_METHOD, const, __VA_ARGS__)
#define STEAL_QUALIFIED_METHOD(qualifier, ...) \
  (_STEAL_METHOD, qualifier, __VA_ARGS__)

#define STEALER(name, cls, ...) \
  _STEALER_I(name, cls, _STEALER_PREPARE(cls, __VA_ARGS__))

// impl {{{

#define _STEALER_PREPARE(cls, ...)                                            \
  HT_FOR(HT_COUNT_ARG(__VA_ARGS__), _STEALER_PREPARE_DO, _STEALER_COMMA, cls, \
         __VA_ARGS__)

#define _STEALER_FILTER_FIELDS(action, ...) \
  _STEALER_FILTER(_STEALER_IS_FIELD, action, __VA_ARGS__)

#define _STEALER_FILTER_FIELDS2(action, ...) \
  _STEALER_FILTER2(_STEALER_IS_FIELD, action, __VA_ARGS__)

#define _STEALER_FILTER_METHODS(action, ...) \
  _STEALER_FILTER(_STEALER_IS_METHOD, action, __VA_ARGS__)

#define _STEALER_FILTER(checker, action, ...)                              \
  HT_FOR(HT_COUNT_ARG(__VA_ARGS__), _STEALER_FILTER_ACTION, _STALER_EMPTY, \
         checker, action, __VA_ARGS__)

#define _STEALER_FILTER2(checker, action, ...)                              \
  HT_FOR(HT_COUNT_ARG(__VA_ARGS__), _STEALER_FILTER_ACTION, _STEALER_COMMA, \
         checker, action, __VA_ARGS__)

#define _STEALER_COMMA() ,

#define _STALER_EMPTY(...)

// --- filter --- {{{

#define _STEALER_FILTER_ACTION(i, checker, action, ...) \
  HT_EXPAND(                                            \
      _STEALER_FILTER_ACTION_I(checker, action, HT_SELECT(i, __VA_ARGS__)))
#define _STEALER_FILTER_ACTION_I(checker, action, x)                  \
  HT_IF(HT_IS_TUPLE(x), _STEALER_FILTER_ACTION_I_DO, checker, action, \
        HT_TUPLE_TO_VARS(x))
#define _STEALER_FILTER_ACTION_I_DO(checker, action, type, ...)               \
  _STEALER_FILTER_ACTION_I_DO_I(HT_UNDERLIND_CONCAT(checker, type)(), action, \
                                __VA_ARGS__)
#define _STEALER_FILTER_ACTION_I_DO_I(cond, action, ...)              \
  HT_EXPAND(HT_UNDERLIND_CONCAT(_STEALER_FILTER_ACTION_I_DO_I, cond)( \
      action, __VA_ARGS__))

#define _STEALER_FILTER_ACTION_I_DO_I_0(...)  // nothing...
#define _STEALER_FILTER_ACTION_I_DO_I_1(action, ...) \
  HT_EXPAND(action(__VA_ARGS__))

// }}}

// --- prepare --- {{{

#define _STEALER_PREPARE_DO(i, ...) \
  HT_EXPAND(_STEALER_PREPARE_DO_I(i, __VA_ARGS__))
#define _STEALER_PREPARE_DO_I(i, cls, ...)                                 \
  HT_IF(HT_IS_TUPLE(HT_SELECT(i, __VA_ARGS__)), _STEALER_PREPARE_DO_II, i, \
        cls, HT_TUPLE_TO_VARS(HT_SELECT(i, __VA_ARGS__)))
#define _STEALER_PREPARE_DO_II(i, cls, ...) \
  HT_EXPAND(_STEALER_PREPARE_DO_III(i, cls, __VA_ARGS__))
#define _STEALER_PREPARE_DO_III(i, cls, type, ...) (type, i, cls, __VA_ARGS__)

//}}}

// -- names define --- {{{

#define _STEALER_SLOT_NAME(id)          _STEALER_SLOT_NAME_I(id, __LINE__)
#define _STEALER_SLOT_NAME_I(id, line)  _STEALER_SLOT_NAME_II(id, line)
#define _STEALER_SLOT_NAME_II(id, line) _slot_##id##_##line

#define _STEALER_MOULD_NAME          _STEALER_MOULD_NAME_I(__LINE__)
#define _STEALER_MOULD_NAME_I(line)  _STEALER_MOULD_NAME_II(line)
#define _STEALER_MOULD_NAME_II(line) _mould_##line

#define _STEALER_REPRODUCE_NAME          _STEALER_REPRODUCE_NAME_I(__LINE__)
#define _STEALER_REPRODUCE_NAME_I(line)  _STEALER_REPRODUCE_NAME_II(line)
#define _STEALER_REPRODUCE_NAME_II(line) __reproduce_##line

// }}}

// -- checker -- {{{
#define _STEALER_IS_FIELD__STEAL_FIELD(...)  1
#define _STEALER_IS_FIELD__STEAL_METHOD(...) 0

#define _STEALER_IS_METHOD__STEAL_FIELD(...)  0
#define _STEALER_IS_METHOD__STEAL_METHOD(...) 1
// }}}

#define _STEALER_PREPARE_FIELD_I(id, cls, type, name)                     \
  struct _STEALER_SLOT_NAME(id) {                                         \
    using value_type  = type;                                             \
    using member_type = value_type(cls::*);                               \
    friend member_type _STEALER_REPRODUCE_NAME(_STEALER_SLOT_NAME(id) *); \
  };                                                                      \
  template struct __stealer::_STEALER_MOULD_NAME<_STEALER_SLOT_NAME(id),  \
                                                 &cls::name>;

#define _STEALER_PREPARE_METHOD_I(id, clz, qualifier, ret_type, name, ...) \
  struct _STEALER_SLOT_NAME(id) {                                          \
    using return_type = ret_type;                                          \
    using member_type = ret_type (clz::*)(__VA_ARGS__) qualifier;          \
    friend member_type _STEALER_REPRODUCE_NAME(_STEALER_SLOT_NAME(id) *);  \
  };                                                                       \
  template struct __stealer::_STEALER_MOULD_NAME<_STEALER_SLOT_NAME(id),   \
                                                 &clz::name>;

#define _STEALER_DECL_FIELDS_I(id, clz, type, name) type& name;

#define _STEALER_FIELD_GETTERS_I(id, clz, type, name)                   \
  __stealer::_STEALER_SLOT_NAME(id)::value_type& HT_UNDERLIND_CONCAT(   \
      _steal_field, name)() {                                           \
    return object_->*_STEALER_REPRODUCE_NAME(                           \
                         (__stealer::_STEALER_SLOT_NAME(id) *)nullptr); \
  }

#define _STEALER_DECL_METHOD_I(id, clz, qualifier, ret_type, name, ...)       \
  template<typename... Args>                                                  \
  __stealer::_STEALER_SLOT_NAME(id)::return_type name(Args&&...args)          \
      qualifier {                                                             \
    return (object_->*_STEALER_REPRODUCE_NAME((__stealer::_STEALER_SLOT_NAME( \
                          id) *)nullptr))(std::forward<Args>(args)...);       \
  }                                                                           \
  __stealer::_STEALER_SLOT_NAME(                                              \
      id)::member_type _steal_function_pointer_##name() {                     \
    return _STEALER_REPRODUCE_NAME(                                           \
        (__stealer::_STEALER_SLOT_NAME(id) *)nullptr);                        \
  }

#define _STEALER_INITIALIZOR_I(id, cls, type, name) \
  , name(HT_UNDERLIND_CONCAT(_steal_field, name)())

// --- decl methods --- {{{

#define _STEALER_ARGS_WITH_NAME_I(...)                                     \
  HT_UNDERLIND_CONCAT(_STEALER_ARGS_WITH_NAME_I, HT_IS_EMPTY(__VA_ARGS__)) \
  (__VA_ARGS__)
#define _STEALER_ARGS_WITH_NAME_ACTION(i, ...) HT_SELECT(i, __VA_ARGS__) a##i

#define _STEALER_ARGS_WITH_NAME_I_1(...)
#define _STEALER_ARGS_WITH_NAME_I_0(...)                            \
  HT_FOR(HT_COUNT_ARG(__VA_ARGS__), _STEALER_ARGS_WITH_NAME_ACTION, \
         _STEALER_COMMA, __VA_ARGS__)

#define _STEALER_ARGS_ONLY_NAME_I(...)                                     \
  HT_UNDERLIND_CONCAT(_STEALER_ARGS_ONLY_NAME_I, HT_IS_EMPTY(__VA_ARGS__)) \
  (__VA_ARGS__)
#define _STEALER_ARGS_ONLY_NAME_ACTION(i, ...) a##i

#define _STEALER_ARGS_ONLY_NAME_I_1(...)
#define _STEALER_ARGS_ONLY_NAME_I_0(...)                            \
  HT_FOR(HT_COUNT_ARG(__VA_ARGS__), _STEALER_ARGS_ONLY_NAME_ACTION, \
         _STEALER_COMMA, __VA_ARGS__)

// }}}

// }}}

#define _STEALER_I(name, cls, ...)                                           \
  namespace __stealer {                                                      \
  template<typename Slot, typename Slot::member_type K>                      \
  struct _STEALER_MOULD_NAME {                                               \
    friend typename Slot::member_type _STEALER_REPRODUCE_NAME(Slot *) {      \
      return K;                                                              \
    }                                                                        \
  };                                                                         \
  _STEALER_FILTER_FIELDS(_STEALER_PREPARE_FIELD_I, __VA_ARGS__)              \
  _STEALER_FILTER_METHODS(_STEALER_PREPARE_METHOD_I, __VA_ARGS__)            \
  }                                                                          \
  class name {                                                               \
    using private_t = cls;                                                   \
    private_t *object_;                                                      \
                                                                             \
   public:                                                                   \
    explicit name(private_t *object)                                         \
        : object_(object)                                                    \
              _STEALER_FILTER_FIELDS(_STEALER_INITIALIZOR_I, __VA_ARGS__) {} \
    explicit name(private_t& object)                                         \
        : object_(&object)                                                   \
              _STEALER_FILTER_FIELDS(_STEALER_INITIALIZOR_I, __VA_ARGS__) {} \
    _STEALER_FILTER_FIELDS(_STEALER_DECL_FIELDS_I, __VA_ARGS__)              \
    _STEALER_FILTER_FIELDS(_STEALER_FIELD_GETTERS_I, __VA_ARGS__)            \
    _STEALER_FILTER_METHODS(_STEALER_DECL_METHOD_I, __VA_ARGS__)             \
  };

// vim: fdm=marker
