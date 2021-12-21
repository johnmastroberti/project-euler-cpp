#include "common.hpp"

void p28() {
  auto nums = rv3::views::iota(4ull) |
              rv3::views::transform([](auto x) { return 2 * (x / 4); }) |
              rv3::views::take(1 + 4 * (1001 / 2));
  auto diagonal_nums = nums | rv3::views::exclusive_scan(1ull);
  print_answer(28, accumulate(diagonal_nums));
}
