#include "common.hpp"

template <u64 N>
class u64_mod {
 private:
  u64 n;
  void apply_mod() { n = n % N; }

 public:
  u64_mod(u64 value = 0) : n(value) {}

  auto& operator+=(u64_mod other) {
    n += other.n;
    apply_mod();
    return *this;
  }
  auto& operator*=(u64_mod other) {
    n *= other.n;
    apply_mod();
    return *this;
  }

  operator u64() const { return n; }
};

template <u64 N>
auto operator+(u64_mod<N> x, u64_mod<N> y) {
  x += y;
  return x;
}
template <u64 N>
auto operator*(u64_mod<N> x, u64_mod<N> y) {
  x *= y;
  return x;
}

template <u64 N>
auto pow(u64_mod<N> x, u64 p) {
  u64_mod<N> ans(1);
  while (p-- > 0) ans *= x;
  return ans;
}

void p48() {
  constexpr u64 M = 1'00000'00000;
  auto ans =
      accumulate(std::views::iota(1ull, 1001ull) |
                 std::views::transform([](auto x) { return pow<M>(x, x); }));
  print_answer(48, ans);
}
