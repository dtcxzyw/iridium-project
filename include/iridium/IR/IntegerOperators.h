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
#include "iridium/IR/OperatorTraits.h"
#include "iridium/Support/OutputStream.hpp"

namespace iridium {
class AddOperator final : public OperatorImplWithTraits<BinaryOperatorTrait> {
public:
  static const AddOperator &get();
  [[nodiscard]] OutputIterator print(OutputIterator It) const override;
  [[nodiscard]] bool isCommutative() const noexcept override { return true; }
  [[nodiscard]] bool isAssociative() const noexcept override { return true; }
  [[nodiscard]] bool
  matchIdentity(const ConstantValue &Value) const noexcept override;
  [[nodiscard]] const ConstantValue *
  getIdentity(const Type &Type) const noexcept override;
  [[nodiscard]] OutputIterator print(const Operator &Op,
                                     OutputIterator It) const override;
};
class SubOperator final : public OperatorImplWithTraits<BinaryOperatorTrait> {
public:
  static const SubOperator &get();
  [[nodiscard]] OutputIterator print(OutputIterator It) const override;
  [[nodiscard]] bool isCommutative() const noexcept override { return false; }
  [[nodiscard]] bool isAssociative() const noexcept override { return false; }
  [[nodiscard]] bool
  matchIdentity(const ConstantValue &) const noexcept override {
    return false;
  }
  [[nodiscard]] const ConstantValue *
  getIdentity(const Type &) const noexcept override {
    return nullptr;
  }
  [[nodiscard]] OutputIterator print(const Operator &Op,
                                     OutputIterator It) const override;
};
class MulOperator final : public OperatorImplWithTraits<BinaryOperatorTrait> {
public:
  static const MulOperator &get();
  [[nodiscard]] OutputIterator print(OutputIterator It) const override;
  [[nodiscard]] bool isCommutative() const noexcept override { return true; }
  [[nodiscard]] bool isAssociative() const noexcept override { return true; }
  [[nodiscard]] bool
  matchIdentity(const ConstantValue &Value) const noexcept override;
  [[nodiscard]] const ConstantValue *
  getIdentity(const Type &Type) const noexcept override;
  [[nodiscard]] OutputIterator print(const Operator &Op,
                                     OutputIterator It) const override;
};
class DivOperator final : public OperatorImplWithTraits<BinaryOperatorTrait> {
public:
  static const DivOperator &get();
  [[nodiscard]] OutputIterator print(OutputIterator It) const override;
  [[nodiscard]] bool isCommutative() const noexcept override { return false; }
  [[nodiscard]] bool isAssociative() const noexcept override { return false; }
  [[nodiscard]] bool
  matchIdentity(const ConstantValue &) const noexcept override {
    return false;
  }
  [[nodiscard]] const ConstantValue *
  getIdentity(const Type &) const noexcept override {
    return nullptr;
  }
  [[nodiscard]] OutputIterator print(const Operator &Op,
                                     OutputIterator It) const override;
};
class RemOperator final : public OperatorImplWithTraits<BinaryOperatorTrait> {
public:
  static const RemOperator &get();
  [[nodiscard]] OutputIterator print(OutputIterator It) const override;
  [[nodiscard]] bool isCommutative() const noexcept override { return false; }
  [[nodiscard]] bool isAssociative() const noexcept override { return false; }
  [[nodiscard]] bool
  matchIdentity(const ConstantValue &) const noexcept override {
    return false;
  }
  [[nodiscard]] const ConstantValue *
  getIdentity(const Type &) const noexcept override {
    return nullptr;
  }
  [[nodiscard]] OutputIterator print(const Operator &Op,
                                     OutputIterator It) const override;
};
class AbsOperator final : public OperatorImplWithTraits<UnaryOperatorTrait> {
public:
  static const AbsOperator &get();
  [[nodiscard]] OutputIterator print(OutputIterator It) const override;
  [[nodiscard]] OutputIterator print(const Operator &Op,
                                     OutputIterator It) const override;
};

} // namespace iridium
