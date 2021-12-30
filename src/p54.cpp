#include <span>

#include "common.hpp"
#include "data.hpp"

enum class Suit { C, H, D, S, Bad }; /*{{{*/

char to_char(Suit s) {
  using enum Suit;
  switch (s) {
    case C:
      return 'C';
    case H:
      return 'H';
    case D:
      return 'D';
    case S:
      return 'S';
    case Bad:
    default:
      return 'X';
  }
}

struct Card {
  int value;
  Suit suit;
};

template <>
struct fmt::formatter<Card> {
  template <typename FormatContext>
  auto format(const Card& c, FormatContext& ctx) -> decltype(ctx.out()) {
    return format_to(ctx.out(), "{}{}", c.value, to_char(c.suit));
  }
};

int char_to_cardval(char c) {
  constexpr std::span vals("23456789TJQKA", 13);
  auto it = std::ranges::find(vals, c);
  if (it == vals.end())
    return -1;
  else
    return static_cast<int>(it - vals.begin());
}

Suit char_to_suit(char c) {
  using enum Suit;
  switch (c) {
    case 'C':
      return C;
    case 'H':
      return H;
    case 'D':
      return D;
    case 'S':
      return S;
    default:
      return Bad;
  }
}

std::istream& operator>>(std::istream& stream, Card& c) {
  std::string str;
  stream >> str;
  assert(str.size() == 2);
  c.value = char_to_cardval(str[0]);
  c.suit = char_to_suit(str[1]);
  return stream;
} /*}}}*/

struct PokerHand {
  // Data members
  std::array<Card, 5> cards;

  // Rank type and rank values
  struct Rank {
    int rank;
    std::array<int, 5> backups;
    static constexpr int royal_flush = 10;
    static constexpr int straight_flush = 9;
    static constexpr int four_of_kind = 8;
    static constexpr int full_house = 7;
    static constexpr int flush = 6;
    static constexpr int straight = 5;
    static constexpr int three_of_kind = 4;
    static constexpr int two_pair = 3;
    static constexpr int one_pair = 2;
    static constexpr int high_card = 1;
    auto operator<=>(Rank const&) const = default;
  };

  auto get_card_values() const {
    std::array<int, 5> vals;
    std::ranges::transform(cards, vals.begin(),
                           [](Card const& c) { return c.value; });
    return vals;
  }

  Rank test_straight_flushes() const {
    auto is_straight =
        ranges::adjacent_find(cards, [](Card const& c1, Card const& c2) {
          return c1.value - 1 != c2.value;
        }) == cards.end();
    auto is_flush = ranges::all_of(
        cards,
        [suit = cards[0].suit](Card const& c) { return c.suit == suit; });

    if (!is_straight && !is_flush) return {.rank = 0, .backups = {}};

    Rank result;
    result.backups = get_card_values();
    if (is_straight && is_flush)
      result.rank =
          cards[0].value == 12 ? Rank::royal_flush : Rank::straight_flush;
    else if (is_straight)
      result.rank = Rank::straight;
    else
      result.rank = Rank::flush;
    return result;
  }

  Rank test_n_of_kinds() const {
    // Does 4, 3 of kind, pairs, and full house
    // four and three of a kind
    auto midval = cards[2].value;
    auto end_non_mid =
        midval == cards[0].value ? cards[4].value : cards[0].value;
    auto pred43 = [val = midval](Card const& c) { return c.value == val; };
    auto n_of_kind = std::ranges::count_if(cards, pred43);
    std::array<int, 5> backs = {0, 0, 0, 0, 0};
    auto copy_not_equal = [&backs, this](int value, int offset) {
      std::ranges::copy_if(get_card_values(), backs.begin() + offset,
                           [value](int v) { return v != value; });
    };
    if (n_of_kind == 4) {
      return {.rank = Rank::four_of_kind,
              .backups = {midval, end_non_mid, 0, 0, 0}};
    }
    if (n_of_kind == 3) {
      // Check for full house
      if (cards[0].value == cards[1].value && cards[3].value == cards[4].value)
        return {.rank = Rank::full_house,
                .backups = {midval, end_non_mid, 0, 0, 0}};
      else {  // not a full house, just 3 of a kind
        backs[0] = midval;
        copy_not_equal(midval, 1);
        return {.rank = Rank::three_of_kind, .backups = backs};
      }
    }

    // check for pairs
    auto p1 = std::ranges::adjacent_find(cards, {},
                                         [](auto const& c) { return c.value; });
    if (p1 == cards.end()) return {.rank = 0, .backups = {}};  // no pairs
    auto p2 = std::ranges::adjacent_find(p1 + 1, cards.end(), {},
                                         [](auto const& c) { return c.value; });
    if (p2 == cards.end()) {  // one pair
      backs[0] = p1->value;
      copy_not_equal(p1->value, 1);
      return {.rank = Rank::one_pair, .backups = backs};
    } else {
      backs[0] = p1->value;
      backs[1] = p2->value;
      if (p1 == cards.begin()) {
        if (p2 == cards.begin() + 2)
          backs[2] = cards[4].value;
        else
          backs[2] = cards[2].value;
      } else
        backs[2] = cards[0].value;
      return {.rank = Rank::two_pair, .backups = backs};
    }
  }

  Rank rank() const {
    if (auto ans = test_straight_flushes(); ans.rank != 0) {
      return ans;
    } else if (auto ans2 = test_n_of_kinds(); ans2.rank != 0) {
      return ans2;
    } else {
      return {.rank = Rank::high_card, .backups = get_card_values()};
    }
  }
};

std::istream& operator>>(std::istream& stream, PokerHand& ph) {
  std::copy_n(std::istream_iterator<Card>(stream), 5, ph.cards.begin());
  std::ranges::sort(ph.cards, std::greater(),
                    [](Card const& c) { return c.value; });
  return stream;
}

const char* rank_to_str(int rank) {
  switch (rank) {
    case PokerHand::Rank::royal_flush:
      return "Royal Flush";
    case PokerHand::Rank::straight_flush:
      return "Straight Flush";
    case PokerHand::Rank::four_of_kind:
      return "Four of a Kind";
    case PokerHand::Rank::full_house:
      return "Full House";
    case PokerHand::Rank::flush:
      return "Flush";
    case PokerHand::Rank::straight:
      return "Straight";
    case PokerHand::Rank::three_of_kind:
      return "Three of a Kind";
    case PokerHand::Rank::two_pair:
      return "Two Pair";
    case PokerHand::Rank::one_pair:
      return "One Pair";
    case PokerHand::Rank::high_card:
      return "High Card";
    default:
      return "ERROR";
  }
}

void p54() {
  auto hands = get_data<PokerHand>("data/p54.txt", 2000);
  auto result =
      rv3::count_if(hands | rv3::views::chunk(2), [](auto const& cview) {
        return cview.begin()->rank() > (++cview.begin())->rank();
      });
  auto ties =
      rv3::count_if(hands | rv3::views::chunk(2), [](auto const& cview) {
        return cview.begin()->rank() == (++cview.begin())->rank();
      });
  fmt::print("Number of ties: {}\n", ties);
  print_answer(54, result);
}
