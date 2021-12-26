#include "common.hpp"

u64 pentagonal_n(u64 n) { return n * (3 * n - 1) / 2; }

bool is_pentagonal(u64 p) {
  p *= 2;
  u64 nmax = std::sqrt(p);
  for (auto n : std::views::iota(1ull, nmax + 1))
    if (p == n * (3 * n - 1)) return true;
  return false;
}

bool sum_and_diff_pentagonal(u64 j, u64 k) {
  auto pj = pentagonal_n(j);
  auto pk = pentagonal_n(k);
  auto sum = is_pentagonal(pj + pk);
  if (!sum) return false;
  auto diff = is_pentagonal(std::max(pj, pk) - std::min(pj, pk));
  return diff;
}

void p44() {
  for (u64 n : std::views::iota(1ull)) {
    for (u64 m : std::views::iota(1ull, n)) {
      if (sum_and_diff_pentagonal(n, m)) {
        spdlog::info("Found P_{} = {} and P_{} = {}", n, pentagonal_n(n), m,
                     pentagonal_n(m));
        print_answer(44, pentagonal_n(n) - pentagonal_n(m));
        return;
      }
    }
  }
}
