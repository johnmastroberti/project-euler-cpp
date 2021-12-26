#include <iostream>
#include <span>

#include "common.hpp"
#include "primes.hpp"

char common_3_digits(const std::string& p) {
  auto has_3_of = [&p](char c) { return std::ranges::count(p, c) >= 3; };
  auto it = std::ranges::find_if(p, has_3_of);
  if (it == p.end())
    return '\0';
  else
    return *it;
}

bool has_prop_p51(std::string p) {
  auto d = common_3_digits(p);
  if (d == '\0') return false;

  static u64 counter = 0;
  counter++;
  if (counter % (1 << 10) == 0) print(p);
  constexpr std::span digits("0123456789", 10);
  return std::ranges::count_if(digits, [&p, d](char c) {
           std::ranges::replace(p, d, c);
           return is_prime(std::stoull(p));
         }) == 8;
}

void p51() {
  Primes<u64> primes;

  // auto status = [max = 0ull](u64 p) mutable {
  //   const u64 chunk_size = 10'000;
  //   if (p / chunk_size > max) {
  //     print(p);
  //     max++;
  //   }
  // };

  for (;;) {
    auto p = primes.next();
    // status(p);
    if (has_prop_p51(std::to_string(p))) {
      print_answer(51, p);
      return;
    }
  }
  // std::vector<std::string> pstrings;
  // std::ranges::transform(primes.up_to(1'000'000), std::back_inserter(pstrings),
  //                        [](auto x) { return std::to_string(x); });
  // auto begin = std::ranges::find_if(
  //     pstrings, [](auto const& s) { return s.size() == 5; });
  // std::copy_if(begin, pstrings.end(),
  //              std::ostream_iterator<std::string>(std::cout, "\n"),
  //              has_prop_p51);
}
