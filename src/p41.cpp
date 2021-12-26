#include "common.hpp"
#include "primes.hpp"

auto factorial(auto n) {
  if (n == 0)
    return decltype(n){1};
  else
    return n * factorial(n - 1);
}

void p41() {
  std::string digits = "987654321";
  for (auto n = 9; n > 1; n--) {
    for (auto i = 0; i < factorial(n); i++) {
      std::ranges::prev_permutation(digits);
      if (is_prime(std::stoll(digits))) goto end;
    }
    assert(std::ranges::is_sorted(digits, std::greater()));
    std::ranges::rotate(digits, digits.begin() + 1);
    digits.pop_back();
  }

end:
  print_answer(41, digits);
}
