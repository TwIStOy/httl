// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include <concepts>
#include <coroutine>
#include <exception>
#include <functional>
#include <memory>
#include <typeindex>
#include <utility>

// ---

#include <ht/core/tag_invoke.hpp>

namespace ht::coro {

namespace _visit_coro_handle_cpo {
struct _fn {
  template<typename T, typename F,
           bool _noexcept = nothrow_tag_invocable<_fn, const T &, F &&>>
    requires tag_invocable<_fn, const T &, F &&>
  void operator()(const T &c, F &&func) const noexcept(_noexcept) {
    tag_invoke(_fn{}, c, std::forward<F>(func));
  }

  template<typename T, typename F>
    requires(!tag_invocable<_fn, const T &, F &&>)
  void operator()(const T &c, F &&func) const noexcept {
  }
};
inline const _fn visit_coro_handle;
}  // namespace _visit_coro_handle_cpo
// tag-invoke cpo function: visit_coro_handle
using _visit_coro_handle_cpo::visit_coro_handle;

// utility struct recording
//   type_info
//   visit underlying coroutine_handle
struct coro_info;

namespace _coro_info_impl {

struct _vtable {
  using callback_t          = void(const coro_info &, void *);
  using visitor_t           = void(const void *, callback_t *, void *);
  using type_index_getter_t = std::type_index();

  // virtual std::type_index type_index_getter();
  type_index_getter_t *type_index_getter;

  // virtual void visit(const void* coroutine_handle_address, callback_t* cb,
  //                    void* data);
  visitor_t *visit;
};

static inline constexpr auto _default_vtable =
    _vtable{.type_index_getter = []() -> std::type_index {
              struct __uninitialized {};
              return {typeid(__uninitialized)};
            },
            .visit =
                [](const void *, _vtable::callback_t *, void *) {
                }};

template<typename P>
inline std::type_index _type_index_for() noexcept {
  return {typeid(P)};
}

template<typename F>
void _invoke_visit(const _vtable &vt, void *fn) {
  std::invoke(*static_cast<std::add_pointer_t<F>>(fn), vt);
}

}  // namespace _coro_info_impl

template<typename P>
struct coro_handle;

struct coro_info {
  coro_info() = default;

  inline coro_info(void *address, const _coro_info_impl::_vtable *vt)
      : address_(address), vtable_(vt) {
  }

  static inline coro_info from_handler(const coro_info &p) {
    return p;
  }

  template<typename P>
  static inline coro_info from_handler(const coro_handle<P> &p) {
    return p.info();
  }

  template<typename P>
  static inline coro_info from_handler(std::coroutine_handle<P> p) {
    return coro_handle<P>(p).info();
  }

  // return wrapped type-info of Promise
  [[nodiscard]] std::type_index type() const noexcept {
    return vtable_->type_index_getter();
  }

  // return address of underlying std::coroutine_handle<P>
  [[nodiscard]] const void *address() const noexcept {
    return address_;
  }

  template<typename F>
  friend void tag_invoke(tag_t<visit_coro_handle>, const coro_info &c, F &&f) {
    c.vtable_->visit(c.address_, &_coro_info_impl::_invoke_visit<F>,
                     std::addressof(f));
  }

 private:
  template<typename P>
  friend struct coro_handle;

  // address of std::coroutine_handle
  const void *address_{nullptr};
  const _coro_info_impl::_vtable *vtable_{&_coro_info_impl::_default_vtable};
};

template<typename P = void>
struct coro_handle;

namespace _coro_handle_impl {

template<typename P>
std::coroutine_handle<> _done_callback_for(void *address) noexcept {
  return std::coroutine_handle<P>::from_address(address)
      .promise()
      .unhandled_done();
}

inline std::coroutine_handle<> default_done_callback(void *) {
  std::terminate();
}

struct vtable : _coro_info_impl::_vtable {
  using done_callback_t = std::coroutine_handle<>(void *);

  // virtual std::coroutine_handle<>(void* coro)
  // return next coroutine_handle after `coro` has done
  done_callback_t *done;
};

template<typename P>
void _visit_for(const void *address, vtable::callback_t *cb, void *data) {
  visit_coro_handle(
      const_cast<const P &>(
          std::coroutine_handle<P>::from_address(const_cast<void *>(address))
              .promise()),
      [cb, data](const auto &continuation) {
        cb(coro_info::from_handler(continuation), data);
      });
}

template<typename P>
inline constexpr vtable vtable_for{{
                                       &_coro_info_impl::_type_index_for<P>,
                                       &_visit_for<P>,
                                   },
                                   &_done_callback_for<P>};

}  // namespace _coro_handle_impl

template<>
struct coro_handle<void> {
  coro_handle() = default;

  template<typename P>
    requires(!std::same_as<P, void>)
  coro_handle(std::coroutine_handle<P> handle) noexcept
      : coro_handle(0, handle) {
  }

  explicit operator bool() const noexcept {
    return handle_ != nullptr;
  }

  [[nodiscard]] std::coroutine_handle<> handle() const noexcept {
    return handle_;
  }

  [[nodiscard]] std::coroutine_handle<> done() const noexcept {
    return vtable_->done(handle_.address());
  }

  void resume() {
    handle_.resume();
  }

  [[nodiscard]] coro_info info() const noexcept {
    return {handle().address(), vtable_};
  }

  template<typename F>
  friend void tag_invoke(tag_t<visit_coro_handle>, const coro_handle<> &c,
                         F &&f) {
    c.info().vtable_->visit(c.handle_.address(),
                            &_coro_info_impl::_invoke_visit<F>,
                            std::addressof(f));
  }

 private:
  friend coro_info;

  template<typename P>
  coro_handle(int, std::coroutine_handle<P> rhs);

  std::coroutine_handle<> handle_;
  static constexpr _coro_handle_impl::vtable _default_vtable{
      {
          _coro_info_impl::_default_vtable.type_index_getter,
          _coro_info_impl::_default_vtable.visit,
      },
      &_coro_handle_impl::default_done_callback};

  const _coro_handle_impl::vtable *vtable_{&_default_vtable};
};

template<typename P>
struct coro_handle {
  coro_handle() = default;

  coro_handle(std::coroutine_handle<P> handle) noexcept : impl_(handle) {
  }

  explicit operator bool() const noexcept {
    return !!impl_;
  }

  explicit operator coro_handle<>() const noexcept {
    return impl_;
  }

  std::coroutine_handle<P> handle() const noexcept {
    return std::coroutine_handle<P>::from_address(impl_.handle_.address());
  }

  [[nodiscard]] std::coroutine_handle<> done() const noexcept {
    return impl_.done();
  }

  void resume() {
    impl_.resume();
  }

  [[nodiscard]] coro_info info() const noexcept {
    return impl_.info();
  }

  [[nodiscard]] P &promise() const noexcept {
    return handle().promise();
  }

  template<typename F>
  friend void tag_invoke(tag_t<visit_coro_handle>, const coro_handle<P> &c,
                         F &&f) {
    visit_coro_handle(c.impl_, std::forward<F>(f));
  }

 private:
  friend coro_info;

  coro_handle<> impl_;
};

template<typename P>
coro_handle<>::coro_handle(int, std::coroutine_handle<P> rhs)
    : handle_(rhs), vtable_(&_coro_handle_impl::vtable_for<P>) {
}

}  // namespace ht::coro

// vim: et sw=2 ts=2
