// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include <concepts>
#include <cstddef>
#include <cstdint>
#include <iterator>
#include <optional>
#include <ranges>
#include <stdexcept>
#include <utility>
#include <vector>

#include <fmt/format.h>

#include <ht/core/box.hpp>

namespace ht {

template<typename T>
class circular_deque {
 public:
  using value_type      = T;
  using size_type       = std::size_t;
  using difference_type = std::ptrdiff_t;
  using reference       = value_type&;
  using const_reference = const value_type&;
  using pointer         = value_type *;
  using const_pointer   = const value_type *;

  struct iterator;
  struct const_iterator;
  using reverse_iterator       = std::reverse_iterator<iterator>;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;

 public:
  explicit circular_deque(size_type count)
      : buffer_(count + 1), max_size_(count) {
  }

  circular_deque(const circular_deque& rhs);
  circular_deque(circular_deque&& rhs) noexcept;

  /// element access
  /// --------------

  reference at(size_type pos);
  const_reference at(size_type pos) const;

  reference operator[](size_type pos);
  const_reference operator[](size_type pos) const;

  reference front();
  const_reference front() const;

  reference back();
  const_reference back() const;

  // missing `data()`

  /// iterators
  /// ---------
  iterator begin() noexcept;
  const_iterator begin() const noexcept;
  const_iterator cbegin() const noexcept;

  iterator end() noexcept;
  const_iterator end() const noexcept;
  iterator cend() noexcept;

  reverse_iterator rbegin() noexcept;
  const_reverse_iterator rbegin() const noexcept;
  const_reverse_iterator crbegin() const noexcept;

  reverse_iterator rend() noexcept;
  const_reverse_iterator rend() const noexcept;
  const_reverse_iterator crend() const noexcept;

  /// capacity
  /// --------
  [[nodiscard]] bool empty() const;
  [[nodiscard]] size_type size() const;
  [[nodiscard]] size_type max_size() const;
  [[nodiscard]] size_type capacity() const;

  /// modifiers
  /// ---------

  void clear();

  std::optional<iterator> insert(const_iterator pos, const T& value);
  std::optional<iterator> insert(const_iterator pos, T&& value);
  std::optional<iterator> insert(const_iterator pos, size_type count,
                                 const T& value);

  template<typename InputIt>
  iterator insert(const_iterator pos, InputIt first, InputIt last);
  iterator insert(const_iterator pos, std::initializer_list<T> ilist);

  template<typename... Args>
  std::optional<iterator> emplace(const_iterator pos, Args&&...args);

  iterator erase(const_iterator pos);
  iterator erase(const_iterator first, const_iterator last);

  bool push_front(const T& value);
  bool push_front(T&& value);
  bool push_back(const T& value);
  bool push_back(T&& value);

  template<typename... Args>
  std::optional<reference> emplace_back(Args&&...args);
  template<typename... Args>
  std::optional<reference> emplace_front(Args&&...args);

  void pop_back();
  void pop_front();

  void resize(size_type count);
  void resize(size_type count, const value_type& value);

  void swap(circular_deque& rhs) noexcept;

  friend void swap(circular_deque& lhs, circular_deque& rhs) noexcept {
    lhs.swap(rhs);
  }

  template<std::ranges::sized_range U>
    requires std::same_as<value_type, std::ranges::range_value_t<U>>
  auto same_elements(const U& rhs) -> bool {
    if (size() != std::ranges::size(rhs)) {
      return false;
    }
    auto it  = begin();
    auto it2 = std::ranges::begin(rhs);
    for (; it != end(); ++it, ++it2) {
      if (*it != *it2) {
        return false;
      }
    }
    return true;
  }

 private:
  inline void range_check(size_type pos) const;

  inline reference at_nocheck(size_type pos) noexcept;
  inline const_reference at_nocheck(size_type pos) const noexcept;

  inline size_type previous(size_type pos, size_type step = 1) noexcept;
  inline size_type next(size_type pos, size_type step = 1) noexcept;

