#include <charconv>
#include <unordered_set>

#include "common.hpp"

auto factorial(std::integral auto n) {
  if (n == 1)
    return n;
  else
    return n * factorial(n - 1);
}

std::pair<bool, int> is_pan_product(std::string const& digits, int s1, int s2) {
  int a = 0, b = 0, c = 0;
  auto afirst = digits.c_str();
  auto alast = afirst + s1;
  auto bfirst = alast;
  auto blast = afirst + s2;
  auto cfirst = blast;
  auto clast = afirst + digits.size();
  std::from_chars(afirst, alast, a);
  std::from_chars(bfirst, blast, b);
  std::from_chars(cfirst, clast, c);
  return {a * b == c, c};
}

void p32() {
  std::string digits = "123456789";
  std::unordered_set<int> pan_prods;
  for (int i = 0; i < factorial(9); i++) {
    std::next_permutation(digits.begin(), digits.end());
    for (int s1 = 1; s1 < 9; s1++)
      for (int s2 = s1 + 1; s2 < 9; s2++)
        if (auto [is_prod, prod] = is_pan_product(digits, s1, s2); is_prod)
          pan_prods.insert(prod);
  }
  print_answer(32, accumulate(pan_prods));
}
