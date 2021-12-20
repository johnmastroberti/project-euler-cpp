#include "common.hpp"
#include "primes.hpp"

using i64 = int64_t;
auto chain_length(i64 a, i64 b) {
  auto quadratic = [a, b](i64 n) { return n * n + a * n + b; };
  auto quad_is_prime = [&quadratic](i64 n) {
    auto q = quadratic(n);
    return q > 1 && is_prime(q);
  };
  auto chain = std::views::iota(0ll, b) | std::views::take_while(quad_is_prime);
  return std::ranges::distance(chain.begin(), chain.end());
}

void p27() {
  Primes<i64> primes;
  auto small_primes = primes.up_to(1000);
  auto avals = std::views::iota(-999, 1001);
  auto ab_pairs = rv3::cartesian_product_view(avals, small_primes);
  auto max_pair = rv3::max_element(ab_pairs, std::less(), [](auto p) {
    auto [a, b] = p;
    return chain_length(a, b);
  });
  auto [a, b] = *max_pair;
  print_answer(27, a * b);
}