  void move_element_forward(size_type begin, size_type end, int cnt);

 private:
  std::vector<box<T>> buffer_;

  size_type max_size_;
  size_type begin_{0};
  size_type end_{0};
};

template<typename T>
struct circular_deque<T>::const_iterator {
  const_iterator(circular_deque<T> *d, size_type index)
      : deque_(d), index_(index) {
  }

  const_iterator(const const_iterator&) = default;

  const T& operator*() const noexcept {
    return deque_->at_nocheck(index_);
  }

  const T *operator->() const noexcept {
    return &(deque_->at_nocheck(index_));
  }

  const_iterator& operator++() noexcept {
    index_ = deque_->next(index_);
    return *this;
  }

  const_iterator operator++(int) noexcept {
    const_iterator ret = *this;

    index_ = deque_->next(index_);
    return ret;
  }

  const_iterator& operator--() noexcept {
    index_ = deque_->previous(index_);
    return *this;
  }

  const_iterator operator--(int) noexcept {
    const_iterator ret = *this;

    index_ = deque_->previous(index_);
    return ret;
  }

  friend const_iterator operator+(const const_iterator& iter,
                                  difference_type offset) noexcept {
    const_iterator ret = iter;
    ret.index_         = ret.deque_->next(ret.index_, offset);
    return ret;
  }

  const_iterator& operator+=(difference_type offset) noexcept {
    index_ = deque_->next(index_, offset);
    return *this;
  }

  friend const_iterator operator-(const const_iterator& iter,
                                  difference_type offset) noexcept {
    const_iterator ret = iter;
    ret.index_         = ret.deque_->previous(ret.index_, offset);
    return ret;
  }

  const_iterator& operator-=(difference_type offset) noexcept {
    index_ = deque_->previous(index_, offset);
    return *this;
  }

  friend std::ptrdiff_t operator-(const const_iterator& lhs,
                                  const const_iterator& rhs) noexcept {
    std::ptrdiff_t diff = lhs.offset();
    return diff - rhs.offset();
  }

  friend bool operator==(const const_iterator& lhs,
                         const const_iterator& rhs) noexcept {
    return lhs.index_ == rhs.index_;
  }

  friend bool operator!=(const const_iterator& lhs,
                         const const_iterator& rhs) noexcept {
    return !(lhs == rhs);
  }

  friend bool operator<(const const_iterator& lhs,
                        const const_iterator& rhs) noexcept {
    return lhs.offset() < rhs.offset();
  }

  friend bool operator<=(const const_iterator& lhs,
                         const const_iterator& rhs) noexcept {
    return !(lhs > rhs);
  }

  friend bool operator>(const const_iterator& lhs,
                        const const_iterator& rhs) noexcept {
    return lhs.offset() > rhs.offset();
  }

  friend bool operator>=(const const_iterator& lhs,
                         const const_iterator& rhs) noexcept {
    return !(lhs < rhs);
  }

 private:
  size_type offset() {
    if (index_ >= deque_->begin_) {
      return index_ - deque_->begin_;
    } else {
      return deque_->capacity() - deque_->begin_ + index_;
    }
  }

  const circular_deque<T> *deque_;
  circular_deque<T>::size_type index_;
};

template<typename T>
struct circular_deque<T>::iterator {
  iterator(circular_deque<T> *d, size_type index) : deque_(d), index_(index) {
  }

  iterator(const iterator&) = default;

  T& operator*() const noexcept {
    return const_cast<T&>(deque_->at_nocheck(index_));
  }

  T *operator->() const noexcept {
    return &(const_cast<T&>(deque_->at_nocheck(index_)));
  }

  iterator& operator++() noexcept {
    index_ = deque_->next(index_);
    return *this;
  }

  iterator operator++(int) noexcept {
    iterator ret = *this;

    index_ = deque_->next(index_);
    return ret;
  }

  iterator& operator--() noexcept {
    index_ = deque_->previous(index_);
    return *this;
  }

