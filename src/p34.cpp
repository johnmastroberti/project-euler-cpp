#include "common.hpp"

constexpr u64 factorial(std::integral auto x) {
  if (x == 0)
    return 1;
  else
    return x * factorial(x - 1);
}

template <u64... ns>
constexpr std::array factorials_impl = {factorial(ns)...};

constexpr auto factorials = factorials_impl<0, 1, 2, 3, 4, 5, 6, 7, 8, 9>;

auto fact_digit_sum(u64 n) {
  u64 sum = 0;
  for (; n > 0u; n /= 10) sum += factorials[n % 10];
  return sum;
}

void p34() {
  auto nums = std::views::iota(10ull, factorials[9] * 7) |
              std::views::filter([](u64 x) { return x == fact_digit_sum(x); });
  print_answer(34, accumulate(nums));
}
