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

#include "iridium/IR/Type.h"
#include "iridium/Support/Debug.hpp"
#include <array>
#include <cassert>
#include <fmt/format.h>

namespace iridium {

const BoolType &BoolType::get() {
  static const BoolType Instance;
  return Instance;
}

OutputIterator BoolType::print(OutputIterator It) const {
  return fmt::format_to(It, "bool");
}

constexpr uint32_t MinSupportedBitWidth = 4;
constexpr uint32_t MaxSupportedBitWidth = 128;

static const std::array<SignedIntegerType, MaxSupportedBitWidth + 1>
    SignedIntegerTypeInstances;
const SignedIntegerType &SignedIntegerType::get(uint32_t BitWidth) {
  assert(MinSupportedBitWidth <= BitWidth && BitWidth <= MaxSupportedBitWidth);
  return SignedIntegerTypeInstances[BitWidth];
}
uint32_t SignedIntegerType::getBitWidth() const noexcept {
  return this - SignedIntegerTypeInstances.begin();
}
OutputIterator SignedIntegerType::print(OutputIterator It) const {
  return fmt::format_to(It, "s{}", getBitWidth());
}

static const std::array<UnsignedIntegerType, MaxSupportedBitWidth + 1>
    UnsignedIntegerTypeInstances;
const UnsignedIntegerType &UnsignedIntegerType::get(uint32_t BitWidth) {
  assert(MinSupportedBitWidth <= BitWidth && BitWidth <= MaxSupportedBitWidth);
  return UnsignedIntegerTypeInstances[BitWidth];
}
uint32_t UnsignedIntegerType::getBitWidth() const noexcept {
  return this - UnsignedIntegerTypeInstances.begin();
}
OutputIterator UnsignedIntegerType::print(OutputIterator It) const {
  return fmt::format_to(It, "u{}", getBitWidth());
}

static const std::array<BitwiseIntegerType, MaxSupportedBitWidth + 1>
    BitwiseIntegerTypeInstances;
const BitwiseIntegerType &BitwiseIntegerType::get(uint32_t BitWidth) {
  assert(MinSupportedBitWidth <= BitWidth && BitWidth <= MaxSupportedBitWidth);
  return BitwiseIntegerTypeInstances[BitWidth];
}
uint32_t BitwiseIntegerType::getBitWidth() const noexcept {
  return this - BitwiseIntegerTypeInstances.begin();
}
OutputIterator BitwiseIntegerType::print(OutputIterator It) const {
  return fmt::format_to(It, "b{}", getBitWidth());
}

static const std::array<ShamtType, MaxSupportedBitWidth + 1> ShamtTypeInstances;
const ShamtType &ShamtType::get(uint32_t BitWidth) {
  assert(MinSupportedBitWidth <= BitWidth && BitWidth <= MaxSupportedBitWidth);
  return ShamtTypeInstances[BitWidth];
}
uint32_t ShamtType::getBitWidth() const noexcept {
  return this - ShamtTypeInstances.begin();
}
OutputIterator ShamtType::print(OutputIterator It) const {
  return fmt::format_to(It, "shamt{}", getBitWidth());
}

static const std::array<FloatType,
                        static_cast<size_t>(FloatTypeClass::FloatTypeClassMax)>
    FloatTypeInstances;
const FloatType &FloatType::get(FloatTypeClass FloatTypeClass) {
  return FloatTypeInstances[static_cast<size_t>(FloatTypeClass)];
}
FloatTypeClass FloatType::getFloatTypeClass() const noexcept {
  return static_cast<FloatTypeClass>(this - FloatTypeInstances.begin());
}
OutputIterator FloatType::print(OutputIterator It) const {
  const char *Name;
  switch (getFloatTypeClass()) {
  case FloatTypeClass::Half:
    Name = "half";
  case FloatTypeClass::BFloat16:
    Name = "bfloat16";
  case FloatTypeClass::Float:
    Name = "float";
  case FloatTypeClass::Double:
    Name = "double";
  default:
    unreachable();
  }
  return fmt::format_to(It, "{}", Name);
}

} // namespace iridium