  iterator operator--(int) noexcept {
    iterator ret = *this;

    index_ = deque_->previous(index_);
    return ret;
  }

  friend iterator operator+(const iterator& iter,
                            difference_type offset) noexcept {
    iterator ret = iter;
    ret.index_   = ret.deque_->next(ret.index_, offset);
    return ret;
  }

  iterator& operator+=(difference_type offset) noexcept {
    index_ = deque_->next(index_, offset);
    return *this;
  }

  friend iterator operator-(const iterator& iter,
                            difference_type offset) noexcept {
    iterator ret = iter;
    ret.index_   = ret.deque_->previous(ret.index_, offset);
    return ret;
  }

  iterator& operator-=(difference_type offset) noexcept {
    index_ = deque_->previous(index_, offset);
    return *this;
  }

  friend std::ptrdiff_t operator-(const iterator& lhs,
                                  const iterator& rhs) noexcept {
    std::ptrdiff_t diff = lhs.offset();
    return diff - rhs.offset();
  }

  friend bool operator==(const iterator& lhs, const iterator& rhs) noexcept {
    return lhs.index_ == rhs.index_;
  }

  friend bool operator!=(const iterator& lhs, const iterator& rhs) noexcept {
    return !(lhs == rhs);
  }

  friend bool operator<(const iterator& lhs, const iterator& rhs) noexcept {
    return lhs.offset() < rhs.offset();
  }

  friend bool operator<=(const iterator& lhs, const iterator& rhs) noexcept {
    return !(lhs > rhs);
  }

  friend bool operator>(const iterator& lhs, const iterator& rhs) noexcept {
    return lhs.offset() > rhs.offset();
  }

  friend bool operator>=(const iterator& lhs, const iterator& rhs) noexcept {
    return !(lhs < rhs);
  }

 private:
  size_type offset() {
    if (index_ >= deque_->begin_) {
      return index_ - deque_->begin_;
    } else {
      return deque_->capacity() - deque_->begin_ + index_;
    }
  }

