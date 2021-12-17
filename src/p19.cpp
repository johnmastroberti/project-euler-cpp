#include <fmt/chrono.h>

#include <chrono>
#include <iostream>

#include "common.hpp"

void p19() {
  using namespace std::chrono;
  auto count = 0;
  for (auto y : std::views::iota(1901, 2001))
    for (auto m : std::views::iota(1, 13)) {
      auto first_sunday = year_month_day(year(y) / month(m) / Sunday[1]);
      if (first_sunday.day() == day(1)) count++;
    }

  print_answer(19, count);
}
