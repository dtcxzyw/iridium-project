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
#include <llvm/ADT/ArrayRef.h>
#include <llvm/ADT/SmallVector.h>
#include <memory>

namespace iridium {
template <typename T, uint32_t N> using SmallVector = llvm::SmallVector<T, N>;
template <typename T> using VectorRef = llvm::SmallVectorImpl<T>;
template <typename T, uint32_t N>
using SmallPtrVector = SmallVector<std::unique_ptr<T>, N>;
template <typename T> using PtrVectorRef = VectorRef<std::unique_ptr<T>>;
template <typename T, uint32_t N> using SmallPtrRefVector = SmallVector<T *, N>;
template <typename T> using PtrArrayRef = llvm::ArrayRef<T *>;
} // namespace iridium
