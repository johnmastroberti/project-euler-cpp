#include <fstream>
#include <iterator>

#include "common.hpp"

std::vector<int> get_data(const char* filename, int N) {
  std::ifstream datafile(filename);
  if (!datafile.good()) {
    spdlog::error("Could not open {} for reading");
    return {};
  }

  std::vector<int> data;
  data.reserve(N);
  std::copy_n(std::istream_iterator<int>(datafile), N,
              std::back_inserter(data));
  return data;
}

auto max_sliding_product(auto row) {
  auto slide_views = row | rv3::views::sliding(4);
  auto slide_products = slide_views | rv3::views::transform([](auto slide) {
                          return accumulate(slide, 1, std::multiplies{});
                        });
  return *rv3::max_element(slide_products);
}

auto max_product(auto rows) {
  auto row_maxes = rows | views::transform([](auto row) {
                     return max_sliding_product(row);
                   });
  return *rv3::max_element(row_maxes);
}

void p11() {
  auto grid = get_data("data/p11.txt", 400);

  auto rows = grid | rv3::views::chunk(20);
  auto horizontal_max = max_product(rows);
  spdlog::info("max product for 4 horizontal elements: {}", horizontal_max);

  auto cols = rv3::views::iota(0, 20) | rv3::views::transform([&grid](int i) {
                return grid | rv3::views::drop(i) | rv3::views::stride(20);
              });
  auto vertical_max = max_product(cols);
  spdlog::info("max product for 4 vertical elements: {}", vertical_max);

  auto upper_right_diagonals =
      rv3::views::iota(0, 17) | rv3::views::transform([&grid](int i) {
        return grid | rv3::views::drop(i) | rv3::views::stride(21) |
               rv3::views::take(20 - i);
        ;
      });
  auto lower_right_diagonals =
      rv3::views::iota(1, 17) | rv3::views::transform([&grid](int i) {
        return grid | rv3::views::drop(20 * i) | rv3::views::stride(21);
      });

  auto upper_left_diagonals =
      rv3::views::iota(0, 17) | rv3::views::transform([&grid](int i) {
        return grid | rv3::views::drop(3 + i) | rv3::views::stride(19) |
               rv3::views::take(4 + i);
        ;
      });
  auto lower_left_diagonals =
      rv3::views::iota(1, 17) | rv3::views::transform([&grid](int i) {
        return grid | rv3::views::drop(19 + 20 * i) | rv3::views::stride(19);
      });

  auto d1 = max_product(upper_right_diagonals);
  auto d2 = max_product(lower_right_diagonals);
  auto d3 = max_product(upper_left_diagonals);
  auto d4 = max_product(lower_left_diagonals);

  auto maxes = std::array{horizontal_max, vertical_max, d1, d2, d3, d4};
  auto max = *rv3::max_element(maxes);
  spdlog::info("Problem 11: {}", max);
}
