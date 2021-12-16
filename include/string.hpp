#pragma once
#include <string_view>

#include "common.hpp"

auto segmented_view(const char* base, std::integral auto total_len,
                    std::integral auto chunk_size) {
  assert(total_len >= chunk_size);
  auto view_len = total_len - chunk_size + 1;

  return views::iota(decltype(total_len){}, view_len) |
         views::transform(
             [=](auto i) { return std::string_view(base + i, chunk_size); });
}
