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
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>

namespace iridium {
struct Name final {
  std::string_view Prefix;
  uint32_t Id;

  [[nodiscard]] OutputIterator print(OutputIterator It) const;
  static Name getStatic(std::string_view Prefix) { return Name{Prefix, 0}; }
  static Name empty() { return Name{std::string_view{}, 0}; }
};

struct TransparentStringHash final {
  using HashType = std::hash<std::string_view>;
  using is_transparent = void;

  std::size_t operator()(const char *Str) const { return HashType{}(Str); }
  std::size_t operator()(std::string_view Str) const { return HashType{}(Str); }
  std::size_t operator()(const std::string &Str) const {
    return HashType{}(Str);
  }
};

class StringPool final {
public:
  StringPool() = default;
  StringPool(const StringPool &) = delete;
  StringPool &operator=(const StringPool &) = delete;
  StringPool(StringPool &&) = delete;
  StringPool &operator=(StringPool &&) = delete;
  ~StringPool() = default;

  Name get(std::string_view Str);
  Name getRenamable(std::string_view Str);

private:
  std::unordered_set<std::string, TransparentStringHash, std::equal_to<>>
      StringMap;
};

class LabelAllocator final {
public:
  LabelAllocator() = default;
  LabelAllocator(const LabelAllocator &) = delete;
  LabelAllocator &operator=(const LabelAllocator &) = delete;
  LabelAllocator(LabelAllocator &&) = delete;
  LabelAllocator &operator=(LabelAllocator &&) = delete;
  ~LabelAllocator() = default;

  void relabel(Name &Name);

private:
  std::unordered_map<const char *, uint32_t> PrefixCount;
};

} // namespace iridium

template <>
struct fmt::formatter<iridium::Name>
    : public iridium::DefaultFormatter<iridium::Name> {};
