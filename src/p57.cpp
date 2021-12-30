#include <cstdio>

#include "InfInt.h"
#include "common.hpp"

void p57() {
  using Ans = std::pair<u64, u64>;
  std::vector<Ans> iters;
  iters.reserve(1000);
  auto generator = [n = InfInt{0}, d = InfInt{1}, npd = InfInt{0}]() mutable {
    // This generator is written a little awkwardly to minimize
    // dynamic memory allocations
    n += d;
    n += d;
    std::swap(n, d);
    npd = 0;
    npd += n;
    npd += d;
    return Ans{npd.numberOfDigits(), d.numberOfDigits()};
  };
  std::ranges::generate_n(std::back_inserter(iters), 1000, generator);
  print_answer(57, std::ranges::count_if(iters, [](auto p) {
                 auto [n, d] = p;
                 return n > d;
               }));
}
