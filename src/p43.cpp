#include <charconv>

#include "common.hpp"

u64 subnum(std::string const& str, unsigned start_ix) {
  u64 result = 1;
  auto first = str.c_str() + start_ix;
  std::from_chars(first, first + 3, result);
  return result;
}

bool has_weird_property(std::string const& str) {
  std::array primes = {2, 3, 5, 7, 11, 13, 17};
  for (unsigned i = 0; i < primes.size(); i++) {
    if (subnum(str, i + 1) % primes[i]) return false;
  }
  spdlog::info("Found {}", str);
  return true;
}

void p43() {
  u64 total = 0;
  std::string digits = "1023456789";  // skip zero at front
  while (digits.front() != '0') {
    std::ranges::next_permutation(digits);
    if (has_weird_property(digits)) total += std::stoull(digits);
  }
  print_answer(43, total);
}
