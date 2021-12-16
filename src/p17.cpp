#include <cstring>
#include <unordered_map>

#include "common.hpp"

u64 number_of_letters(u64 x) {
  if (x == 1000) return std::strlen("onethousand");
  using Map = std::unordered_map<u64, u64>;
  const Map ones_map = {{0, 0},
                        {1, std::strlen("one")},
                        {2, std::strlen("two")},
                        {3, std::strlen("three")},
                        {4, std::strlen("four")},
                        {5, std::strlen("five")},
                        {6, std::strlen("six")},
                        {7, std::strlen("seven")},
                        {8, std::strlen("eight")},
                        {9, std::strlen("nine")}};

  const Map teens_map = {
      {10, std::strlen("ten")},      {11, std::strlen("eleven")},
      {12, std::strlen("twelve")},   {13, std::strlen("thirteen")},
      {14, std::strlen("fourteen")}, {15, std::strlen("fifteen")},
      {16, std::strlen("sixteen")},  {17, std::strlen("seventeen")},
      {18, std::strlen("eighteen")}, {19, std::strlen("nineteen")}};

  const Map tens_map = {{0, 0},
                        {2, std::strlen("twenty")},
                        {3, std::strlen("thirty")},
                        {4, std::strlen("forty")},
                        {5, std::strlen("fifty")},
                        {6, std::strlen("sixty")},
                        {7, std::strlen("seventy")},
                        {8, std::strlen("eighty")},
                        {9, std::strlen("ninety")}};

  auto digits = std::array{x % 10, (x % 100) / 10, (x % 1000) / 100};
  auto last_two = x % 100;
  u64 total = 0;
  if (digits[1] == 1)
    total += teens_map.at(last_two);
  else
    total += ones_map.at(digits[0]) + tens_map.at(digits[1]);
  if (digits[2] != 0)
    total += ones_map.at(digits[2]) + std::strlen("hundred") +
             (last_two != 0) * std::strlen("and");

  return total;
}

void p17() {
  print(number_of_letters(342));
  print(number_of_letters(115));
  auto total = accumulate(std::views::iota(0, 1001) |
                          std::views::transform(number_of_letters));
  print_answer(17, total);
}
