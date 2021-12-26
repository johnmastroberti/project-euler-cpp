#include "common.hpp"

bool is_palindrome_str(std::string const& s) {
  return std::equal(s.begin(), s.end(), s.rbegin(), s.rend());
}

bool is_palindrome_10(u64 n) {
  if (n % 10 == 0) return false;
  auto chars = std::to_string(n);
  return is_palindrome_str(chars);
}

std::string to_binary_revstring(u64 n) {
  std::string result;
  for (; n > 0u; n /= 2) result.push_back(n % 2 ? '1' : '0');
  return result;
}

bool is_palindrome_2(u64 n) {
  if (n % 2 == 0) return false;
  auto chars = to_binary_revstring(n);
  return is_palindrome_str(chars);
}

bool is_double_palindrome(u64 n) {
  return is_palindrome_2(n) && is_palindrome_10(n);
}

void p36() {
  auto nums = std::views::iota(1ull, 1'000'000ull) |
              std::views::filter(is_double_palindrome);
  print_answer(36, accumulate(nums));
}
