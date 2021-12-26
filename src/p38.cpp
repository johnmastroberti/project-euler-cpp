#include <charconv>

#include "common.hpp"

bool is_concat_product(std::string const& num) {
  int base = 0;
  for (int i = 1; i < 5; i++) {
    std::from_chars(num.c_str(), num.c_str() + i, base);
    auto concat_product = std::to_string(base);
    for (int j = 2; concat_product.size() < num.size(); j++)
      concat_product += std::to_string(j * base);
    if (concat_product == num) return true;
  }
  return false;
}

void p38() {
  std::string digits = "987654321";
  for (;;) {
    std::ranges::prev_permutation(digits);
    if (is_concat_product(digits)) break;
  }
  print_answer(38, digits);
}
