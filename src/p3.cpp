#include "common.hpp"
#include "primes.hpp"

void p3() {
  auto divisors = unique_prime_divisors(600851475143ull);
  auto max_divisor = divisors.back();
  spdlog::info("Problem 3: {}", max_divisor);
}
