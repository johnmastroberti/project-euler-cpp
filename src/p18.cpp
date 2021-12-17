#include <optional>

#include "common.hpp"
#include "data.hpp"

auto triangle_n(auto n) { return n * (n + 1) / 2; }

// struct Node; [>{{{<]
//
// struct Node {
//   u64 value;
//   Node *c1;
//   Node *c2;
// };
//
// struct DenseTree {
//   std::optional<std::vector<Node>> nodes;
//   Node *head;
//
//   DenseTree(const char *filename, int Nrows) {
//     auto Nitems = triangle_n(Nrows);
//     auto values = get_data<u64>(filename, Nitems);
//     nodes.emplace(values.size(), Node{});
//     for (auto rix : std::views::iota(0, Nrows - 1)) {
//       for (auto cix : std::views::iota(0, rix + 1)) {
//         auto lix = triangle_n(rix) + cix;
//         auto lix1 = triangle_n(rix + 1) + cix;
//         auto lix2 = triangle_n(rix + 1) + cix + 1;
//         nodes->at(lix) = {.value = values[lix],
//                           .c1 = &nodes->at(lix1),
//                           .c2 = &nodes->at(lix2)};
//       }
//     }
//     for (auto cix : std::views::iota(0, Nrows + 1))
//       nodes->at(triangle_n(Nrows-1)
//   }
// }; [>}}}<]

struct Point {
  u64 value;
  u64 score;
};

std::istream &operator>>(std::istream &is, Point &p) {
  is >> p.value;
  p.score = p.value;
  return is;
}

template <>
struct fmt::formatter<Point> {
  template <typename FormatContext>
  auto format(const Point &p, FormatContext &ctx) -> decltype(ctx.out()) {
    return format_to(ctx.out(), "\n(value = {}, score = {})", p.value, p.score);
  }
};

void p18() {
  auto Nrows = 15;
  // read in the data
  auto data = get_data<Point>("data/p18.txt", triangle_n(Nrows));

  // each row above the bottom row should score value + max(child scores)
  for (auto rnum = Nrows - 2; rnum >= 0; rnum--) {
    for (auto i : std::views::iota(triangle_n(rnum), triangle_n(rnum + 1))) {
      auto cix1 = i + rnum + 1;
      auto cix2 = cix1 + 1;
      data[i].score += std::max(data[cix1].score, data[cix2].score);
    }
  }

  print_answer(18, data[0].score);
}
