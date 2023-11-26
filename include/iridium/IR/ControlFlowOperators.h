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
class BranchOperator final
    : public OperatorImplWithTraits<TerminatorOperatorTrait> {
  static const BranchOperator &get();
  [[nodiscard]] bool
  isValidTerminator(const Operator &ParentOp) const noexcept override {
    return true;
  }
  [[nodiscard]] OutputIterator print(OutputIterator It) const override;
  [[nodiscard]] OutputIterator print(const Operator &Op,
                                     OutputIterator It) const override;
};
class CondBranchOperator final
    : public OperatorImplWithTraits<TerminatorOperatorTrait> {
  static const CondBranchOperator &get();
  [[nodiscard]] OutputIterator print(OutputIterator It) const override;
  [[nodiscard]] OutputIterator print(const Operator &Op,
                                     OutputIterator It) const override;
  [[nodiscard]] bool
  isValidTerminator(const Operator &ParentOp) const noexcept override {
    return true;
  }
};
class SwitchOperator final
    : public OperatorImplWithTraits<TerminatorOperatorTrait> {
  static const SwitchOperator &get();
  [[nodiscard]] OutputIterator print(OutputIterator It) const override;
  [[nodiscard]] OutputIterator print(const Operator &Op,
                                     OutputIterator It) const override;
  [[nodiscard]] bool
  isValidTerminator(const Operator &ParentOp) const noexcept override {
    return true;
  }
};
class UnreachableOperator final
    : public OperatorImplWithTraits<TerminatorOperatorTrait> {
  static const UnreachableOperator &get();
  [[nodiscard]] OutputIterator print(OutputIterator It) const override;
  [[nodiscard]] OutputIterator print(const Operator &Op,
                                     OutputIterator It) const override;
  [[nodiscard]] bool
  isValidTerminator(const Operator &ParentOp) const noexcept override {
    return true;
  }
};

} // namespace iridium
