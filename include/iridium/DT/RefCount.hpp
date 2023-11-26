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
#include <cstdint>
#include <cstdlib>
#include <utility>

namespace iridium {
template <typename T> class Ref;
class RefCountBase {
public:
  RefCountBase() noexcept = default;
  virtual ~RefCountBase() noexcept = default;
  RefCountBase(RefCountBase &) = delete;
  RefCountBase(RefCountBase &&) = delete;
  RefCountBase &operator=(RefCountBase &) = delete;
  RefCountBase &operator=(RefCountBase &&) = delete;

private:
  uint32_t RefCount = 0;
  template <typename T> friend class Ref;
  void addRef() noexcept;
  void decRef();
};

template <typename T> class Ref final {
public:
  Ref() noexcept = default;
  explicit Ref(std::nullptr_t) noexcept {}
  explicit Ref(T *Ptr) noexcept : Ptr{Ptr} {
    if (Ptr)
      Ptr->addRef();
  }
  ~Ref() {
    if (Ptr)
      Ptr->decRef();
  }
  Ref(const Ref &Other) noexcept : Ref{Other.Ptr} {}
  template <typename U> Ref(const Ref<U> &Other) noexcept : Ref{Other.Ptr} {}
  Ref(Ref &&Other) noexcept : Ptr{Other.Ptr} { Other.Ptr = nullptr; }
  void swap(Ref &Other) noexcept { std::swap(Ptr, Other.Ptr); }

  Ref &operator=(Ref &&Other) noexcept {
    this->swap(Other);
    return *this;
  }

  // NOLINTNEXTLINE(bugprone-unhandled-self-assignment)
  Ref &operator=(const Ref &Other) noexcept {
    if (Ptr != Other.Ptr) {
      Ref Copy{Other};
      this->swap(Copy);
    }
    return *this;
  }

  bool operator==(const Ref &Other) const noexcept { return Ptr == Other.Ptr; }
  bool operator!=(const Ref &Other) const noexcept { return Ptr != Other.Ptr; }
  T *release() { return std::exchange(Ptr, nullptr); }
  T &operator*() const noexcept { return *Ptr; }
  T *operator->() const noexcept { return Ptr; }
  [[nodiscard]] T *get() const noexcept { return Ptr; }
  explicit operator bool() const noexcept { return Ptr != nullptr; }

private:
  T *Ptr = nullptr;

  template <typename U> friend class Ref;
};

template <typename T, typename U = T, typename... Ts>
[[nodiscard]] auto make(Ts &&...Args) -> Ref<U> {
  return Ref<U>{static_cast<U *>(new T{std::forward<Ts>(Args)...})};
}

} // namespace iridium
