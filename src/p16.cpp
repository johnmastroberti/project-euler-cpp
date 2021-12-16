#include "InfInt.h"
#include "common.hpp"

InfInt big_pow(int base, int power) {
  auto big_base = InfInt(base);
  return accumulate(
      std::views::iota(0, power) |
          std::views::transform([big_base](int) { return big_base; }),
      InfInt(1), std::multiplies{});
}

u64 char_to_u64(char c) { return c - '0'; }

void p16() {
  auto num = big_pow(2, 1000);
  auto num_string = num.toString();
  auto total = accumulate(num_string | std::views::transform(char_to_u64));
  print_answer(16, total);
}
