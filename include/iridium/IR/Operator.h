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
class Operand final : public Value, public IntrusiveListNode<Operand> {
public:
  Operand(class Operator &Parent, TrackedValue &Use);
  ~Operand() override;
  void replaceWith(TrackedValue &NewUse);
  [[nodiscard]] class Operator &getParent() const noexcept { return Parent; }
  [[nodiscard]] OutputIterator print(OutputIterator It) const override;

private:
  class Operator &Parent;
  TrackedValue *ValueUse;
};

class Result final : public TrackedValue {
public:
  Result(class Operator &Parent, const Type &Type, const Name &Name)
      : TrackedValue(Type, Name), Parent(Parent) {}
  [[nodiscard]] class Operator &getParent() const { return Parent; }

private:
  class Operator &Parent;
};

class Operator : public IntrusiveListNode<Operator> {
public:
  Operator() = default;
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
  [[nodiscard]] bool isTriviallyDead() const;

  void addResult(const Type &Type, const Name &Name = Name::empty());
  void addOperand(TrackedValue &Value);

  [[nodiscard]] virtual OutputIterator print(OutputIterator It) const = 0;

protected:
  enum class TypePrintMode { None, PrintFirst, PrintAll };

  [[nodiscard]] OutputIterator printNormal(OutputIterator It,
                                           std::string_view Name,
                                           TypePrintMode PrintMode) const;

private:
  SmallPtrVector<Result, 2> Results;
  SmallPtrVector<Operand, 2> Operands;
};

class PoisonOperator final : public Operator {
public:
  PoisonOperator(const Type &Type);
  [[nodiscard]] OutputIterator print(OutputIterator It) const override;
};

class MergeStateOperator final : public Operator {
public:
  MergeStateOperator(const PtrArrayRef<TrackedValue> &States);
  [[nodiscard]] OutputIterator print(OutputIterator It) const override;
};
} // namespace iridium
