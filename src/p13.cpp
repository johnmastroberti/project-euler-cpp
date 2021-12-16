#include <string_view>

#include "InfInt.h"
#include "common.hpp"
#include "data.hpp"

void p13() {
  auto num_strings = get_data<std::string>("data/p13.txt", 100);
  auto total_bignum = accumulate(
      num_strings |
          std::views::transform([](auto&& str) { return InfInt(str); }),
      InfInt(0));
  auto total_str = total_bignum.toString();
  spdlog::info("Problem 13: {}",
               std::string_view(total_str.begin(), total_str.begin() + 10));
}
