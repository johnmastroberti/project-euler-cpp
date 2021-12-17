#include "InfInt.h"
#include "common.hpp"

InfInt factorial(int n) {
  InfInt answer = 1;
  for (auto i = 2; i <= n; i++) answer *= i;
  return answer;
}

u64 char_to_num(char c) { return c - '0'; }

void p20() {
  auto number = factorial(100).toString();
  print_answer(20, accumulate(number | std::views::transform(char_to_num)));
}
