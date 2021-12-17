#include "common.hpp"
#include "primes.hpp"

u64 factor_sum(std::pair<u64, u64> prime_factor) {
  auto [p, n] = prime_factor;
  u64 total = 1;
  u64 factor = 1;
  for (u64 i = 1; i <= n; i++) {
    factor *= p;
    total += factor;
  }

  return total;
}

u64 d(u64 n) {
  auto primes = prime_divisors(n);
  auto sum = accumulate(primes | std::views::transform(factor_sum), 1ull,
                        std::multiplies());
  return sum - n;
}

auto is_amicable(u64 n) {
  auto dn = d(n);
  return dn != n && d(dn) == n;
}

void p21() {
  fmt::print("d({}) = {}\n", 220, d(220));
  fmt::print("d(d({})) = {}\n", 220, d(d(220)));

  auto anums = std::views::iota(3, 10'000) | std::views::filter(is_amicable);
  auto sum = accumulate(anums);
  print_answer(21, sum);
}
