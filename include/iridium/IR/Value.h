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
#include "iridium/IR/Type.h"
#include "iridium/Support/Name.hpp"

namespace iridium {
class Value {
public:
  Value(const Type &Type) : ValueType(Type) {}
  virtual ~Value() = default;
  Value(const Value &) = delete;
  Value &operator=(const Value &) = delete;
  Value(Value &&) = delete;
  Value &operator=(Value &&) = delete;

  [[nodiscard]] const Type &getType() const noexcept { return ValueType; }
  [[nodiscard]] virtual OutputIterator print(OutputIterator It) const = 0;

  [[nodiscard]] const Value &decay() const noexcept { return *this; }

private:
  const Type &ValueType;
};

class TrackedValue : public Value {
public:
  TrackedValue(const Type &Type, const Name &Name)
      : Value(Type), ValueName{Name} {}
  [[nodiscard]] uint32_t useCount() const;
  void addUser(class Operand &Op);
  void removeUser(class Operand &Op);
  [[nodiscard]] OutputIterator print(OutputIterator It) const final;
  [[nodiscard]] OutputIterator printUse(OutputIterator It) const;

private:
  Name ValueName;
  IntrusiveList<class Operand> Users;
};

} // namespace iridium
template <>
struct fmt::formatter<iridium::Value>
    : public iridium::DefaultFormatter<iridium::Value> {};
