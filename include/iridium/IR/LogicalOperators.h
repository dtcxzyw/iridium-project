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
#include "iridium/IR/Operator.h"
#include "iridium/IR/OperatorTraits.h"
#include "iridium/IR/Value.h"
#include "iridium/Support/Name.hpp"
#include "iridium/Support/OutputStream.hpp"

namespace iridium {
class SelectOperator final
    : public OperatorImplWithTraits<CondInferOperatorTrait,
                                    VectorizableOperatorTrait> {
public:
  [[nodiscard]] static std::unique_ptr<Operator>
  create(const OperatorImpl &Impl, TrackedValue &Cond, TrackedValue &TrueVal,
         TrackedValue &FalseVal, const Name &Name);
  [[nodiscard]] OutputIterator print(OutputIterator It) const override;
  [[nodiscard]] OutputIterator print(const Operator &Op,
                                     OutputIterator It) const override;
  static const SelectOperator &get();
};
class LogicalAndOperator final
    : public OperatorImplWithTraits<BinaryOperatorTrait> {
public:
  [[nodiscard]] OutputIterator print(OutputIterator It) const override;
  [[nodiscard]] OutputIterator print(const Operator &Op,
                                     OutputIterator It) const override;
  static const LogicalAndOperator &get();
};
class LogicalOrOperator final
    : public OperatorImplWithTraits<BinaryOperatorTrait> {
public:
  [[nodiscard]] OutputIterator print(OutputIterator It) const override;
  [[nodiscard]] OutputIterator print(const Operator &Op,
                                     OutputIterator It) const override;
  static const LogicalOrOperator &get();
};
} // namespace iridium
