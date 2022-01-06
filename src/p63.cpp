#include "common.hpp"

void p63() {
  auto logs =
      stdv::iota(2, 10) | stdv::transform([](auto x) { return std::log10(x); });
  auto powerful_counts = logs | stdv::transform([](auto x) {
                           return static_cast<u64>(1.0 / (1.0 - x));
                         });
  print_answer(63, accumulate(powerful_counts) + 1);  // 0^1 counts too I guess
}
