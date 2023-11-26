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
#include "iridium/DT/RefCount.hpp"
#include "iridium/IR/Type.h"
#include <llvm/ADT/APFloat.h>
#include <llvm/ADT/APInt.h>
#include <llvm/ADT/APSInt.h>

namespace iridium {
class ConstantValue {
public:
  ConstantValue() = default;
  ConstantValue(const ConstantValue &) = delete;
  ConstantValue &operator=(const ConstantValue &) = delete;
  ConstantValue(ConstantValue &&) = delete;
  ConstantValue &operator=(ConstantValue &&) = delete;
  virtual ~ConstantValue() = default;

  [[nodiscard]] virtual bool isZero() const noexcept = 0;
  [[nodiscard]] virtual bool isOne() const noexcept = 0;
  [[nodiscard]] virtual bool isAllOnes() const noexcept = 0;

  bool operator==(const ConstantValue &Other) const noexcept {
    return this == &Other;
  }
};

class ConstantInt final : public ConstantValue {
public:
  // TODO: use refcount
  static const ConstantValue &getZero(const Type &ScalarType);
  static const ConstantValue &getOne(const Type &ScalarType);
  static const ConstantValue &getAllOnes(const Type &ScalarType);
};

class ConstantFloat final : public ConstantValue {
public:
};

} // namespace iridium
