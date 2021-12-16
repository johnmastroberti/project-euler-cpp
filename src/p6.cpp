#include "common.hpp"
#include "problems.hpp"

auto square(u64 x) { return x * x; }

void p6() {
  auto nums = views::iota(1ull, 101ull);
  auto sum_squares = accumulate(nums | views::transform(square));
  auto square_sum = square(accumulate(nums));
  auto diff = square_sum - sum_squares;

  spdlog::info("Problem 6: {}", diff);
}
