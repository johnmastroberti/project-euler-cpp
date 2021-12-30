#pragma once
#include "common.hpp"

struct is_palindrome {
  bool operator()(std::integral auto n) {
    auto numstring = std::to_string(n);

    return std::equal(numstring.begin(), numstring.end(), numstring.rbegin(),
                      numstring.rend());
  }
};
