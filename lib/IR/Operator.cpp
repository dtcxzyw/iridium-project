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

#include "iridium/IR/Operator.h"
#include "iridium/IR/Type.h"
#include <algorithm>
#include <cassert>

namespace iridium {
Operand::Operand(Operator &Parent, TrackedValue &Use)
    : Value(Use.getType()), Parent(Parent), ValueUse(&Use) {
  Use.addUser(*this);
}
OutputIterator Operand::print(OutputIterator It) const {
  return ValueUse->printUse(It);
}
Operand::~Operand() { ValueUse->removeUser(*this); }
void Operand::replaceWith(TrackedValue &NewUse) {
  if (ValueUse == &NewUse)
    return;

  ValueUse->removeUser(*this);
  ValueUse = &NewUse;
  NewUse.addUser(*this);
}
bool Operator::isTriviallyDead() const {
  return std::ranges::all_of(
      Results, [](const auto &Res) { return Res->useCount() == 0; });
}
void Operator::addResult(const Type &Type, const Name &Name) {
  Results.emplace_back(std::make_unique<Result>(*this, Type, Name));
}
void Operator::addOperand(TrackedValue &Value) {
  Operands.emplace_back(std::make_unique<Operand>(*this, Value));
}
// PoisonOperator::PoisonOperator(const Type &Type) { addResult(Type); }
// OutputIterator PoisonOperator::print(OutputIterator It) const {
//   return fmt::format_to(It, "poison {}", results().front()->getType());
// }
// MergeStateOperator::MergeStateOperator(
//     const PtrArrayRef<TrackedValue> &States) {
//   for (const auto &State : States) {
//     assert(State->getType().getTypeClass() == TypeClass::State);
//     addOperand(*State);
//   }
// }
// [[nodiscard]] OutputIterator
// MergeStateOperator::print(OutputIterator It) const {
//   return printNormal(It, "merge_state", TypePrintMode::None);
// }
} // namespace iridium
