#include "common.hpp"
#include "primes.hpp"

void p7() {
  auto primes = first_n_primes(10'001);
  spdlog::info("Problem 7: {}", primes.at(10'000));
}
