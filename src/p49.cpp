#include "common.hpp"
#include "primes.hpp"

bool is_prime_seq(u64 p, u64 q) { return is_prime(2 * q - p); }

auto find_prime_seqs() {
  // Collect the primes between 1'000 and 10'000
  Primes<u64> primes;
  std::vector<u64> primes_in_range;
  primes_in_range.reserve(2000);
  std::ranges::copy_if(primes.up_to(10'000),
                       std::back_inserter(primes_in_range),
                       [](auto p) { return p > 1000; });

  // Find the three term prime arithmetic sequences
  std::vector<std::array<u64, 3>> prime_seqs;
  for (auto [i, p] : rv3::views::enumerate(primes_in_range))
    for (auto q : primes_in_range | rv3::views::drop(i + 1))
      if (is_prime_seq(p, q)) prime_seqs.push_back({p, q, q * 2 - p});

  return prime_seqs;
}

bool is_perm_seq(std::array<u64, 3> const& seq) {
  std::array<std::string, 3> s;
  std::ranges::transform(seq, s.begin(),
                         [](auto x) { return std::to_string(x); });
  return std::ranges::is_permutation(s[0], s[1]) &&
         std::ranges::is_permutation(s[1], s[2]);
}

void p49() {
  // Strategy:
  // * Find all arithmetic sequences of primes (forall p, q > p prime, is q + (q-p) prime?)
  // * Check each of these for being permuations
  auto seqs = find_prime_seqs();
  auto it = std::ranges::find_if(
      seqs, [](auto s) { return is_perm_seq(s) && s[0] != 1487; });
  auto ans = fmt::format("{}{}{}", it->at(0), it->at(1), it->at(2));
  print_answer(49, ans);
}
