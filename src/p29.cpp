#include "InfInt.h"
#include "common.hpp"

auto count_unique_powers(int power_bound, int n) {
  auto b = std::views::iota(2, power_bound + 1);
  static std::vector<int> powers;
  powers.reserve((power_bound - 1) * 5);
  powers.resize(0);

  for (auto k : std::views::iota(1, n + 1))
    std::ranges::copy(b | std::views::transform([k](auto x) { return x * k; }),
                      std::back_inserter(powers));
  assert(powers.size() == 99ull * n);
  assert(powers.back() == n * 100);
  std::ranges::sort(powers);
  auto [first, last] = std::ranges::unique(powers);
  powers.erase(first, last);
  return powers.size();
}

void p29() {
  auto perfect_powers = 12;
  u64 total = (99 - (perfect_powers + 9)) * 99;
  total += count_unique_powers(100, 6);      // 2, 4, 8, 16, 32, 64
  total += count_unique_powers(100, 4);      // 3, 9, 27, 81
  total += 4 * count_unique_powers(100, 2);  // 25, 36, 49, 100
  assert(total < 99ull * 99);
  print_answer(29, total);  // wrong

  std::vector<InfInt> lazy;
  lazy.reserve(99 * 99);
  for (int a = 2; a <= 100; a++) {
    InfInt base = a;
    for (int b = 2; b <= 100; b++) {
      base *= a;
      lazy.push_back(base);
    }
  }
  std::ranges::sort(lazy);
  auto [first, last] = std::ranges::unique(lazy);
  lazy.erase(first, last);
  print_answer(29, lazy.size());
}
