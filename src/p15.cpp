#include "InfInt.h"
#include "common.hpp"

u64 partial_factorial(u64 low, u64 hi) {
  assert(low <= hi);
  return accumulate(std::views::iota(low, hi + 1), 1ull, std::multiplies{});
}

u64 partial_double_factorial(u64 low, u64 hi) {
  assert(low <= hi);
  return accumulate(
      std::views::iota(low, hi + 1) |
          std::views::filter([low](u64 x) { return x % 2 == low % 2; }),
      1ull, std::multiplies{});
}

u64 factorial(u64 n) { return partial_factorial(1, n); }

u64 double_factorial(u64 n) { return partial_double_factorial((n % 2) + 2, n); }

InfInt big_partial_factorial(int low, int hi) {
  assert(low <= hi);
  InfInt result = InfInt(1);
  for (; low <= hi; low++) result *= low;
  return result;
}

void p15() {
  auto answer = big_partial_factorial(21, 40) / big_partial_factorial(2, 20);
  spdlog::info("Problem 15: {}", answer.toString());
}
