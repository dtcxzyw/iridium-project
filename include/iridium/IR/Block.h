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
#include "iridium/DT/IntrusiveList.hpp"
#include "iridium/IR/Operator.h"
#include "iridium/Support/Name.hpp"

namespace iridium {
class BlockArgument final : public TrackedValue {
public:
  BlockArgument(const Type &Type, const Name &Name, class Block &Parent)
      : TrackedValue(Type, Name), Parent(Parent) {}
  [[nodiscard]] class Block &getParent() const;

private:
  class Block &Parent;
};

class Block final {
public:
  Block(const Name &Name, class Region &Parent)
      : BlockName(Name), Parent(&Parent) {}
  void setParent(class Region &Parent) { this->Parent = &Parent; }
  [[nodiscard]] class Region &getParent() const { return *Parent; }
  [[nodiscard]] OutputIterator print(OutputIterator It) const;

  [[nodiscard]] PtrVectorRef<BlockArgument> &arguments() { return Arguments; }
  [[nodiscard]] IntrusiveList<Operator> &operators() { return Operators; }
  [[nodiscard]] Name getName() const { return BlockName; }
  [[nodiscard]] Operator &getTerminator() { return Operators.back(); }

private:
  SmallPtrVector<BlockArgument, 4> Arguments;
  IntrusiveList<Operator> Operators;
  Name BlockName;
  class Region *Parent;
};

} // namespace iridium
