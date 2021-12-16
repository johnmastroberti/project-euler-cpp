#include "common.hpp"
#include "primes.hpp"
#include "problems.hpp"

void p5() {
  auto ans = accumulate(views::iota(2ull, 21ull), 1ull, std::lcm<u64, u64>);
  spdlog::info("Problem 5: {}", ans);
}
