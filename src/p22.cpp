#include "common.hpp"
#include "data.hpp"

int64_t char_to_num2(char c) {
  if (c >= 'A' && c <= 'Z')
    return c - 'A' + 1;
  else if (c >= 'a' && c <= 'z')
    return c - 'a' + 1;
  else
    return 0;
}

int64_t name_score(std::string const& name) {
  return accumulate(name | std::views::transform(char_to_num2));
}

void p22() {
  auto names = get_data<std::string>("data/p22.txt", 5163);
  std::ranges::sort(names);

  print(name_score(names[937]) * 938);

  auto name_scores = names | std::views::transform(name_score);
  auto total = accumulate(
      name_scores | rv3::views::enumerate |
      rv3::views::transform([](auto p) { return (p.first + 1) * p.second; }));

  print_answer(22, total);
}
