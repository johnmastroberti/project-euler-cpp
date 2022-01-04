#include <gmp.h>

#include <cstdlib>
#include <unordered_map>

#include "common.hpp"
#include "primes2.hpp"

template <int Nele>
using decomp_t = std::array<int, Nele>;

template <int Nele>
auto decomp_concat(int first, decomp_t<Nele> rest) {
  decomp_t<Nele + 1> result;
  result[0] = first;
  std::ranges::copy(rest, result.begin() + 1);
  return result;
}

template <int Nele>
std::vector<decomp_t<Nele>> sum_decompositions(int sum, int min_ele = 0) {
  assert(sum >= 0);
  std::vector<decomp_t<Nele>> decompositions;

  if constexpr (Nele == 1) {
    if (sum >= min_ele) decompositions.push_back({sum});
  } else {
    if (sum - min_ele <= min_ele) return {};

    for (auto i = min_ele; i < sum - min_ele; i++) {
      std::ranges::transform(
          sum_decompositions<Nele - 1>(sum - i, i + 1),
          std::back_inserter(decompositions),
          [i](auto const& tup) { return decomp_concat<Nele - 1>(i, tup); });
    }
  }
  return decompositions;
}

u64 concat(u64 x, u64 y) {
  return std::stoull(std::to_string(x) + std::to_string(y));
}

static constexpr std::array old_primes = {3, 7, 109, 673};

bool is_cat_prime(u64 p) {
  static u64 size = 0;
  constexpr u64 chunk_size = 100'000;
  if (p % 3 != 1) return false;
  if (p > size) {
    size += chunk_size;
    spdlog::info("Checking {}", p);
  }
  return std::ranges::all_of(old_primes, [p](auto op) {
    return is_prime(concat(p, op)) && is_prime(concat(op, p));
  });
}

void p60_first_attempt() { /*{{{*/
  assert(concat(3, 5) == 35);
  assert(concat(420, 69) == 42069);

  auto p_it = std::ranges::find_if(
      primes<u64>, [](auto p) { return p > 673 && is_cat_prime(p); });

  spdlog::info("Found the last prime: {}", *p_it);

  print_answer(60, accumulate(old_primes) + *p_it);
} /*}}}*/

static constexpr u64 N = 100'000;  // number of primes to check up to
static constexpr auto M = 5;       // size of the concatenating set

auto make_prime_array(std::vector<u64> const& primelist,
                      std::array<int, M> const& choices) {
  std::array<u64, M> result;
  std::ranges::transform(choices, result.begin(),
                         [&](auto ix) { return primelist.at(ix); });
  return result;
}

constexpr u64 size10(u64 n) {
  u64 ans = 10;
  while (n > ans) ans *= 10ull;
  return ans;
}

constexpr u64 fcat(u64 x, u64 y) { return x * size10(y) + y; }

class Mpz {
 private:
  mpz_t m_ele;

 public:
  Mpz(std::string const& s) {
    mpz_init(m_ele);
    mpz_set_str(m_ele, s.c_str(), 10);
  }

  Mpz(const Mpz&) = delete;
  Mpz& operator=(const Mpz&) = delete;

  Mpz& operator=(std::string const& s) {
    mpz_set_str(m_ele, s.c_str(), 10);
    return *this;
  }

  ~Mpz() { mpz_clear(m_ele); }

  bool is_prime() const { return mpz_probab_prime_p(m_ele, 0) > 0; }
};

bool check_prime(u64 x, u64 y) {
  static std::unordered_map<u64, bool> prev_checked;
  if (auto it = prev_checked.find(x*y); it != prev_checked.end())
    return it->second;

  auto sx = std::to_string(x);
  auto sy = std::to_string(y);

  bool result =
      is_prime(std::stoull(sx + sy)) && is_prime(std::stoull(sy + sx));
  prev_checked.emplace(x*y, result);
  return result;

  // Mpz p = sx + sy;
  // if (!p.is_prime()) return false;
  // p = sy + sx;
  // if (!p.is_prime()) return false;
  // return true;
}

bool is_cat_set(std::array<u64, M> const& pset) {
  if (pset[0] != 3 &&
      std::ranges::any_of(
          pset, [firstmod = pset[0] % 3](auto p) { return p % 3 != firstmod; }))
    return false;
  for (auto i = 0; i < M; i++)
    for (auto j = i + 1; j < M; j++)
      // if (!is_prime(fcat(pset[i], pset[j])) ||
      //     !is_prime(fcat(pset[j], pset[i])))
      if (!check_prime(pset[i], pset[j])) return false;
  return true;
}

void p60_blah() {
  std::vector<u64> my_primes;
  my_primes.reserve(N);
  std::ranges::copy_n(primes<u64>.begin() + 1, N,
                      std::back_inserter(my_primes));
  std::array<u64, M> pset;
  std::vector<decltype(pset)> good_quads;
  for (int sum = 0; sum < 500; sum++) {
    // spdlog::info("Checking sum = {}", sum);
    for (auto choices : sum_decompositions<M>(sum)) {
      pset = make_prime_array(my_primes, choices);
      if (is_cat_set(pset)) {
        print(pset);
        good_quads.push_back(pset);
        return;
      }
    }
  }

  print(good_quads);
}

void p60_dirty() {
  std::vector<u64> my_primes;
  my_primes.reserve(N);
  my_primes.push_back(3);
  std::ranges::copy(primes<u64> | rv3::views::drop(3) | rv3::views::take(N - 1),
                    std::back_inserter(my_primes));

  bool good_settings = true;
  auto getsetting = [&good_settings](const char* var) {
    const char* s = std::getenv(var);
    if (!s) {
      spdlog::error("{} not provided", var);
      good_settings = false;
      return 0ull;
    }
    return std::strtoull(s, nullptr, 10);
  };

  const u64 base = getsetting("EULERBASE");
  const u64 offset = getsetting("EULEROFFSET");
  const u64 inc = getsetting("EULERINC");
  if (!good_settings) return;

  std::array<u64, M> pset;
  for (u64 sum = base + offset; sum < N; sum += inc) {
    spdlog::info("Checking sum = {}", sum);
    for (u64 i = 0; i < sum; i++)
      for (u64 j = i + 1; i + j < sum; j++)
        for (u64 k = j + 1; i + j + k < sum; k++)
          for (u64 l = k + 1; i + j + k + l < sum; l++) {
            u64 m = sum - i - j - k - l;
            if (m <= l) break;
            pset = {my_primes[i], my_primes[j], my_primes[k], my_primes[l],
                    my_primes[m]};
            if (is_cat_set(pset)) {
              print(pset);
              return;
            }
          }
  }
}

void p60() { p60_dirty(); }

// bool is_cat_prime2(std::array<int, 4> const& seed, u64 p) {
//   return std::ranges::all_of(seed, [p](auto op) {
//     return is_prime(concat(p, op)) && is_prime(concat(op, p));
//   });
// }
//
// void p60() {
//   std::array seeds = {std::array{3, 7, 109, 673}, std::array{23, 311, 677, 827},
//                       std::array{3, 37, 67, 2377}, std::array{3, 17, 449, 2069},
//                       std::array{11, 23, 743, 1871}};
//   for (auto p : primes<u64>) {
//     spdlog::info("Checking p = {}", p);
//     for (auto const& s : seeds)
//       if (is_cat_prime2(s, p)) spdlog::info("Found the set {}, {}", s, p);
//   }
// }
