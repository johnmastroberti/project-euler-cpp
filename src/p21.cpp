#include "common.hpp"
#include "primes.hpp"

auto d(u64 n) { return sum_of_factors(n); }

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
