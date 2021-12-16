#include "common.hpp"
#include "primes.hpp"

void p10() {
  Primes<u64> primes;
  auto my_primes = primes.up_to(2'000'000ull);
  auto total = accumulate(my_primes);
  spdlog::info("Problem 10: {}", total);
}
