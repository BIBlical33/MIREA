#include <algorithm>
#include <numeric>

#include "main_functions.h"
#include "practices.h"

namespace procedural_programming {

int Marbles(size_t marbles_amount) {
  if (marbles_amount == 0) {
    return 0;
  }

  int* marbles = new int[marbles_amount];

  std::iota(marbles, marbles + marbles_amount, 1);

  int amount_of_coincidences = 0;

  do {
    for (size_t i = 0; i != marbles_amount; ++i)
      if (marbles[i] == static_cast<int>(i + 1)) {
        amount_of_coincidences++;
        break;
      }
  } while (std::next_permutation(marbles, marbles + marbles_amount));

  return amount_of_coincidences;

  delete[] marbles;
}

}  // namespace procedural_programming
