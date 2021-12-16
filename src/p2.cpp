#include "common.hpp"

class FibNum {
 private:
  size_t m_index;
  size_t m_value;
  size_t m_prev;

 public:
  FibNum() : m_index(0), m_value(1), m_prev(0) {}
  size_t value() const { return m_value; }

  FibNum& operator++() {
    m_index++;
    auto temp = m_value;
    m_value += m_prev;
    m_prev = temp;
    return *this;
  }

  FibNum operator++(int) {
    auto ans = *this;
    this->operator++();
    return ans;
  }

  operator size_t() const { return value(); }
};

void p2() {
  static_assert(std::weakly_incrementable<FibNum>);
  auto fibs =
      views::iota(FibNum()) |
      views::take_while([](auto const& num) { return num <= 4'000'000ull; }) |
      views::filter([](auto const& num) { return num.value() % 2 == 0; });
  auto total = accumulate(fibs, 0ull);

  spdlog::info("Problem 2: {}", total);
}
