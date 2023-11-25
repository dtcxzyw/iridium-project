// SPDX-License-Identifier: Apache-2.0
// Copyright 2023 Iridium authors
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once
#include <cstdint>

namespace iridium {

template <typename T> class IntrusiveList;
template <typename T> class IntrusiveListIterator;

template <typename T> class IntrusiveListNode {
public:
  friend class IntrusiveList<T>;
  friend class IntrusiveListIterator<T>;

  T &get() { return *static_cast<T *>(this); }

private:
  IntrusiveListNode<T> *Next = nullptr;
  IntrusiveListNode<T> *Prev = nullptr;
};

template <typename T> class IntrusiveListIterator final {
public:
  IntrusiveListIterator(IntrusiveListNode<T> *Node) : Node(Node) {}
  IntrusiveListIterator(IntrusiveListNode<T> &Node) : Node(&Node) {}
  T &operator*() { return Node->get(); }
  T *operator->() { return &Node->get(); }
  T &operator*() const { return Node->get(); }
  T *operator->() const { return &Node->get(); }
  IntrusiveListIterator &operator++() {
    Node = Node->Next;
    return *this;
  }
  IntrusiveListIterator &operator--() {
    Node = Node->Prev;
    return *this;
  }
  IntrusiveListIterator operator++(int) {
    auto Ret = *this;
    ++*this;
    return Ret;
  }
  IntrusiveListIterator operator--(int) {
    auto Ret = *this;
    --*this;
    return Ret;
  }
  bool operator==(const IntrusiveListIterator &Other) const {
    return Node == Other.Node;
  }
  bool operator!=(const IntrusiveListIterator &Other) const {
    return Node != Other.Node;
  }
  IntrusiveListNode<T> &get() { return *Node; }

private:
  IntrusiveListNode<T> *Node;
};

template <typename T> class IntrusiveList final {
public:
  IntrusiveList() : Size(0) {
    Head.Next = &Tail;
    Tail.Prev = &Head;
  }
  IntrusiveListIterator<T> begin() { return Head.Next; }
  IntrusiveListIterator<T> end() { return &Tail; }
  auto &front() { return Head.Next->get(); }
  auto &back() { return Tail.Prev->get(); }
  void insert(IntrusiveListIterator<T> Pos, IntrusiveListNode<T> &Node) {
    auto &Before = Pos.get();
    Node.Next = Before.Next;
    Node.Prev = &Before;
    Before.Next->Prev = &Node;
    Before.Next = &Node;
    ++Size;
  }
  void remove(IntrusiveListIterator<T> It) {
    auto &Node = It.get();
    Node.Next->Prev = Node.Prev;
    Node.Prev->Next = Node.Next;
    Node.Next = nullptr;
    Node.Prev = nullptr;
    --Size;
  }
  void destroy(IntrusiveListIterator<T> It) {
    remove(It);
    delete &It.get().get();
  }
  [[nodiscard]] uint32_t size() const noexcept { return Size; }
  [[nodiscard]] bool empty() const noexcept { return Size == 0; }

private:
  IntrusiveListNode<T> Head, Tail;
  uint32_t Size;
};

} // namespace iridium
