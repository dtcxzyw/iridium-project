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

#include "iridium/IR/Value.h"
#include "iridium/IR/Operator.h"
#include <fmt/core.h>

namespace iridium {
OutputIterator TrackedValue::print(OutputIterator It) const {
  return fmt::format_to(It, "%{}:{}", ValueName, getType());
}
OutputIterator TrackedValue::printUse(OutputIterator It) const {
  return fmt::format_to(It, "%{}", ValueName);
}
uint32_t TrackedValue::useCount() const { return Users.size(); }
void TrackedValue::addUser(Operand &Op) { Users.insert(Users.end(), Op); }
void TrackedValue::removeUser(Operand &Op) { Users.remove(Op); }
} // namespace iridium
