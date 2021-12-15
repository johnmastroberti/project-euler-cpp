#include "common.hpp"
#include "problems.hpp"

void p1() {
  auto nums = views::iota(0) | views::take(1000) |
              views::filter([](auto x) { return x % 3 == 0 || x % 5 == 0; });
  auto total = accumulate(nums, 0);
  spdlog::info("Problem 1: {}", total);
}
