#include "InfInt.h"
#include "common.hpp"
#include "rational.hpp"
#include "tqdm.h"

bool more_digits_in_num(Rational<InfInt> const& r) {
  return r.num.toString().size() > r.den.toString().size();
}

void p57() {
  std::vector<Rational<InfInt>> iters;
  iters.reserve(1000);
  tqdm bar;
  auto generator = [&bar, i = 1, x = Rational(InfInt{2}, InfInt{1}),
                    one = Rational(InfInt{1}, InfInt{1})]() mutable {
    bar.progress(i++, 1000);
    x = one + one / x;
    return x;
  };
  std::ranges::generate_n(std::back_inserter(iters), 1000, generator);
  bar.finish();
  print_answer(57, std::ranges::count_if(iters, more_digits_in_num));
}
