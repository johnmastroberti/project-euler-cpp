#include "common.hpp"

int count_triplets(int p) {
  int count = 0;
  for (int a = 1; a <= p / 3; a++) {
    for (int b = a; b <= p / 2; b++) {
      int c = p - b - a;
      if (c < b) break;
      if (a * a + b * b == c * c) count++;
    }
  }
  return count;
}

void p39() {
  std::vector<int> triplet_counts;
  triplet_counts.reserve(1000);
  rv3::transform(std::views::iota(0, 1000), std::back_inserter(triplet_counts),
                 count_triplets);
  auto max_it = rv3::max_element(triplet_counts);
  print_answer(39, std::distance(triplet_counts.begin(), max_it));
}
