#if 0

#include <algorithm>
#include <array>
#include <ctime>
#include <format>
#include <regex>
#include <vector>

#include "main_functions.h"

namespace {

void Practice2(size_t n) {
  std::vector<int> array;
  array.reserve(n);

  for (size_t i = 0; i != n; ++i)
    array.push_back(main_functions::IntegerInput());

  auto min_it = std::min_element(array.begin(), array.end());
  int k = main_functions::IntegerInput();

  if (k < 0) {
    std::cerr << "Incorrect input";
    return;
  }

  for (int i = 0; i < k; ++i) array.insert(array.begin(), *min_it);
}

void Practice5(std::string text) {
  std::regex pattern{
      R"([ \.,;,\-\"\\?!\(\)](\d+)|^(\d+)[ \.,;,\-\"\\?!\(\)]|[ \.,;,\-\"\\?!\(\)](\d+)$|^(\d+)$)"};
  std::smatch match;
  std::string answer;

  if (std::regex_search(text, match, pattern)) {
    answer = match.str();

    do {
      std::string match_str = match.str();

      if (match_str.length() < answer.length()) answer = match_str;

      int digits_length =
          (match_str[0] == '-') ? match_str.length() - 1 : match_str.length();

      pattern = std::vformat(
          R"([ \.,;,\-\"\\?!\(\)](-?\d{{1,{0}}})|^(-?\d{{1,{0}}})[ \.,;,\-\"\\?!\(\)]|[ \.,;,\-\"\\?!\(\)](-?\d{{1,{0}}})$|^(-?\d{{1,{0}}})$)",
          std::make_format_args(digits_length));

      text = match.suffix().str();
    } while (std::regex_search(text, match, pattern));

    std::cout << answer;
  } else
    std::cout << "No numbers in the text\n";
}

}  // namespace

#endif
