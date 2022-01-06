#include <unordered_map>

#include "common.hpp"

auto cb(auto x) { return x * x * x; }

void p62() {
  std::unordered_map<std::string, int> cube_counts;
  std::unordered_map<std::string, u64> smallest_cubes;
  u64 size = 10;
  for (auto n : stdv::iota(1ull)) {
    auto n3 = cb(n);
    auto n3s = std::to_string(n3);
    stdr::sort(n3s);
    cube_counts[n3s]++;
    if (!smallest_cubes.contains(n3s)) smallest_cubes[n3s] = n3;

    if (cb(n + 1) >= size) {
      for (auto const& [k, v] : cube_counts)
        if (v == 5) {
          print_answer(62, smallest_cubes[k]);
          return;
        }
      size *= 10;
      cube_counts.clear();
      smallest_cubes.clear();
    }
  }
}
