#include "common.hpp"
#include "data.hpp"

u64 char_to_u64_p42(char c) { return c - 'A' + 1; }

u64 string_to_u64(std::string const& str) {
  return accumulate(str | std::views::transform(char_to_u64_p42));
}

bool is_triangular(u64 t) {
  u64 n = std::sqrt(2 * t);
  return n * (n + 1) == 2 * t;
}

void p42() {
  auto words = get_data<std::string>("data/p42.txt");
  auto answer = std::ranges::count_if(
      words | std::views::transform(string_to_u64), is_triangular);
  assert(is_triangular(string_to_u64("SKY")));
  print_answer(42, answer);
}
