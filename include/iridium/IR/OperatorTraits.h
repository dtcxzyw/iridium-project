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
#include "iridium/IR/Value.h"
#include "iridium/Support/OutputStream.hpp"

namespace iridium {
template <typename... Ts>
class OperatorImplWithTraits : public OperatorImpl, public Ts... {
public:
  const OperatorTrait *
  getTrait(OperatorTraitTag TraitTag) const noexcept override {
    return getTraitImpl<Ts...>(TraitTag);
  }

private:
  template <typename First, typename... Args>
  const OperatorTrait *getTraitImpl(OperatorTraitTag TraitTag) const noexcept {
    if (First::getIdentifier() == TraitTag)
      return static_cast<const First *>(this);
    if constexpr (sizeof...(Args) > 0)
      return getTraitImpl<Args...>(TraitTag);
    return nullptr;
  }
};

class ConstantValue;

class OperatorTrait {
public:
  OperatorTrait() = default;
  OperatorTrait(const OperatorTrait &) = delete;
  OperatorTrait &operator=(const OperatorTrait &) = delete;
  OperatorTrait(OperatorTrait &&) = delete;
  OperatorTrait &operator=(OperatorTrait &&) = delete;
  virtual ~OperatorTrait() = default;
};

class BinaryOperatorTrait : public OperatorTrait {
public:
  static OperatorTraitTag getIdentifier();
  [[nodiscard]] virtual bool isCommutative() const noexcept { return false; }
  [[nodiscard]] virtual bool isAssociative() const noexcept { return false; }
  [[nodiscard]] virtual bool
  matchIdentity(const ConstantValue &Value) const noexcept {
    return false;
  }
  [[nodiscard]] virtual const ConstantValue *
  getIdentity(const Type &Type) const noexcept {
    return nullptr;
  }
  // TODO: match inverse

  [[nodiscard]] static std::unique_ptr<Operator>
  create(const OperatorImpl &Impl, TrackedValue &LHS, TrackedValue &RHS,
         const Name &Name);
  [[nodiscard]] static OutputIterator printBinary(const Operator &Op,
                                                  OutputIterator It);
};

class UnaryOperatorTrait : public OperatorTrait {
public:
  static OperatorTraitTag getIdentifier();
  [[nodiscard]] static std::unique_ptr<Operator>
  create(const OperatorImpl &Impl, TrackedValue &Val, const Name &Name);
  [[nodiscard]] static OutputIterator printUnary(const Operator &Op,
                                                 OutputIterator It);
};

class VectorizableOperatorTrait : public OperatorTrait {
public:
  static OperatorTraitTag getIdentifier();
};

class TerminatorOperatorTrait : public OperatorTrait {
public:
  static OperatorTraitTag getIdentifier();
  [[nodiscard]] virtual bool
  isValidTerminator(const Operator &ParentOp) const noexcept = 0;
};

class CondInferOperatorTrait : public OperatorTrait {
public:
  static OperatorTraitTag getIdentifier();
};

class RelationOperatorTrait : public OperatorTrait {
public:
  static OperatorTraitTag getIdentifier();
  [[nodiscard]] static std::unique_ptr<Operator>
  create(const OperatorImpl &Impl, TrackedValue &LHS, TrackedValue &RHS,
         const Name &Name);
  [[nodiscard]] virtual bool isReflexive() const noexcept { return false; }
  [[nodiscard]] virtual bool isIrreflexive() const noexcept { return false; }
  [[nodiscard]] virtual bool isSymmetric() const noexcept { return false; }
  [[nodiscard]] virtual bool isAntisymmetric() const noexcept { return false; }
  [[nodiscard]] virtual bool isAsymmetric() const noexcept { return false; }
  [[nodiscard]] virtual bool isTransitive() const noexcept { return false; }

  [[nodiscard]] static OutputIterator printRelation(const Operator &Op,
                                                    OutputIterator It);
};

class MayNoReturnOperatorTrait : public OperatorTrait {
public:
  static OperatorTraitTag getIdentifier();
  [[nodiscard]] virtual bool alwaysReturn() const noexcept { return false; }
  [[nodiscard]] virtual bool alwaysNoReturn() const noexcept { return false; }
};

} // namespace iridium
