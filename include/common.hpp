#pragma once
#include <fmt/core.h>
#include <fmt/ranges.h>
#include <spdlog/spdlog.h>

#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <numeric>
#include <ranges>
#include <vector>

namespace ranges = std::ranges;
namespace views = std::views;

using u64 = uint64_t;

auto accumulate(auto&& range, auto init) {
  for (auto x : range) {
    // spdlog::info("Processing x = {}", x);
    init += x;
  }
  return init;
}
