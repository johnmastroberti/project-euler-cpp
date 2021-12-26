#include "shape_numbers.hpp"

u64 triangular_n(u64 n) { return n * (n + 1) / 2; }

bool is_triangular(u64 t) {
  u64 n = std::sqrt(2 * t);
  return n * (n + 1) == 2 * t;
}

u64 pentagonal_n(u64 n) { return n * (3 * n - 1) / 2; }

bool is_pentagonal(u64 p) {
  p *= 2;
  u64 nmax = std::sqrt(p);
  for (auto n : std::views::iota(1ull, nmax + 1))
    if (p == n * (3 * n - 1)) return true;
  return false;
}

u64 hexagonal_n(u64 n) { return n * (2 * n - 1); }

bool is_hexagonal(u64 h) {
  u64 nmax = std::sqrt(h);
  for (auto n : std::views::iota(1ull, nmax + 1))
    if (h == hexagonal_n(n)) return true;
  return false;
}
