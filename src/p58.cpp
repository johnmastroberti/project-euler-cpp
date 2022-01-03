#include "common.hpp"
#include "primes.hpp"

struct PC {
  u64 primes = 0;
  u64 total = 0;

  operator std::string() const { return fmt::format("{}/{}", primes, total); }
};

bool whole_ring_under_one_tenth(PC const& pc) {
  return (pc.primes != 0) && (pc.total % 4 == 1) && (pc.primes * 10 < pc.total);
}

void p58() {
  auto nums = rv3::views::iota(4ull) |
              rv3::views::transform([](auto x) { return 2 * (x / 4); });
  auto diagonal_nums = nums | rv3::views::exclusive_scan(1ull);
  auto prime_counts =
      diagonal_nums | rv3::views::exclusive_scan(PC{}, [](PC const& pc, u64 d) {
        return PC{pc.primes + is_prime(d), pc.total + 1};
      });
  auto tipping_point = *rv3::find_if(prime_counts, whole_ring_under_one_tenth);

  auto side_length = (tipping_point.total - 1) / 2 + 1;
  print_answer(58, side_length);
}
