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

class FAddOperator final
    : public OperatorImplWithTraits<BinaryOperatorTrait,
                                    VectorizableOperatorTrait> {
public:
  static const FAddOperator &get();
  [[nodiscard]] OutputIterator print(OutputIterator It) const override;
  [[nodiscard]] bool isCommutative() const noexcept override { return true; }
  [[nodiscard]] OutputIterator print(const Operator &Op,
                                     OutputIterator It) const override;
};
class FSubOperator final
    : public OperatorImplWithTraits<BinaryOperatorTrait,
                                    VectorizableOperatorTrait> {
public:
  static const FSubOperator &get();
  [[nodiscard]] OutputIterator print(OutputIterator It) const override;
  [[nodiscard]] OutputIterator print(const Operator &Op,
                                     OutputIterator It) const override;
};
class FMulOperator final
    : public OperatorImplWithTraits<BinaryOperatorTrait,
                                    VectorizableOperatorTrait> {
public:
  static const FMulOperator &get();
  [[nodiscard]] OutputIterator print(OutputIterator It) const override;
  [[nodiscard]] bool isCommutative() const noexcept override { return true; }
  [[nodiscard]] OutputIterator print(const Operator &Op,
                                     OutputIterator It) const override;
};
class FDivOperator final
    : public OperatorImplWithTraits<BinaryOperatorTrait,
                                    VectorizableOperatorTrait> {
public:
  static const FDivOperator &get();
  [[nodiscard]] OutputIterator print(OutputIterator It) const override;
  [[nodiscard]] OutputIterator print(const Operator &Op,
                                     OutputIterator It) const override;
};
class FSignExtractOperator final
    : public OperatorImplWithTraits<VectorizableOperatorTrait> {
public:
  static const FSignExtractOperator &get();
  [[nodiscard]] OutputIterator print(OutputIterator It) const override;
  [[nodiscard]] OutputIterator print(const Operator &Op,
                                     OutputIterator It) const override;
};
class FSignInjectOperator final
    : public OperatorImplWithTraits<VectorizableOperatorTrait> {
public:
  static const FSignInjectOperator &get();
  [[nodiscard]] OutputIterator print(OutputIterator It) const override;
  [[nodiscard]] OutputIterator print(const Operator &Op,
                                     OutputIterator It) const override;
};

class FCmpOperator final
    : public OperatorImplWithTraits<RelationOperatorTrait> {
  static const FCmpOperator &get();
  [[nodiscard]] OutputIterator print(OutputIterator It) const override;
  [[nodiscard]] OutputIterator print(const Operator &Op,
                                     OutputIterator It) const override;
};

} // namespace iridium
