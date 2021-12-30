#include "InfInt.h"
#include "common.hpp"

InfInt iipow(InfInt const& a, InfInt b) {
  InfInt ans = 1;
  while (b-- > 0) ans *= a;
  return ans;
}

u64 digit_sum(std::tuple<InfInt, InfInt> ab) {
  auto [a, b] = ab;
  auto digits = iipow(a, b).toString();
  return accumulate(
      digits | std::views::transform([](char c) -> u64 { return c - '0'; }));
}

void p56() {
  std::vector<InfInt> v(98, 0);
  std::iota(v.begin(), v.end(), InfInt{2});
  auto combos = rv3::cartesian_product_view(v, v);
  std::vector<u64> digit_sums;
  digit_sums.reserve(98 * 98);
  rv3::transform(combos, std::back_inserter(digit_sums), digit_sum);
  print_answer(56, *std::ranges::max_element(digit_sums));
}
