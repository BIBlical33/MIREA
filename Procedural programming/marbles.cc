#include "marbles.h"

#include <algorithm>
#include <numeric>

#include "main_functions.h"

namespace procedural_programming {

void MarblesRun() {
  std::cout << "Enter amount of marbles (positive int required)\n";

  if (int marbles_amount = main_functions::IntegerInput();
      marbles_amount >= 2) {
    int* marbles = new int[marbles_amount];

    std::iota(marbles, marbles + marbles_amount, 1);

    int amount_of_coincidences = 0;

    do
      for (int i = 0; i != marbles_amount; ++i)
        if (marbles[i] == i + 1) {
          amount_of_coincidences++;
          break;
        }
    while (std::next_permutation(marbles, marbles + marbles_amount));

    std::cout << amount_of_coincidences << std::endl;

    delete[] marbles;
  } else {
    std::cout << marbles_amount << "Incorrect data entered\n";
  }
}

}  // namespace procedural_programming