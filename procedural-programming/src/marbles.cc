// Copyright 2025, github.com/BIBlical33
//
// Solving Marbles tasks.
// Task descriptions (in Russian):
// https://drive.google.com/drive/folders/1WK_ulsyjzy_g6WYER9h5GWO-sKLsl-Zm?usp=sharing
//
// License: GNU General Public License v3.0
// See: https://www.gnu.org/licenses/gpl-3.0.html

#include <algorithm>
#include <numeric>
#include <vector>

#include "include/main_functions.h"
#include "include/practices.h"

namespace procedural_programming {

int Marbles(size_t marbles_amount) {
  if (marbles_amount == 0)
    return 0;
  else if (marbles_amount >= 20)
    throw std::invalid_argument(
        "The function supports argument values less than 20");

  std::vector<int> marbles(marbles_amount);
  std::iota(marbles.begin(), marbles.end(), 1);

  int amount_of_coincidences = 0;

  do {
    for (size_t i = 0; i != marbles_amount; ++i)
      if (marbles[i] == static_cast<int>(i + 1)) {
        amount_of_coincidences++;
        break;
      }
  } while (std::next_permutation(marbles.begin(), marbles.end()));

  return amount_of_coincidences;
}

}  // namespace procedural_programming
