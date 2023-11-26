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
#include "iridium/Support/OutputStream.hpp"
#include <cstdint>

namespace iridium {

enum class TypeClass {
  Bool,
  SignedInteger,
  UnsignedInteger,
  BitwiseInteger,
  Shamt,
  Float,
  Vector,
  State,
};

class Type {
public:
  Type() = default;
  virtual ~Type() = default;
  Type(const Type &) = delete;
  Type &operator=(const Type &) = delete;
  Type(Type &&) = delete;
  Type &operator=(Type &&) = delete;

  bool operator==(const Type &Rhs) const noexcept { return this == &Rhs; }

  [[nodiscard]] virtual OutputIterator print(OutputIterator It) const = 0;
  [[nodiscard]] virtual TypeClass getTypeClass() const noexcept = 0;
};

class BoolType final : public Type {
public:
  static const BoolType &get();
  [[nodiscard]] OutputIterator print(OutputIterator It) const override;
  [[nodiscard]] TypeClass getTypeClass() const noexcept override {
    return TypeClass::Bool;
  }
};

class SignedIntegerType final : public Type {
public:
  static const SignedIntegerType &get(uint32_t BitWidth);
  [[nodiscard]] OutputIterator print(OutputIterator It) const override;
  [[nodiscard]] TypeClass getTypeClass() const noexcept override {
    return TypeClass::SignedInteger;
  }
  [[nodiscard]] uint32_t getBitWidth() const noexcept;
};

class UnsignedIntegerType final : public Type {
public:
  static const UnsignedIntegerType &get(uint32_t BitWidth);
  [[nodiscard]] OutputIterator print(OutputIterator It) const override;
  [[nodiscard]] TypeClass getTypeClass() const noexcept override {
    return TypeClass::UnsignedInteger;
  }
  [[nodiscard]] uint32_t getBitWidth() const noexcept;
};

class BitwiseIntegerType final : public Type {
public:
  static const BitwiseIntegerType &get(uint32_t BitWidth);
  [[nodiscard]] OutputIterator print(OutputIterator It) const override;
  [[nodiscard]] TypeClass getTypeClass() const noexcept override {
    return TypeClass::BitwiseInteger;
  }
  [[nodiscard]] uint32_t getBitWidth() const noexcept;
};

class ShamtType final : public Type {
public:
  static const ShamtType &get(uint32_t BitWidth);
  [[nodiscard]] OutputIterator print(OutputIterator It) const override;
  [[nodiscard]] TypeClass getTypeClass() const noexcept override {
    return TypeClass::Shamt;
  }
  [[nodiscard]] uint32_t getBitWidth() const noexcept;
};

enum class FloatTypeClass {
  Half,
  BFloat16,
  Float,
  Double,
  FloatTypeClassMax,
};

class FloatType final : public Type {
public:
  static const FloatType &get(FloatTypeClass FloatTypeClass);
  [[nodiscard]] OutputIterator print(OutputIterator It) const override;
  [[nodiscard]] TypeClass getTypeClass() const noexcept override {
    return TypeClass::Float;
  }
  [[nodiscard]] FloatTypeClass getFloatTypeClass() const noexcept;
};

class StateType final : public Type {
public:
  static const StateType &get(uint32_t BitWidth);
  [[nodiscard]] OutputIterator print(OutputIterator It) const override;
  [[nodiscard]] TypeClass getTypeClass() const noexcept override {
    return TypeClass::State;
  }
  static const StateType &get();
};

} // namespace iridium

template <>
struct fmt::formatter<iridium::Type>
    : public iridium::DefaultFormatter<iridium::Type> {};
