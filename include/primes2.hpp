#pragma once
#include <map>

#include "common.hpp"

template <std::integral IntT>
class Primes {
 private:
  static std::vector<IntT> m_prime_list;

  class Iterator { /*{{{*/
   private:
    u64 index;

   public:
    Iterator(u64 ix = 0) : index(ix) {}
    auto operator*() const { return m_prime_list[index]; }

    auto& operator++() {
      ++index;
      if (index == m_prime_list.size()) find_next_prime();
      return *this;
    }

    auto operator++(int) {
      auto ans = *this;
      this->operator++();
      return ans;
    }

    auto& operator--() {
      if (index == 0) return *this;
      --index;
      return *this;
    }

    auto& operator--(int) {
      auto ans = *this;
      this->operator--();
      return ans;
    }

    auto& operator+=(std::integral auto x) {
      index += x;
      while (index > m_prime_list.size()) find_next_prime();
      return *this;
    }

    auto& operator-=(std::integral auto x) {
      index -= std::max(x, index);
      return *this;
    }

    auto operator+(std::integral auto x) const {
      auto ans = *this;
      ans += x;
      return ans;
    }

    auto operator-(std::integral auto x) const {
      auto ans = *this;
      ans -= x;
      return ans;
    }

    std::int64_t operator-(Iterator const& o) {
      return o.index > index ? o.index - index : index - o.index;
    }

    using difference_type = std::int64_t;
    using value_type = IntT;
    using pointer = IntT*;
    using reference = IntT&;
    using iterator_category = std::bidirectional_iterator_tag;
  }; /*}}}*/

  static void find_next_prime() { /*{{{*/
    if (m_prime_list.size() == 0)
      return m_prime_list.push_back(2);
    else if (m_prime_list.size() == 1)
      return m_prime_list.push_back(3);

    auto p = m_prime_list.back() + 2;
    for (;; p += 2) {
      auto p_is_prime = ranges::none_of(
          m_prime_list | views::take_while([p](auto x) { return x * x <= p; }),
          [p](auto x) { return p % x == 0; });
      if (p_is_prime) return m_prime_list.push_back(p);
    }
  } /*}}}*/

 public:
  Primes() = default;

  auto begin() const { return Iterator(); }
  auto end() const { return std::unreachable_sentinel_t{}; }

  auto operator[](std::size_t ix) {
    auto it = begin();
    it += ix;
    return *it;
  }
};

template <std::integral IntT>
std::vector<IntT> Primes<IntT>::m_prime_list = {2, 3};

template <std::integral IntT>
auto primes = Primes<IntT>();

bool is_prime(std::integral auto num) {
  auto possible_factors =
      primes<decltype(num)> |
      rv3::views::take_while([s = static_cast<std::intmax_t>(std::sqrt(num))](
                                 auto p) { return std::cmp_less(p, s); });
  return std::ranges::none_of(possible_factors,
                              [num](auto p) { return num % p == 0; });
}

std::vector<u64> unique_prime_divisors(u64 num);
std::map<u64, u64> prime_divisors(u64 num);
u64 sum_of_factors(u64 n);  // proper divisors only
