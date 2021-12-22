#include <compare>

#include "common.hpp"

struct Ratio { /*{{{*/
  int n;
  int d;

  Ratio(int num, int den) : n(num), d(den) {}
  Ratio() : Ratio(0, 1) {}
  Ratio(int x) : Ratio(x, 1) {}

  auto& reduce() {
    auto gcd = std::gcd(n, d);
    n /= gcd;
    d /= gcd;
    return *this;
  }

  auto operator<=>(Ratio const& other) { return n * other.d <=> other.n * d; }
  auto operator==(Ratio const& other) { return n * other.d == other.n * d; }
};

template <>
struct fmt::formatter<Ratio> : formatter<std::string> {
  // parse is inherited from formatter<string_view>.
  template <typename FormatContext>
  auto format(Ratio const& rat, FormatContext& ctx) {
    return format_to(ctx.out(), "{}/{}", rat.n, rat.d);
  }
};

Ratio operator*(Ratio r1, Ratio r2) { return {r1.n * r2.n, r1.d * r2.d}; }

auto to_ratio(std::tuple<int, int> tup) {
  return Ratio{std::get<0>(tup), std::get<1>(tup)};
} /*}}}*/

Ratio dumb_cancel(Ratio rat) {
  auto ratn1 = rat.n % 10;
  auto ratn2 = rat.n / 10;
  auto ratd1 = rat.d % 10;
  auto ratd2 = rat.d / 10;

  if (ratn1 == ratd1) return {ratn2, ratd2};
  if (ratn1 == ratd2) return {ratn2, ratd1};
  if (ratn2 == ratd1) return {ratn1, ratd2};
  if (ratn2 == ratd2)
    return {ratn1, ratd1};
  else
    return 0;
}

void p33() {
  auto nums = rv3::views::iota(11, 100);
  auto fracs =
      rv3::views::cartesian_product(nums, nums) |
      rv3::views::transform(to_ratio) | rv3::views::filter([](auto rat) {
        return rat < 1 && (rat.d % 10 != 0);
      }) |
      rv3::views::filter([](auto rat) { return rat == dumb_cancel(rat); });
  auto prod = accumulate(fracs, Ratio{1, 1}, std::multiplies());
  print_answer(33, prod.reduce());
}