  circular_deque<T> *deque_;
  circular_deque<T>::size_type index_;
};

template<typename T>
inline auto circular_deque<T>::range_check(size_type pos) const -> void {
  if (pos >= size()) [[unlikely]] {
    throw std::out_of_range(
        fmt::format("circular_deque::range_check: pos (which is {}) >= "
                    "this->size() (which is {})",
                    pos, size()));
  }
}

template<typename T>
auto circular_deque<T>::previous(size_type pos, size_type step) noexcept
    -> size_type {
  if (pos < step) {
    return capacity() + pos - step;
  } else {
    return pos - step;
  }
}

template<typename T>
auto circular_deque<T>::next(size_type pos, size_type step) noexcept
    -> size_type {
  return (pos + step) % capacity();
}

template<typename T>
auto circular_deque<T>::at(size_type pos) -> reference {
  range_check(pos);
  return operator[](pos);
}

template<typename T>
auto circular_deque<T>::at(size_type pos) const -> const_reference {
  range_check(pos);
  return operator[](pos);
}

template<typename T>
auto circular_deque<T>::at_nocheck(size_type pos) const noexcept
    -> const_reference {
  auto real_pos = (begin_ + pos) % buffer_.size();
  return buffer_[real_pos].get();
}

template<typename T>
auto circular_deque<T>::at_nocheck(size_type pos) noexcept -> reference {
  auto real_pos = (begin_ + pos) % buffer_.size();
  return buffer_[real_pos].get();
}

template<typename T>
auto circular_deque<T>::operator[](size_type pos) -> reference {
  return at_nocheck(pos);
}

template<typename T>
auto circular_deque<T>::operator[](size_type pos) const -> const_reference {
  return at_nocheck(pos);
}

template<typename T>
auto circular_deque<T>::front() -> reference {
  return at_nocheck(begin_);
}

template<typename T>
auto circular_deque<T>::front() const -> const_reference {
  return at_nocheck(begin_);
}

template<typename T>
auto circular_deque<T>::back() -> reference {
  return at_nocheck(previous(end_));
}

template<typename T>
auto circular_deque<T>::back() const -> const_reference {
  return at_nocheck(previous(end_));
}

template<typename T>
auto circular_deque<T>::empty() const -> bool {
  return begin_ == end_;
}

template<typename T>
auto circular_deque<T>::size() const -> size_type {
  return (capacity() + end_ - begin_) % capacity();
}

template<typename T>
auto circular_deque<T>::max_size() const -> size_type {
  return max_size_;
}

template<typename T>
auto circular_deque<T>::capacity() const -> size_type {
  return buffer_.size();
}

template<typename T>
auto circular_deque<T>::begin() noexcept -> iterator {
  return iterator{this, begin_};
}

template<typename T>
auto circular_deque<T>::begin() const noexcept -> const_iterator {
  return const_iterator{this, begin_};
}

template<typename T>
auto circular_deque<T>::cbegin() const noexcept -> const_iterator {
  return const_iterator{this, begin_};
}

template<typename T>
auto circular_deque<T>::end() noexcept -> iterator {
  return iterator{this, end_};
}

template<typename T>
auto circular_deque<T>::end() const noexcept -> const_iterator {
  return const_iterator{this, end_};
}

template<typename T>
auto circular_deque<T>::cend() noexcept -> iterator {
  return const_iterator{this, end_};
}

template<typename T>
auto circular_deque<T>::rbegin() noexcept -> reverse_iterator {
  return std::make_reverse_iterator(end());
}

template<typename T>
auto circular_deque<T>::rbegin() const noexcept -> const_reverse_iterator {
  return std::make_reverse_iterator(cend());
}

template<typename T>
auto circular_deque<T>::crbegin() const noexcept -> const_reverse_iterator {
  return std::make_reverse_iterator(cend());
}

template<typename T>
auto circular_deque<T>::rend() noexcept -> reverse_iterator {
  return std::make_reverse_iterator(begin());
}

template<typename T>
auto circular_deque<T>::rend() const noexcept -> const_reverse_iterator {
  return std::make_reverse_iterator(cbegin());
}

template<typename T>
auto circular_deque<T>::crend() const noexcept -> const_reverse_iterator {
  return std::make_reverse_iterator(cbegin());
}

template<typename T>
auto circular_deque<T>::clear() -> void {
  for (auto i = begin_; i != end_; i = next(i)) {
    destruct_union_member(&buffer_[i]);
  }
}

template<typename T>
auto circular_deque<T>::push_back(const T& value) -> bool {
  if (size() == max_size()) {
    return false;
  }
  construct_union_member(&buffer_[end_], value);
  end_ = next(end_);
  return true;
}

template<typename T>
auto circular_deque<T>::push_back(T&& value) -> bool {
  if (size() == max_size()) {
    return false;
  }
  construct_union_member(&buffer_[end_], std::move(value));
  end_ = next(end_);
  return true;
}

template<typename T>
auto circular_deque<T>::push_front(const T& value) -> bool {
  if (size() == max_size()) {
    return false;
  }

  begin_ = previous(begin_);
  construct_union_member(&buffer_[begin_], value);
  return true;
}

template<typename T>
auto circular_deque<T>::push_front(T&& value) -> bool {
  if (size() == max_size()) {
    return false;
  }

  begin_ = previous(begin_);
  construct_union_member(&buffer_[begin_], std::move(value));
  return true;
}

template<typename T>
auto circular_deque<T>::insert(const_iterator pos, const T& value)
    -> std::optional<iterator> {
  return emplace(pos, value);
}

template<typename T>
auto circular_deque<T>::insert(const_iterator pos, T&& value)
    -> std::optional<iterator> {
  return emplace(pos, std::move(value));
}

template<typename T>
auto circular_deque<T>::insert(const_iterator pos, size_type count,
                               const T& value) -> std::optional<iterator> {
  if (size() + count > max_size() || pos.deque_ != this) {
    return std::nullopt;
  }

  // fast path at beginning
  if (pos == cbegin()) {
    for (auto i = previous(begin_, count); i != begin_; i = next(i)) {
      construct_union_member(&buffer_[i], value);
    }
    begin_ = previous(begin_, count);

    return begin();
  }

  move_element_forward(pos.index_, end_, count);
  end_ = next(end_, count);

  auto end = next(pos.index_, count);
  for (auto i = pos.index_; i != end; i = next(i)) {
    construct_union_member(&buffer_[i], value);
  }
  return iterator{this, pos.index_};
}

template<typename T>
template<typename... Args>
auto circular_deque<T>::emplace(const_iterator pos, Args&&...args)
    -> std::optional<iterator> {
  if (size() == max_size() || pos.deque_ != this) {
    return std::nullopt;
  }

  // fast path at beginning
  if (pos == cbegin()) {
    emplace_front(std::forward<Args>(args)...);
    return begin();
  }

  // move all element to next
  move_element_forward(pos.index_, end_, 1);
  end_ = next(end_);

  construct_union_member(buffer_[pos.index_], std::forward<Args>(args)...);
  return iterator{this, pos.index_};
}

template<typename T>
auto circular_deque<T>::move_element_forward(size_type begin, size_type end,
                                             int cnt) -> void {
  if (cnt == 0) {
    return;
  }

  if (cnt > 0) {
    for (auto i = next(end, cnt - 1);; i = previous(i)) {
      auto pi = previous(i, cnt);
      construct_union_member(&buffer_[i], std::move(buffer_[pi]).get());
      destruct_union_member(&buffer_[pi]);
      if (pi == begin) {
        break;
      }
    }
  } else {
    auto c = -cnt;
    for (auto i = begin; i != end; i = next(i)) {
      auto pi = previous(i, c);
      construct_union_member(&buffer_[pi], std::move(buffer_[i]).get());
      destruct_union_member(&buffer_[i]);
    }
  }
}

template<typename T>
template<typename InputIt>
auto circular_deque<T>::insert(const_iterator pos, InputIt first, InputIt last)
    -> iterator {
  auto count = std::distance(first, last);

  if (size() + count > max_size() || pos.deque_ != this) {
    return std::nullopt;
  }

  auto it = first;

  // fast path at beginning
  if (pos == cbegin()) {
    for (auto i = previous(begin_, count); i != begin_; i = next(i)) {
      construct_union_member(&buffer_[i], *it);
      ++it;
    }
    begin_ = previous(begin_, count);

    return begin();
  }

  move_element_forward(pos.index_, end_, count);
  end_ = next(end_, count);

  auto end = next(pos.index_, count);
  for (auto i = pos.index_; i != end; i = next(i)) {
    construct_union_member(&buffer_[i], *it);
    ++it;
  }
  return iterator{this, pos.index_};
}

template<typename T>
auto circular_deque<T>::insert(const_iterator pos,
                               std::initializer_list<T> ilist) -> iterator {
  auto count = ilist.size();

  if (size() + count > max_size() || pos.deque_ != this) {
    return std::nullopt;
  }

  auto it = ilist.begin();

  // fast path at beginning
  if (pos == cbegin()) {
    for (auto i = previous(begin_, count); i != begin_; i = next(i)) {
      construct_union_member(&buffer_[i], std::move(*it));
      ++it;
    }
    begin_ = previous(begin_, count);

    return begin();
  }

  move_element_forward(pos.index_, end_, count);
  end_ = next(end_, count);

  auto end = next(pos.index_, count);
  for (auto i = pos.index_; i != end; i = next(i)) {
    construct_union_member(&buffer_[i], std::move(*it));
    ++it;
  }
  return iterator{this, pos.index_};
}

template<typename T>
auto circular_deque<T>::erase(const_iterator pos) -> iterator {
  // fast path at beginning
  if (pos == cbegin()) {
    pop_front();
    return begin();
  }

  destruct_union_member(&buffer_[pos.index_]);
  move_element_forward(next(pos.index_), end_, -1);
  end_ = previous(end_);
  return iterator{this, pos.index_};
}

template<typename T>
auto circular_deque<T>::erase(const_iterator first, const_iterator last)
    -> iterator {
  auto cnt = std::distance(first, last);

  // fast path at beginning
  if (first == cbegin()) {
    while (cnt > 0) {
      pop_front();
    }
    return begin();
  }

  for (auto it = first; it != last; ++it) {
    destruct_union_member(&buffer_[it.index_]);
  }
  move_element_forward(last.index_, end_, -cnt);
  end_ = previous(end_, cnt);
  return iterator{this, first.index_};
}

template<typename T>
auto circular_deque<T>::pop_back() -> void {
  end_ = previous(end_);
  destruct_union_member(&buffer_[end_]);
}

template<typename T>
auto circular_deque<T>::pop_front() -> void {
  destruct_union_member(&buffer_[begin_]);
  begin_ = next(begin_);
}

template<typename T>
template<typename... Args>
auto circular_deque<T>::emplace_back(Args&&...args)
    -> std::optional<reference> {
  if (size() == max_size()) {
    return std::nullopt;
  }
  construct_union_member(&buffer_[end_], std::forward<Args>(args)...);
  auto& res = buffer_[end_];
  end_      = next(end_);
  return res;
}

template<typename T>
template<typename... Args>
auto circular_deque<T>::emplace_front(Args&&...args)
    -> std::optional<reference> {
  if (size() == max_size()) {
    return std::nullopt;
  }
  auto i = previous(begin_);
  construct_union_member(&buffer_[i], std::forward<Args>(args)...);
  auto& res = buffer_[i];
  begin_    = i;
  return res;
}

template<typename T>
auto circular_deque<T>::resize(size_type count) -> void {
  if (count > max_size()) {
    count = max_size();
  }
  if (count > size()) {
    // extend
    auto delta = count - size();
    while (delta > 0) {
      construct_union_member(&buffer_[end_]);
      end_ = next(end_);
      delta--;
    }
  } else {
    auto delta = size() - count;
    while (delta > 0) {
      pop_back();
      delta--;
    }
  }
}

template<typename T>
auto circular_deque<T>::resize(size_type count, const value_type& value)
    -> void {
  if (count > max_size()) {
    count = max_size();
  }
  if (count > size()) {
    // extend
    auto delta = count - size();
    while (delta > 0) {
      construct_union_member(&buffer_[end_], value);
      end_ = next(end_);
      delta--;
    }
  } else {
    auto delta = size() - count;
    while (delta > 0) {
      pop_back();
      delta--;
    }
  }
}

template<typename T>
auto circular_deque<T>::swap(circular_deque& rhs) noexcept -> void {
  buffer_.swap(rhs.buffer_);
  swap(max_size_, rhs.max_size_);
  swap(begin_, rhs.begin_);
  swap(end_, rhs.end_);
}

template<typename T>
circular_deque<T>::circular_deque(const circular_deque& rhs)
    : buffer_(rhs.max_size_ + 1),
      max_size_(rhs.max_size_),
      begin_(rhs.begin_),
      end_(rhs.end_) {
  for (auto i = begin_; i != end_; i = next(i)) {
    construct_union_member(&buffer_[i], rhs.buffer_[i].get());
  }
}

template<typename T>
circular_deque<T>::circular_deque(circular_deque&& rhs) noexcept
    : buffer_(rhs.max_size_ + 1),
      max_size_(rhs.max_size_),
      begin_(rhs.begin_),
      end_(rhs.end_) {
  for (auto i = begin_; i != end_; i = next(i)) {
    construct_union_member(&buffer_[i], std::move(rhs.buffer_[i]).get());
  }
}

}  // namespace ht

// vim: et sw=2 ts=2
