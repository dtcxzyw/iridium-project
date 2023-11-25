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
#include "iridium/DT/IntrusiveList.hpp"
#include "iridium/DT/SmallVector.hpp"
#include "iridium/IR/Value.h"
#include "iridium/Support/OutputStream.hpp"

namespace iridium {
class Operator;

class Operand final : public Value, public IntrusiveListNode<Operand> {
public:
  Operand(Operator &Parent, TrackedValue &Use);
  ~Operand() override;
  void replaceWith(TrackedValue &NewUse);
  [[nodiscard]] Operator &getParent() const noexcept { return Parent; }
  [[nodiscard]] OutputIterator print(OutputIterator It) const override;

private:
  Operator &Parent;
  TrackedValue *ValueUse;
};

class Result final : public TrackedValue {
public:
  Result(Operator &Parent, const Type &Type, const Name &Name)
      : TrackedValue(Type, Name), Parent(Parent) {}
  [[nodiscard]] Operator &getParent() const { return Parent; }

private:
  Operator &Parent;
};

struct OperatorTraitTagStorage {};
using OperatorTraitTag = const OperatorTraitTagStorage *;
class OperatorTrait;

class OperatorImpl {
public:
  OperatorImpl() = default;
  OperatorImpl(const OperatorImpl &) = delete;
  OperatorImpl &operator=(const OperatorImpl &) = delete;
  OperatorImpl(OperatorImpl &&) = delete;
  OperatorImpl &operator=(OperatorImpl &&) = delete;
  virtual ~OperatorImpl() = default;

  [[nodiscard]] virtual OutputIterator print(OutputIterator It) const = 0;
  [[nodiscard]] virtual OutputIterator print(const Operator &Op,
                                             OutputIterator It) const = 0;

  template <typename Trait> [[nodiscard]] bool hasImpl() const noexcept {
    return getTrait(Trait::getIdentifier());
  }
  template <typename Trait> [[nodiscard]] const Trait &impl() const noexcept {
    auto Ptr = implIfPresent<Trait>();
    assert(Ptr);
    return *Ptr;
  }
  template <typename Trait>
  [[nodiscard]] const Trait *implIfPresent() const noexcept {
    return *reinterpret_cast<const Trait *>(getTrait(Trait::getIdentifier()));
  }

protected:
  virtual const OperatorTrait *getTrait(OperatorTraitTag Tag) const noexcept {
    return nullptr;
  }
};

class Operator final : public IntrusiveListNode<Operator> {
public:
  Operator(const OperatorImpl &OpImpl) : OpImpl(OpImpl) {}
  Operator(const Operator &) = delete;
  Operator &operator=(const Operator &) = delete;
  Operator(Operator &&) = delete;
  Operator &operator=(Operator &&) = delete;
  virtual ~Operator() = default;

  PtrVectorRef<Result> &results() { return Results; }
  PtrVectorRef<Operand> &operands() { return Operands; }
  [[nodiscard]] const PtrVectorRef<Result> &results() const { return Results; }
  [[nodiscard]] const PtrVectorRef<Operand> &operands() const {
    return Operands;
  }
  [[nodiscard]] const OperatorImpl &getImpl() const noexcept { return OpImpl; }
  [[nodiscard]] bool isTriviallyDead() const;

  void addResult(const Type &Type, const Name &Name = Name::empty());
  void addOperand(TrackedValue &Value);

  [[nodiscard]] OutputIterator print(OutputIterator It) const;

private:
  const OperatorImpl &OpImpl;
  SmallPtrVector<Result, 2> Results;
  SmallPtrVector<Operand, 2> Operands;
  // TODO: Op Attributes
};

// class PoisonOperator final : public Operator {
// public:
//   PoisonOperator(const Type &Type);
//   [[nodiscard]] OutputIterator print(OutputIterator It) const override;
// };

// class MergeStateOperator final : public Operator {
// public:
//   MergeStateOperator(const PtrArrayRef<TrackedValue> &States);
//   [[nodiscard]] OutputIterator print(OutputIterator It) const override;
// };
} // namespace iridium

template <>
struct fmt::formatter<iridium::OperatorImpl>
    : public iridium::DefaultFormatter<iridium::OperatorImpl> {};
template <>
struct fmt::formatter<iridium::Operator>
    : public iridium::DefaultFormatter<iridium::Operator> {};
