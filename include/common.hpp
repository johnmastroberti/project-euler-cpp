#pragma once
#include <fmt/core.h>
#include <fmt/ranges.h>
#include <spdlog/spdlog.h>

#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <numeric>
#include <range/v3/all.hpp>
#include <ranges>
#include <vector>

namespace rv3 = ranges;
// namespace ranges = std::ranges;
// namespace views = std::views;
namespace views = ranges::views;

using u64 = uint64_t;

void print(auto&& x) { fmt::print("{}\n", x); }
void print_answer(int pnum, auto&& value) {
  spdlog::info("Problem {}: {}", pnum, value);
}

template <typename Binop, typename Range, typename Init>
concept AccumulateBinaryOp = requires(Binop&& binop, Init init) {
  { binop(init, ranges::range_value_t<Range>{}) } -> std::convertible_to<Init>;
};

template <ranges::range R, typename I, AccumulateBinaryOp<R, I> B>
auto accumulate(R&& range, I init, B&& binop) {
  for (auto x : range) {
    init = binop(init, x);
  }
  return init;
}

auto accumulate(ranges::range auto&& range, auto init) {
  return accumulate(range, init, std::plus{});
}

auto accumulate(ranges::range auto&& range) {
  return accumulate(range, ranges::range_value_t<decltype(range)>{});
}
