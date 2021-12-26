#include "common.hpp"

bool all_same_digits(u64 n) {
  std::array multipliers = {2, 3, 4, 5, 6};
  return std::ranges::all_of(
      multipliers, [n, nstr = std::to_string(n)](auto x) {
        return std::ranges::is_permutation(nstr, std::to_string(x * n));
      });
}

void p52() {
  auto N = std::views::iota(1ull);
  print_answer(52, *std::ranges::find_if(N, all_same_digits));
}
