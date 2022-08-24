// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include <list>
#include <memory>
#include <queue>
#include <stdexcept>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

#include "fmt/format.h"
#include "ht/strings/stringify.hpp"

namespace ht {

template<typename Ch = char>
struct _basic_ac_automaton_node {
  std::unordered_map<Ch, _basic_ac_automaton_node *> next_;
  int finished_{-1};
  _basic_ac_automaton_node *failed_{nullptr};
  bool is_root_{false};
  uint32_t index_{0};

  _basic_ac_automaton_node *next(Ch ch);
};

template<typename T>
_basic_ac_automaton_node<T> *_basic_ac_automaton_node<T>::next(T ch) {
  if (auto it = next_.find(ch); it == next_.end()) {
    if (is_root_) {
      next_[ch] = this;
    } else {
      next_[ch] = failed_->next(ch);
    }
  }
  return next_[ch];
}

template<typename Ch = char>
class basic_ac_automaton {
 public:
  using str_t      = std::basic_string<Ch>;
  using str_view_t = std::basic_string_view<Ch>;
  using node_t     = _basic_ac_automaton_node<Ch>;

  basic_ac_automaton();
  basic_ac_automaton(basic_ac_automaton &&) noexcept = default;

  void push(str_view_t pattern);

  void build();

  struct QueryResult {
    str_view_t matched;
    uint32_t start_pos;
  };
  std::vector<QueryResult> query(str_view_t pattern) const;

 private:
  node_t *new_node();

  node_t *push_internal(str_view_t pattern);

 private:
  std::list<std::unique_ptr<node_t>> nodes_;
  std::vector<str_t> patterns_;
  node_t *root_;
  bool built_{false};
};

template<typename T>
basic_ac_automaton<T>::basic_ac_automaton() {
  root_ = new_node();
}

template<typename T>
typename basic_ac_automaton<T>::node_t *basic_ac_automaton<T>::new_node() {
  nodes_.push_back(std::make_unique<node_t>());
  auto n    = nodes_.back().get();
  n->index_ = nodes_.size();
  return n;
}

template<typename T>
typename basic_ac_automaton<T>::node_t *basic_ac_automaton<T>::push_internal(
    str_view_t pattern) {
  auto cur = root_;

  for (size_t i = 0; i < pattern.length(); i++) {
    auto &nxt = cur->next_[pattern[i]];
    if (nxt == nullptr) {
      nxt = new_node();
    }

    cur = nxt;
  }

  return cur;
}

template<typename T>
void basic_ac_automaton<T>::push(str_view_t pattern) {
  if (built_) {
    throw std::runtime_error(
        "Should not push patterns after build has been invoked");
  }

  node_t *cur = push_internal(pattern);
  if (cur->finished_ == -1) {
    cur->finished_ = patterns_.size();
    patterns_.push_back(str_t{pattern});
  }
}

template<typename T>
void basic_ac_automaton<T>::build() {
  std::queue<node_t *> Q;
  root_->failed_  = root_;
  root_->is_root_ = true;

  for (auto &[ch, node] : root_->next_) {
    node->failed_ = root_;
    Q.push(node);
  }

  while (!Q.empty()) {
    auto cur = Q.front();
    Q.pop();

    for (auto &[ch, node] : cur->next_) {
      node->failed_ = cur->failed_->next(ch);
      Q.push(node);
    }
  }
}

template<typename T>
std::vector<typename basic_ac_automaton<T>::QueryResult>
basic_ac_automaton<T>::query(str_view_t pattern) const {
  std::vector<QueryResult> result;
  node_t *cur = root_;
  for (size_t i = 0; i < pattern.length(); i++) {
    cur      = cur->next(pattern[i]);
    auto tmp = cur;
    while (tmp != root_) {
      if (tmp->finished_ != -1) {
        QueryResult res;
        res.matched   = patterns_[tmp->finished_];
        res.start_pos = i - res.matched.length() + 1;
        result.push_back(std::move(res));
      }
      tmp = tmp->failed_;
    }
  }

  return result;
}

using ac_automaton = basic_ac_automaton<>;

template<typename T>
auto tag_invoke(ht::tag_t<ht::stringify>,
                const _basic_ac_automaton_node<T> &node, uint16_t, int16_t) {
  if (node.is_root_) {
    return "root";
  }
  return fmt::format("node_{}", node.index_);
}

template<typename T>
auto tag_invoke(ht::tag_t<ht::stringify>, const basic_ac_automaton<T> &v,
                uint16_t, int16_t) {
  using fmt::operator""_a;

  std::ostringstream os;
  os << "#@startdot\n";
  os << "digraph AcAutomaton {\n";

  os << fmt::format("// nodes count: {}\n", v.nodes_.size());

  // define all nodes first
  for (auto &node : v.nodes_) {
    os << fmt::format(
        "{name}[label=\"{label}\", shape=\"box\", style=filled, "
        "fillcolor=\"{color}\"]\n",
        "label"_a = node.GetLabel(), "name"_a = *node,
        "color"_a = node.finished_ == -1 ? "#FFFFFF" : "#ADFF2F");
  }

  // define "next" edges
  for (auto &node : v.nodes_) {
    for (auto it : node.next_) {
      os << fmt::format("{src}->{tgt}[label=\"{ch}\"]\n", "src"_a = *node,
                        "tgt"_a = *it.second, "ch"_a = it.first);
    }
  }

  os << "edge[color=\"#FF6347\"]\n";

  // define "failed" edges
  for (auto &node : v.nodes_) {
    os << fmt::format("{src}->{tgt}[label=\"failed\"]\n", "src"_a = *node,
                      "tgt"_a = *node.failed_);
  }

  os << "}\n";
  os << "#@enddot\n";
  return os.str();
}

}  // namespace ht

// vim: et sw=2 ts=2
