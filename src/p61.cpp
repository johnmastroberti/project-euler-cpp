#include <optional>
#include <unordered_map>
#include <unordered_set>

#include "common.hpp"

struct FigFunc { /*{{{*/
 private:
  auto tria(u64 n) const { return n * (n + 1) / 2; }
  auto quad(u64 n) const { return n * n; }
  auto pent(u64 n) const { return n * (3 * n - 1) / 2; }
  auto hexa(u64 n) const { return n * (2 * n - 1); }
  auto hept(u64 n) const { return n * (5 * n - 3) / 2; }
  auto octa(u64 n) const { return n * (3 * n - 2); }

 public:
  int f = 0;

  auto operator()(u64 n) const {
    switch (f) {
      case 3:
        return tria(n);
      case 4:
        return quad(n);
      case 5:
        return pent(n);
      case 6:
        return hexa(n);
      case 7:
        return hept(n);
      case 8:
        return octa(n);
      default:
        return u64{};
    }
  }
}; /*}}}*/

auto make_figurate_vec(int f) {
  namespace stdv = rv3::views;
  std::vector<u64> result;
  result.reserve(100);
  auto four_digit_nums = stdv::iota(1ull) | stdv::transform(FigFunc(f)) |
                         stdv::drop_while([](auto n) { return n < 1000; }) |
                         stdv::take_while([](auto n) { return n < 10'000; });
  rv3::copy(four_digit_nums, std::back_inserter(result));
  return result;
}

using MapT = std::unordered_map<int, std::vector<u64>>;
auto make_fignum_map() {
  const std::array figs = {3, 4, 5, 6, 7, 8};
  MapT map;
  for (auto f : figs) map.emplace(f, make_figurate_vec(f));
  return map;
}

constexpr bool forms_link(u64 head, u64 tail) {
  return head % 100 == tail / 100;
}

using ChainsT = std::vector<std::vector<u64>>;
using SetT = std::unordered_set<int>;
ChainsT find_open_chains(u64 head, MapT const& figurates, SetT remaining_figs,
                         std::optional<int> startfig = std::nullopt) {
  ChainsT chains;
  if (remaining_figs.empty()) {
    chains.emplace_back();
    return chains;
  }

  SetT figs_to_check = startfig ? SetT{*startfig} : remaining_figs;

  for (auto fig : figs_to_check) {
    remaining_figs.erase(fig);
    for (auto fn : figurates.at(fig)) {
      if (!startfig && !forms_link(head, fn)) continue;
      for (auto&& tail : find_open_chains(fn, figurates, remaining_figs)) {
        chains.emplace_back(tail);
        chains.back().push_back(fn);
      }
    }
    remaining_figs.emplace(fig);
  }
  return chains;
}

bool is_closed_chain(std::vector<u64> const& chain) {
  return forms_link(chain.front(), chain.back());
}

void p61() {
  auto chains = find_open_chains(0, make_fignum_map(), {3, 4, 5, 6, 7, 8}, 8);
  for (auto const& c : chains)
    if (is_closed_chain(c)) print_answer(61, accumulate(c));
}
