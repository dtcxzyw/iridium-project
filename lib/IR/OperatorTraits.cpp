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

#include "iridium/IR/OperatorTraits.h"
#include <memory>

namespace iridium {

OperatorTraitTag BinaryOperatorTrait::getIdentifier() {
  static const OperatorTraitTagStorage Tag;
  return &Tag;
}
std::unique_ptr<Operator> BinaryOperatorTrait::create(const OperatorImpl &Impl,
                                                      TrackedValue &LHS,
                                                      TrackedValue &RHS,
                                                      const Name &Name) {
  auto Op = std::make_unique<Operator>(Impl);
  assert(LHS.getType() == RHS.getType());
  Op->addOperand(LHS);
  Op->addOperand(RHS);
  Op->addResult(LHS.getType(), Name);
  return Op;
}
OutputIterator BinaryOperatorTrait::printBinary(const Operator &Op,
                                                OutputIterator It) {
  return fmt::format_to(It, "{} = {} {}, {}", Op.results().front()->decay(),
                        Op.getImpl(), Op.operands().front()->decay(),
                        Op.operands().back()->decay());
}
OperatorTraitTag UnaryOperatorTrait::getIdentifier() {
  static const OperatorTraitTagStorage Tag;
  return &Tag;
}
std::unique_ptr<Operator> UnaryOperatorTrait::create(const OperatorImpl &Impl,
                                                     TrackedValue &Val,
                                                     const Name &Name) {
  auto Op = std::make_unique<Operator>(Impl);
  Op->addOperand(Val);
  Op->addResult(Val.getType(), Name);
  return Op;
}
OutputIterator UnaryOperatorTrait::printUnary(const Operator &Op,
                                              OutputIterator It) {
  return fmt::format_to(It, "{} = {} {}", Op.results().front()->decay(),
                        Op.getImpl(), Op.operands().front()->decay());
}
OperatorTraitTag VectorizableOperatorTrait::getIdentifier() {
  static const OperatorTraitTagStorage Tag;
  return &Tag;
}
OperatorTraitTag TerminatorOperatorTrait::getIdentifier() {
  static const OperatorTraitTagStorage Tag;
  return &Tag;
}
OperatorTraitTag CondInferOperatorTrait::getIdentifier() {
  static const OperatorTraitTagStorage Tag;
  return &Tag;
}

} // namespace iridium
