#include "common.hpp"

auto pow5(auto x) { return x * x * x * x * x; }

u64 sum_of_digit_powers(u64 n) {
  u64 total = 0;
  for (; n > 0; n /= 10) total += pow5(n % 10);
  return total;
}

u64 good_num(u64 n) { return n == sum_of_digit_powers(n); }

void p30() {
  std::vector<u64> nums;
  std::ranges::copy(
      std::views::iota(2ull, 1'000'000ull) | std::views::filter(good_num),
      std::back_inserter(nums));
  print(nums);
  print_answer(30, accumulate(nums));
}
