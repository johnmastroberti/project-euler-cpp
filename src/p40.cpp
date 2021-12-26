#include "common.hpp"

int champernowne_dn(int n) {
  assert(n > 0);
  int target_num_digits = 1;
  int chunk_leader = 1;
  int search_index = 1;
  for (;;) {
    int chunk_size = target_num_digits * 9 * chunk_leader;
    if (search_index + chunk_size > n) break;
    search_index += chunk_size;
    target_num_digits++;
    chunk_leader *= 10;
  }

  int chunk_index = n - search_index;
  int target_num = chunk_leader + chunk_index / target_num_digits;
  int digit_num = chunk_index % target_num_digits;
  return std::to_string(target_num).at(digit_num) - '0';
}

void p40() {
  std::array ns = {1, 10, 100, 1'000, 10'000, 100'000, 1'000'000};
  print_answer(40, accumulate(ns | std::views::transform(champernowne_dn), 1,
                              std::multiplies()));
}
