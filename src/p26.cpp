#include "common.hpp"

auto recurrance_length(int64_t d) {
  spdlog::info("Checking d = {}", d);
  for (int64_t len = 1, numer = 10;; len++, numer *= 10) {
    auto r = numer / d;
    auto product = r * d;
    spdlog::info("numer = {}, r = {}, p = {}", numer, r, product);
    if (product == numer) return 0l;  // not repeating
    if (product == numer - 1) return len;
  }
}

u64 wiki_algo(u64 q) {
  u64 b = 10, p = 1, pos = 0;
  std::unordered_map<u64, u64> ps;
  while (!ps.contains(p)) {
    ps[p] = pos;
    auto bp = b * p;
    auto z = bp / q;
    p = bp - z * q;
    if (p == 0) return 0;
    pos++;
  }
  return pos - ps.at(p);
}

void p26() {
  for (auto i : std::views::iota(1ull, 30ull))
    fmt::print("Recurrence length of 1/{} ({}) = {}\n", i,
               1.0 / static_cast<double>(i), wiki_algo(i));

  auto lens =
      std::views::iota(1ull, 1000ull) | std::views::transform(wiki_algo);
  auto max_itr = std::ranges::max_element(lens);
  auto max_d = std::distance(lens.begin(), max_itr) + 1;
  print_answer(26, max_d);
}
