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

#include "iridium/IR/IntegerOperators.h"
#include "iridium/IR/ConstantValue.h"

namespace iridium {
OutputIterator AddOperator::print(OutputIterator It) const {
  return fmt::format_to(It, "add");
}
bool AddOperator::matchIdentity(const ConstantValue &Value) const noexcept {
  return Value.isZero();
}
const ConstantValue *AddOperator::getIdentity(const Type &Type) const noexcept {
  return &ConstantInt::getZero(Type);
}
OutputIterator AddOperator::print(const Operator &Op, OutputIterator It) const {
  return printBinary(Op, It);
}
const AddOperator &AddOperator::get() {
  static const AddOperator Op;
  return Op;
}

OutputIterator SubOperator::print(OutputIterator It) const {
  return fmt::format_to(It, "sub");
}
OutputIterator SubOperator::print(const Operator &Op, OutputIterator It) const {
  return printBinary(Op, It);
}
const SubOperator &SubOperator::get() {
  static const SubOperator Op;
  return Op;
}

OutputIterator MulOperator::print(OutputIterator It) const {
  return fmt::format_to(It, "mul");
}
bool MulOperator::matchIdentity(const ConstantValue &Value) const noexcept {
  return Value.isOne();
}
const ConstantValue *MulOperator::getIdentity(const Type &Type) const noexcept {
  return &ConstantInt::getOne(Type);
}
OutputIterator MulOperator::print(const Operator &Op, OutputIterator It) const {
  return printBinary(Op, It);
}
const MulOperator &MulOperator::get() {
  static const MulOperator Op;
  return Op;
}

OutputIterator DivOperator::print(OutputIterator It) const {
  return fmt::format_to(It, "div");
}
OutputIterator DivOperator::print(const Operator &Op, OutputIterator It) const {
  return printBinary(Op, It);
}
const DivOperator &DivOperator::get() {
  static const DivOperator Op;
  return Op;
}

OutputIterator RemOperator::print(OutputIterator It) const {
  return fmt::format_to(It, "rem");
}
OutputIterator RemOperator::print(const Operator &Op, OutputIterator It) const {
  return printBinary(Op, It);
}
const RemOperator &RemOperator::get() {
  static const RemOperator Op;
  return Op;
}

OutputIterator AbsOperator::print(OutputIterator It) const {
  return fmt::format_to(It, "abs");
}
OutputIterator AbsOperator::print(const Operator &Op, OutputIterator It) const {
  return printUnary(Op, It);
}
const AbsOperator &AbsOperator::get() {
  static const AbsOperator Op;
  return Op;
}

} // namespace iridium
