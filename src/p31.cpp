#include "common.hpp"
#include "tqdm.h"

int value_of_coins(auto tup) {
  return 1 * std::get<0>(tup) + 2 * std::get<1>(tup) + 5 * std::get<2>(tup) +
         10 * std::get<3>(tup) + 20 * std::get<4>(tup) + 50 * std::get<5>(tup) +
         100 * std::get<6>(tup);
}

void p31() {
  auto target = 200;
  u64 good_combos = 0;
  tqdm bar;
  for (int p100 = 0; p100 <= 2; p100++) {
    for (int p50 = 0; p50 <= 4; p50++) {
      for (int p20 = 0; p20 <= 10; p20++) {
        bar.progress(p20 + 11 * p50 + 55 * p100, 11 * 5 * 3);
        for (int p10 = 0; p10 <= 200 / 10; p10++) {
          for (int p5 = 0; p5 <= 200 / 5; p5++) {
            for (int p2 = 0; p2 <= 100; p2++) {
              auto total =
                  value_of_coins(std::tuple{0, p2, p5, p10, p20, p50, p100});
              if (total > target)
                break;
              else
                good_combos++;
            }
          }
        }
      }
    }
  }
  bar.finish();

  print_answer(31, good_combos + 1);
}
