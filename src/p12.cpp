#include "common.hpp"
#include "primes.hpp"
#include "problems.hpp"

auto triangle_n(u64 n) {
  if (n % 2 == 0)
    return (n / 2ull) * (n + 1ull);
  else
    return n * ((n + 1ull) / 2ull);
}

auto number_of_divisors(u64 num) {
  auto divisors = prime_divisors(num);
  return accumulate(divisors | std::views::values |
                        std::views::transform([](u64 x) { return x + 1; }),
                    1ull, std::multiplies{});
}

auto divisors_of_triangle_n(u64 n) {
  if (n % 2 == 0)
    return number_of_divisors(n / 2ull) * number_of_divisors(n + 1ull);
  else
    return number_of_divisors(n) * number_of_divisors((n + 1ull) / 2ull);
}

void p12() {
  auto triangle_numbers =
      std::views::iota(1ull) | std::views::transform(triangle_n);

  auto ans_it = std::ranges::find_if(
      triangle_numbers, [](u64 t) { return number_of_divisors(t) > 500; });
  spdlog::info("Problem 12: {}", *ans_it);

  auto ans_index_it = std::ranges::find_if(std::views::iota(1ull), [](u64 i) {
    return divisors_of_triangle_n(i) > 500;
  });
  auto ans = triangle_n(*ans_index_it);
  spdlog::info("Problem 12 (alternative method): {}", ans);
}
