#include "common.hpp"

u64 count_big_elements(u64 n) {
  auto indices = std::views::iota(0ull, n + 1);
  auto begin = indices.begin();
  auto mid = begin + n / 2 + 1;  // one after midpoint
  auto big_finder = [n, nCr = 1ull](auto r) mutable {
    if (r == 0) return nCr > 1'000'000;
    nCr = nCr * (n + 1 - r) / r;
    return nCr > 1'000'000;
  };
  auto big = std::ranges::find_if(begin, mid, big_finder);
  if (big == mid)
    return 0;
  else
    return n + 1 - static_cast<u64>(2 * std::distance(begin, big));
}

void p53() {
  auto ans = accumulate(std::views::iota(1ull, 101ull) |
                        std::views::transform(count_big_elements));
  print_answer(53, ans);
}
