#include <unordered_set>

#include "common.hpp"
#include "primes.hpp"
#include "tqdm.h"

constexpr u64 max = 28124;

bool is_abundant(u64 n) { return sum_of_factors(n) > n; }

auto find_abundant_numbers() {
  std::vector<u64> abundant_numbers;
  abundant_numbers.reserve(10'000);
  auto aview = std::views::iota(1ull, max) | std::views::filter(is_abundant);
  std::ranges::copy(aview, std::back_inserter(abundant_numbers));
  return abundant_numbers;
}

auto sum_of_abundant_sums() {
  auto anums = find_abundant_numbers();
  std::unordered_set<u64> asums;
  tqdm bar;
  for (auto i : std::views::iota(0ull, anums.size())) {
    bar.progress(static_cast<int>(i), static_cast<int>(anums.size()));
    for (auto j : std::views::iota(0ull, i + 1)) {
      auto sum = anums[i] + anums[j];
      if (sum >= max) break;
      asums.insert(sum);
    }
  }
  bar.finish();
  return accumulate(asums);
}

void p23() {
  auto total = max * (max - 1) / 2 - sum_of_abundant_sums();
  print_answer(23, total);
}
