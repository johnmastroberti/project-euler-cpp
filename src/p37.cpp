#include "common.hpp"
#include "primes.hpp"

u64 left_trunc(u64 n) {
  u64 base = 1, result = 0;
  for (; n >= 10u; base *= 10, n /= 10) result += (n % 10) * base;
  return result;
}

u64 right_trunc(u64 n) { return n / 10; }

bool is_trunc_prime_impl(u64 p, auto&& trunc_func) {
  for (; p > 0u; p = trunc_func(p))
    if (!is_prime(p)) return false;
  return true;
}

bool is_trunc_prime(u64 p) {
  return is_trunc_prime_impl(p, left_trunc) &&
         is_trunc_prime_impl(p, right_trunc);
}

void p37() {
  Primes<u64> primes;
  primes.next();  // 2
  primes.next();  // 3
  primes.next();  // 5
  primes.next();  // 7, next call gives 11
  int found = 0;
  std::vector<u64> trunc_primes;
  while (found < 11) {
    auto p = primes.next();
    if (is_trunc_prime(p)) {
      trunc_primes.push_back(p);
      found++;
    }
  }
  print_answer(37, accumulate(trunc_primes));
}
