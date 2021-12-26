#include "common.hpp"
#include "primes.hpp"

bool fails_goldbach_conjecture(u64 c) {
  if (is_prime(c)) return false;
  auto double_squares =
      std::views::iota(1ull) |
      std::views::transform([](auto x) { return 2 * x * x; }) |
      std::views::take_while([c](auto s) { return s < c - 2; });
  return std::ranges::none_of(double_squares,
                              [c](auto s) { return is_prime(c - s); });
}

void p46() {
  auto odds = std::views::iota(1ull) |
              std::views::transform([](auto n) { return 2 * n + 1; });
  auto it = std::ranges::find_if(odds, fails_goldbach_conjecture);
  print_answer(46, *it);
}
