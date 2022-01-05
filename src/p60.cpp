#include "common.hpp"
#include "primes2.hpp"

constexpr u64 size10(u64 x) {
  u64 size = 10;
  while (size < x) size *= 10ull;
  return size;
}

constexpr u64 fcat(u64 x, u64 y) { return x * size10(y) + y; }

bool is_concat_pair(u64 p, u64 q) {
  return is_prime(fcat(p, q)) && is_prime(fcat(q, p));
}

using cpair = std::pair<u64, u64>;

template <typename T>
bool vec_contains(std::vector<T> const& v, T const& ele) {
  return std::find(v.begin(), v.end(), ele) != v.end();
}

bool forms_quad(cpair const& p1, cpair const& p2,
                [[maybe_unused]] std::vector<cpair> const& pairs) {
  std::array xterms = {cpair{p1.first, p2.first}, cpair{p1.first, p2.second},
                       cpair{p1.second, p2.first}, cpair{p1.second, p2.second}};
  return std::ranges::none_of(
             xterms, [](auto pair) { return pair.first == pair.second; }) &&
         std::ranges::all_of(xterms, [&pairs](auto pair) {
           return is_concat_pair(pair.first, pair.second);
         });
}

bool forms_quint(std::array<u64, 4> const& quad) {
  auto pmax = quad.front();
  for (auto p : primes<u64>) {
    if (p >= pmax) return false;
    if (std::ranges::all_of(quad,
                            [p](auto q) { return is_concat_pair(p, q); })) {
      spdlog::info("Found quintuple {} + {}", p, quad);
      return true;
    }
  }
}

void p60() {
  std::vector<cpair> pairs;
  u64 checked_until_ix = 0;

  for (auto p : primes<u64>) {
    // find all concatenating pairs where both members are no more than p
    for (auto q :
         primes<u64> | std::views::take_while([p](auto x) { return x < p; }))
      if (is_concat_pair(p, q)) {
        // spdlog::info("Found pair [{}, {}]", q, p);
        pairs.emplace_back(q, p);
      }

    // Check if any of the newly found pairs forms a quad
    // with any of the other pairs, and if it does, try to make a 5-tuple
    for (auto const& pair1 : pairs | rv3::views::drop(checked_until_ix))
      for (auto const& pair2 : pairs)
        if (forms_quad(pair1, pair2, pairs)) {
          std::array quad = {pair1.first, pair1.second, pair2.first,
                             pair2.second};
          std::ranges::sort(quad);
          spdlog::info("Found quad {}", quad);
          if (forms_quint(quad)) return;
        }

    checked_until_ix = pairs.size();
  }
}
