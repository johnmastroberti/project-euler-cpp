#include <string>

#include "common.hpp"
#include "numprops.hpp"

void p4() {
  std::vector<u64> nums;
  nums.reserve(10'000);
  u64 bound = 1000;
  for (u64 i = 900; i < bound; i++)
    for (u64 j = i; j < bound; j++) nums.push_back(i * j);

  auto palindromes = nums | views::filter(is_palindrome());
  auto max = ranges::max_element(palindromes);
  if (max != palindromes.end())
    spdlog::info("Problem 4: {}", *max);
  else
    spdlog::info("Could not find answer");
}
