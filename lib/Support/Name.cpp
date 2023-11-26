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

#include "iridium/Support/Name.hpp"
#include <cassert>
#include <cctype>
#include <cstdint>
#include <fmt/core.h>
#include <limits>

namespace iridium {
constexpr uint32_t PrefixOnly = std::numeric_limits<uint32_t>::max();

[[nodiscard]] OutputIterator Name::print(OutputIterator It) const {
  if (Id == 0 || Id == PrefixOnly)
    return fmt::format_to(It, "{}", Prefix);
  return fmt::format_to(It, "{}{}", Prefix, Id);
}

Name StringPool::get(std::string_view Str) {
  assert(!Str.empty());
  if (auto It = StringMap.find(Str); It != StringMap.end())
    return Name{*It, PrefixOnly};
  return Name{*StringMap.insert(std::string(Str)).first, PrefixOnly};
}
Name StringPool::getRenamable(std::string_view Str) {
  while (!Str.empty() && std::isdigit(Str.back()))
    Str.remove_suffix(1);
  assert(!Str.empty());
  if (auto It = StringMap.find(Str); It != StringMap.end())
    return Name{*It, 0};
  return Name{*StringMap.insert(std::string(Str)).first, 0};
}

void LabelAllocator::relabel(Name &Name) {
  if (Name.Id == PrefixOnly)
    return;
  Name.Id = PrefixCount[Name.Prefix.data()]++;
}
} // namespace iridium
