#include "common.hpp"

bool is_pythagorean_triplet(u64 a, u64 b, u64 c) {
  return a * a + b * b == c * c;
}

std::array<u64, 3> find_triplet(u64 total) {
  for (u64 a = 1; a < total; a++) {
    for (u64 b = 1; b < total - a; b++) {
      u64 c = 1000 - b - a;
      if (is_pythagorean_triplet(a, b, c)) return {a, b, c};
    }
  }
  return {0, 0, 0};
}

void p9() {
  auto triplet = find_triplet(1000);
  spdlog::info("Problem 9: {}", accumulate(triplet, 1ull, std::multiplies{}));
}
