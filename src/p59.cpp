#include <cctype>
#include <filesystem>

#include "common.hpp"
#include "data.hpp"
#include "tqdm.h"

using uc = char;

uc to_uc(int x) { return static_cast<uc>(x); }

void make_char_data(const char* intfilename, const char* charfilename) {
  if (std::filesystem::exists(charfilename)) return;

  auto intdata = get_data<int>(intfilename);
  auto charfile = std::ofstream(charfilename);
  if (!charfile.good())
    spdlog::error("Count not open {} for writing", charfilename);
  std::ranges::transform(intdata, std::ostream_iterator<char>(charfile),
                         [](int x) { return static_cast<uc>(x); });
}

std::array<uc, 3> to_password(int n) {
  // if (n == 0) spdlog::warn("Got zero in the password generator");
  std::array<uc, 3> pw = {'a', 'a', 'a'};
  std::ranges::for_each(pw, [&n](auto& c) {
    c += static_cast<uc>(n % 26);
    n /= 26;
  });
  return pw;
}

auto decrypt(auto const& data, auto const& password) {
  return rv3::zip_view(data, password | rv3::views::cycle) |
         rv3::views::transform([](auto tup) {
           auto [x, y] = tup;
           return static_cast<uc>(x xor y);
         });
}

void show(auto const& message) {
  const char* sep = "\n--------------------------------------------------";
  for (auto c : message) std::putchar(c);
  std::puts(sep);
}

auto count_good_words(auto&& range) {
  using namespace std::literals;
  std::array search_words = {"square"s, "diameter"s, "and"s, "the"s, "that"s};
  auto words = range | rv3::views::split(' ');
  return rv3::count_if(words, [&search_words](auto const& word) {
    return rv3::any_of(
        search_words, [&word](auto const& sw) { return rv3::equal(word, sw); });
  });
}

void p59() {
  make_char_data("data/p59.txt", "data/p59chars.txt");
  auto data = get_data<uc>("data/p59chars.txt");

  auto plaintext = std::vector<uc>(data.size(), 'a');
  auto passwords =
      std::views::iota(0, 26 * 26 * 26) | std::views::transform(to_password);
  tqdm bar;
  auto score_pw = [&bar, &plaintext, &data, i = 0](auto const& pw) mutable {
    bar.progress(i++, 26 * 26 * 26);
    rv3::copy(decrypt(data, pw), plaintext.begin());
    return count_good_words(plaintext);
  };

  auto scores = std::vector<int>(passwords.size(), 0);
  rv3::transform(passwords, scores.begin(), score_pw);
  bar.finish();

  auto max_it = rv3::max_element(scores);
  print(rv3::count(scores, *max_it));
  for (int ix = 0; auto pw : passwords)
    if (scores[ix++] == *max_it) show(decrypt(data, pw));

  auto best_pw = passwords.begin() + std::distance(scores.begin(), max_it);
  print_answer(59, accumulate(decrypt(data, *best_pw), 0ull));
}
