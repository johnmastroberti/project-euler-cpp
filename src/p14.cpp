#include "common.hpp"

u64 collatz_step(u64 n) {
  if (n % 2)
    return 3 * n + 1;
  else
    return n / 2;
}

void p14() {
  // setup
  u64 bound = 1'000'000ull;
  std::vector<u64> collatz_lengths;
  collatz_lengths.reserve(bound + 1);
  collatz_lengths.push_back(0);  // n=0
  collatz_lengths.push_back(0);  // n=1

  // work
  for (const auto Ninit : std::views::iota(2ull, bound)) {
    u64 len = 0;
    u64 n = Ninit;
    while (n >= Ninit) {
      n = collatz_step(n);
      len++;
    }
    collatz_lengths.push_back(len + collatz_lengths.at(n));
  }

  auto max_itr = std::ranges::max_element(collatz_lengths);
  spdlog::info("Problem 14: {}",
               std::distance(collatz_lengths.begin(), max_itr));
}
