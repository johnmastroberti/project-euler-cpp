#include "primes.hpp"

class PossiblePrime { /*{{{*/
 private:
  u64 m_value;
  u64 m_base;

  static constexpr u64 ten = u64(10);

  u64 next_suffix() const {
    const auto suffix = m_value - ten * m_base;
    switch (suffix) {
      case 1:
        return 3;
      case 3:
        return 7;
      case 7:
        return 9;
      case 9:
        return 1;
      default:
        assert(false);
    }
    return 0;
  }

 public:
  PossiblePrime() : m_value(3), m_base(0) {}
  auto value() const { return m_value; }

  auto& operator++() {
    auto suffix = next_suffix();
    if (suffix == 1) m_base++;
    m_value = ten * m_base + suffix;
    return *this;
  }

  auto operator++(int) {
    auto ans = *this;
    this->operator++();
    return ans;
  }

  operator u64() const { return value(); }
};
/*}}}*/

std::vector<u64> first_n_primes(u64 n) { /*{{{*/
  // degenerate cases
  if (n == 0) return {};
  if (n == 1) return {2};
  // setup
  std::vector<u64> primes;
  primes.reserve(n);
  primes.push_back(2);

  u64 p = 1;
  for (u64 i = 0; i < n; i++) {
    for (;;) {
      p += 2;
      if (ranges::none_of(
              primes | views::take_while([root = std::sqrt(p)](auto x) {
                return double(x) <= root;
              }),
              [p](auto d) { return p % d == 0; }))
        break;
    }
    primes.push_back(p);
  }
  return primes;
}

std::vector<u64> primes_up_to(u64 n) {
  spdlog::info("Finding primes up to {}", n);
  // degenerate cases
  if (n < 2) return {};
  if (n == 2) return {2};
  // setup
  std::vector<u64> primes;
  // primes.reserve(static_cast<size_t>(double(n) / std::log(n)));
  primes.push_back(2);

  u64 p = 1;
  for (u64 i = 0; i < n; i++) {
    for (; p <= n;) {
      p += 2;
      if (ranges::none_of(
              primes | views::take_while([p](auto x) { return x <= p * p; }),
              [p](auto d) { return p % d == 0; }))
        break;
    }
    if (p > n) break;
    if (i % 1000 == 0) spdlog::info("Found prime p = {}", p);
    primes.push_back(p);
  }
  return primes;
} /*}}}*/

auto divide_out(u64 num, u64 divisor) {
  u64 count = 0;
  while (num % divisor == 0) {
    num /= divisor;
    count++;
  }
  return std::pair{num, count};
}

std::vector<u64> unique_prime_divisors(u64 num) {
  std::vector<u64> divisors;
  static Primes<u64> primes;
  primes.reset();

  while (num > 1) {
    auto p = primes.next();
    auto [new_num, count] = divide_out(num, p);
    if (count > 0) {
      divisors.push_back(p);
      num = new_num;
    }
  }
  return divisors;
}

std::map<u64, u64> prime_divisors(u64 num) {
  std::map<u64, u64> divisors;
  static Primes<u64> primes;
  primes.reset();

  while (num > 1) {
    auto p = primes.next();
    auto [new_num, count] = divide_out(num, p);
    if (count != 0) divisors.insert({p, count});
    num = new_num;
  }
  return divisors;
}

u64 factor_sum_impl(std::pair<u64, u64> prime_factor) {
  auto [p, n] = prime_factor;
  u64 total = 1;
  u64 factor = 1;
  for (u64 i = 1; i <= n; i++) {
    factor *= p;
    total += factor;
  }

  return total;
}

u64 sum_of_factors(u64 n) {
  auto primes = prime_divisors(n);
  auto sum = accumulate(primes | std::views::transform(factor_sum_impl), 1ull,
                        std::multiplies());
  return sum - n;
}

bool is_prime(u64 n) {
  static Primes<u64> primes;
  primes.reset();
  primes.next();
  for (u64 d = 2; d * d <= n; d = primes.next())
    if (n % d == 0) return false;
  return true;
}
