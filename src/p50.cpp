#include "common.hpp"
#include "primes.hpp"
#include "tqdm.h"

void inclusive_scan(auto&& range, auto out) {
  if (std::ranges::begin(range) == std::ranges::end(range)) return;
  auto total = std::ranges::range_value_t<decltype(range)>{};
  for (auto&& x : range) {
    total += x;
    *out = total;
    ++out;
  }
}

void p50() {
  Primes<u64> primes;
  std::vector<u64> pscan;
  inclusive_scan(primes.up_to(100'000), std::back_inserter(pscan));
  auto pslen = pscan.size();

  u64 max_run = 0, max_run_prime = 0;
  for (u64 i = 0; i < pslen; i++) {
    for (u64 j = i + max_run + 1; j < pslen && pscan[j] - pscan[i] < 1'000'000u;
         j++) {
      if (is_prime(pscan[j] - pscan[i])) {
        max_run = j - i;
        max_run_prime = pscan[j] - pscan[i];
      }
    }
  }

  print_answer(50, max_run_prime);
}
