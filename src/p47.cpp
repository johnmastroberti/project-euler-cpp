#include "common.hpp"
#include "primes.hpp"

template <unsigned M>
bool has_M_prime_factors(u64 n) {
  return unique_prime_divisors(n).size() == M;
}

void p47() {
  auto N = std::views::iota(1ull);
  auto quads = N | rv3::views::sliding(4);
  auto it = rv3::find_if(quads, [](auto&& qview) {
    return rv3::all_of(qview, has_M_prime_factors<4>);
  });
  print_answer(47, *it);
}
