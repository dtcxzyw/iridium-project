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
class LoopOperator final
    : public OperatorImplWithTraits<MayNoReturnOperatorTrait> {
public:
  static const LoopOperator &get();
  [[nodiscard]] OutputIterator print(OutputIterator It) const override;
  [[nodiscard]] OutputIterator print(const Operator &Op,
                                     OutputIterator It) const override;
};
class BreakOperator final
    : public OperatorImplWithTraits<TerminatorOperatorTrait> {
public:
  static const BreakOperator &get();
  [[nodiscard]] OutputIterator print(OutputIterator It) const override;
  [[nodiscard]] OutputIterator print(const Operator &Op,
                                     OutputIterator It) const override;
  [[nodiscard]] bool
  isValidTerminator(const Operator &ParentOp) const noexcept override {
    return ParentOp.getImpl() == LoopOperator::get();
  }
};
class YieldOperator final
    : public OperatorImplWithTraits<TerminatorOperatorTrait> {
public:
  static const BreakOperator &get();
  [[nodiscard]] OutputIterator print(OutputIterator It) const override;
  [[nodiscard]] OutputIterator print(const Operator &Op,
                                     OutputIterator It) const override;
  [[nodiscard]] bool
  isValidTerminator(const Operator &ParentOp) const noexcept override {
    return ParentOp.getImpl() == LoopOperator::get();
  }
};

} // namespace iridium
