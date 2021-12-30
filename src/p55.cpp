#include "InfInt.h"
#include "common.hpp"
#include "numprops.hpp"

InfInt reverse_infint(InfInt const& n) {
  auto s = n.toString();
  std::ranges::reverse(s);
  return InfInt(s);
}

bool is_lychrel(int n) {
  InfInt x = n;
  InfInt y = reverse_infint(x);
  for ([[maybe_unused]] auto i : std::views::iota(0, 50)) {
    x += y;
    y = reverse_infint(x);
    if (x == y) return false;
  }
  return true;
}

void p55() {
  auto ans = std::ranges::count_if(std::views::iota(0, 10'000), is_lychrel);
  print_answer(55, ans);
}
