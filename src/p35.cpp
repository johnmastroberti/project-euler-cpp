#include "common.hpp"
#include "primes.hpp"

u64 find_mag(u64 x) {
  u64 mag = 1;
  while (x / (10 * mag) != 0) mag *= 10;
  return mag;
}

u64 rotate(u64 x) {
  auto last_digit = x % 10;
  return x / 10 + last_digit * find_mag(x);
}

bool is_circular_prime(u64 p) {
  const auto p_orig = p;
  p = rotate(p);
  for (; p != p_orig; p = rotate(p))
    if (!is_prime(p)) return false;
  return true;
}

void p35() {
  Primes<u64> primes;
  auto ans = std::ranges::count_if(primes.up_to(1'000'000), is_circular_prime);
  print_answer(35, ans);
}
