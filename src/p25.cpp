#include "common.hpp"

void p25() {
  double phi = 0.5 * (1.0 + std::sqrt(5));
  auto n = (999 + 0.5 * std::log10(5)) / std::log10(phi);
  print_answer(25, n);
}
