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

#include "iridium/IR/LogicalOperators.h"
#include "iridium/IR/Operator.h"
#include <fmt/format.h>

namespace iridium {
std::unique_ptr<Operator> SelectOperator::create(const OperatorImpl &Impl,
                                                 TrackedValue &Cond,
                                                 TrackedValue &TrueVal,
                                                 TrackedValue &FalseVal,
                                                 const Name &Name) {
  assert(TrueVal.getType() == FalseVal.getType());
  auto Op = std::make_unique<Operator>(Impl);
  Op->addResult(TrueVal.getType(), Name);
  Op->addOperand(Cond);
  Op->addOperand(TrueVal);
  Op->addOperand(FalseVal);
  return Op;
}
OutputIterator SelectOperator::print(OutputIterator It) const {
  return fmt::format_to(It, "select");
}
OutputIterator SelectOperator::print(const Operator &Op,
                                     OutputIterator It) const {
  return fmt::format_to(It, "{} = {} {}, {}, {}", Op.results().front()->decay(),
                        Op.getImpl(), Op.getOperand(0).decay(),
                        Op.getOperand(1).decay(), Op.getOperand(2).decay());
}
const SelectOperator &SelectOperator::get() {
  static SelectOperator Impl;
  return Impl;
}
OutputIterator LogicalAndOperator::print(OutputIterator It) const {
  return fmt::format_to(It, "logical_and");
}
OutputIterator LogicalAndOperator::print(const Operator &Op,
                                         OutputIterator It) const {
  return printBinary(Op, It);
}
const LogicalAndOperator &LogicalAndOperator::get() {
  static LogicalAndOperator Impl;
  return Impl;
}
OutputIterator LogicalOrOperator::print(OutputIterator It) const {
  return fmt::format_to(It, "logical_or");
}
OutputIterator LogicalOrOperator::print(const Operator &Op,
                                        OutputIterator It) const {
  return printBinary(Op, It);
}
const LogicalOrOperator &LogicalOrOperator::get() {
  static LogicalOrOperator Impl;
  return Impl;
}

} // namespace iridium
