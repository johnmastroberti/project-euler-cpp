#include "common.hpp"
#include "primes.hpp"
#include "problems.hpp"

void p3() {
  auto divisors = prime_divisors(600851475143ull);
  auto max_divisor = divisors.back();
  spdlog::info("Problem 3: {}", max_divisor);
}
