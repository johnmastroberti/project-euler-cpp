#pragma once
#include "common.hpp"
// Generic version (supports InfInt)
template <typename T>
struct Rational { /*{{{*/
  T num, den;

  Rational(T n = T{}, T d = ++T{}) : num(n), den(d) { reduce(); }

  template <std::integral U>
  auto operator<=>(Rational<U> const& o) const {
    return num * o.den <=> den * o.num;
  }

  auto& operator+=(Rational const& o) {
    num = num * o.den + den * o.num;
    den *= o.den;
    reduce();
    return *this;
  }
  auto& operator-=(Rational const& o) {
    num = num * o.den - den * o.num;
    den *= o.den;
    reduce();
    return *this;
  }
  auto& operator*=(Rational const& o) {
    num *= o.num;
    den *= o.den;
    reduce();
    return *this;
  }
  auto& operator/=(Rational const& o) {
    num *= o.den;
    den *= o.num;
    reduce();
    return *this;
  }

  auto operator+(Rational const& o) const {
    auto ans = *this;
    ans += o;
    return ans;
  }
  auto operator-(Rational const& o) const {
    auto ans = *this;
    ans -= o;
    return ans;
  }
  auto operator*(Rational const& o) const {
    auto ans = *this;
    ans *= o;
    return ans;
  }
  auto operator/(Rational const& o) const {
    auto ans = *this;
    ans /= o;
    return ans;
  }

  auto reduce() {
    using std::gcd;
    auto g = gcd(num, den);
    num /= g;
    den /= g;
    return *this;
  }
}; /*}}}*/

// Constexpr, noexcept enabled version for builtin integral types
// template <std::integral T>
// struct Rational { [>{{{<]
//   static constexpr auto zero = T{};
//   static constexpr auto one = ++T{};
//   T num, den;
//
//   constexpr Rational(T n = zero, T d = one) noexcept : num(n), den(d) {}
//
//   template <std::integral U>
//   constexpr auto operator<=>(Rational<U> const& o) const noexcept {
//     return num * o.den <=> den * o.num;
//   }
//
//   constexpr auto& operator+=(Rational const& o) noexcept {
//     num = num * o.den + den * o.num;
//     den *= o.den;
//     return *this;
//   }
//   constexpr auto& operator-=(Rational const& o) noexcept {
//     num = num * o.den - den * o.num;
//     den *= o.den;
//     return *this;
//   }
//   constexpr auto& operator*=(Rational const& o) noexcept {
//     num *= o.num;
//     den *= o.den;
//     return *this;
//   }
//   constexpr auto& operator/=(Rational const& o) noexcept {
//     num *= o.den;
//     den *= o.num;
//     return *this;
//   }
//
//   constexpr auto operator+(Rational const& o) const noexcept {
//     auto ans = *this;
//     ans += o;
//     return ans;
//   }
//   constexpr auto operator-(Rational const& o) const noexcept {
//     auto ans = *this;
//     ans -= o;
//     return ans;
//   }
//   constexpr auto operator*(Rational const& o) const noexcept {
//     auto ans = *this;
//     ans *= o;
//     return ans;
//   }
//   constexpr auto operator/(Rational const& o) const noexcept {
//     auto ans = *this;
//     ans /= o;
//     return ans;
//   }
//
//   constexpr auto reduce() noexcept {
//     auto g = std::gcd(num, den);
//     num /= g;
//     den /= g;
//     return *this;
//   }
// }; [>}}}<]
