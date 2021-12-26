#include <iostream>
#include <span>

#include "common.hpp"
#include "primes.hpp"

char common_3_digits(const std::string& p) {
  auto has_3_of = [&p](char c) { return std::ranges::count(p, c) == 3; };
  auto it = std::ranges::find_if(p, has_3_of);
  if (it == p.end())
    return '\0';
  else
    return *it;
}

bool has_prop_p51(std::string p) {
  auto d = common_3_digits(p);
  if (p == "56003") spdlog::info("For 56003, d = '{}'", d);
  if (d == '\0') return false;

  auto it1 = std::ranges::find(p, d);
  auto it2 = std::ranges::find(it1 + 1, p.end(), d);
  auto it3 = std::ranges::find(it2 + 1, p.end(), d);
  constexpr std::span digits("0123456789", 10);
  auto dstart = (it1 == p.begin()) ? digits.begin() + 1 : digits.begin();
  auto count =
      std::ranges::count_if(dstart, digits.end(), [&p, it1, it2, it3](char c) {
        *it1 = c;
        *it2 = c;
        *it3 = c;
        return is_prime(std::stoull(p));
      });
  return count == 8;
}

void p51() {
  Primes<u64> primes;

  for (;;) {
    auto p = primes.next();
    if (has_prop_p51(std::to_string(p))) {
      print_answer(51, p);
      return;
    }
  }
}
