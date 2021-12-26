#include "common.hpp"
#include "shape_numbers.hpp"

bool is_pent_and_hex(u64 t) { return is_pentagonal(t) && is_hexagonal(t); }

void p45() {
  auto tri_nums =
      std::views::iota(286ull) | std::views::transform(triangular_n);
  auto it = std::ranges::find_if(tri_nums, is_pent_and_hex);
  print_answer(45, *it);
}
