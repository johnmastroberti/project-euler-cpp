#include "common.hpp"

void p24() {
  std::string digits = "0123456789";
  for (auto i = 1; i < 1'000'000; i++) std::ranges::next_permutation(digits);

  print_answer(24, digits);
}
