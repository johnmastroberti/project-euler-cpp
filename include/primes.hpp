#pragma once
#include <map>

#include "common.hpp"

bool is_prime(u64 num);
std::vector<u64> first_n_primes(u64 n);
std::vector<u64> primes_up_to(u64 n);
std::vector<u64> unique_prime_divisors(u64 num);
std::map<u64, u64> prime_divisors(u64 num);

template <typename IntT>
class Primes {
 private:
  std::vector<IntT> m_prime_list;

 public:
  Primes() : m_prime_list() {}

  IntT next() {
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

  auto first_n(IntT n) {
    while (m_prime_list.size() < n) next();
    return ranges::take_view(m_prime_list, n);
  }

  auto up_to(IntT n) {
    while (m_prime_list.size() == 0ull || m_prime_list.back() < n) next();
    return ranges::take_while_view(m_prime_list, [n](auto p) { return p < n; });
  }
};
