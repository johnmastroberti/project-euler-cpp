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

bool is_prime(u64 num) {
  // basic checks
  if (num < 2) return false;
  if (num % 2 == 0) return (num == 2);
  if (num % 5 == 0) return (num == 5);

  // Check divisibility by possible divisors
  auto root = static_cast<u64>(std::sqrt(num));
  auto possible_divisors =
      views::iota(PossiblePrime()) |
      views::take_while([root](auto p) { return p < root; });
  return ranges::none_of(possible_divisors,
                         [num](auto d) { return num % d == 0; });
} /*}}}*/

class Primes {
 private:
  std::vector<u64> m_prime_list;

 public:
  Primes() : m_prime_list() {}

  u64 next() {
    // base cases
    if (m_prime_list.size() == 0) {
      m_prime_list.push_back(2);
      return 2;
    } else if (m_prime_list.size() == 1) {
      m_prime_list.push_back(3);
      return 3;
    }

    auto p = m_prime_list.back() + 2;
    for (;; p += 2) {
      auto p_is_prime = ranges::none_of(
          m_prime_list | views::take_while([p](auto x) { return x * x <= p; }),
          [p](auto x) { return p % x == 0; });
      if (p_is_prime) {
        m_prime_list.push_back(p);
        return p;
      }
    }
  }

  auto first_n(u64 n) {
    while (m_prime_list.size() < n) next();
    return ranges::take_view(m_prime_list, n);
  }

  auto up_to(u64 n) {
    while (m_prime_list.back() < n) next();
    return ranges::take_while_view(m_prime_list, [n](auto p) { return p < n; });
  }
};

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

std::vector<u64> prime_divisors(u64 num) {
  std::vector<u64> divisors;
  Primes primes;

  while (num > 1) {
    auto p = primes.next();
    auto [new_num, count] = divide_out(num, p);
    if (count > 0) {
      divisors.push_back(p);
      num = new_num;
    }
  }

  // Make a primes class that generates prime numbers lazily

  // auto primes = primes_up_to(num);
  // auto divisor_view =
  //     primes | views::filter([num](auto p) { return num % p == 0; });
  // ranges::copy(divisor_view, std::back_inserter(divisors));
  return divisors;
}
