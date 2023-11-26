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
#include <cstdio>
#include <fmt/core.h>
#include <fmt/format.h>
#include <fmt/printf.h>

namespace iridium {
class OutputStream {
public:
  OutputStream(FILE *File) : File(File) {}
  virtual ~OutputStream() = default;
  OutputStream(const OutputStream &) = delete;
  OutputStream &operator=(const OutputStream &) = delete;
  OutputStream(OutputStream &&) = delete;
  OutputStream &operator=(OutputStream &&) = delete;

  template <typename... T>
  void print(fmt::format_string<T...> Fmt, T &&...Args) {
    fmt::fprintf(File, Fmt, std::forward<T>(Args)...);
  }

private:
  FILE *File;
};

OutputStream &err();
OutputStream &out();

using OutputIterator = fmt::format_context::iterator;

template <typename T> class DefaultFormatter {
public:
  constexpr auto
  parse(fmt::format_parse_context &Ctx) -> fmt::format_parse_context::iterator {
    const auto *It = Ctx.begin();
    const auto *End = Ctx.end();

    // Check if reached the end of the range:
    if (It != End && *It != '}')
      fmt::detail::throw_format_error("invalid format");

    // Return an iterator past the end of the parsed range:
    return It;
  }

  OutputIterator format(const T &Val, fmt::format_context &Ctx) const {
    return Val.print(Ctx.out());
  }
};

} // namespace iridium
