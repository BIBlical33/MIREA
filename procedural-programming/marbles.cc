#include "marbles.h"

#include <algorithm>
#include <iostream>
#include <numeric>

#include "main_functions.h"

namespace procedural_programming {

void MarblesRun() {
  std::cout << "Enter amount of marbles (positive int required)\n";

  if (int input = main_functions::IntegerInput(); input >= 2) {
    size_t marbles_amount = static_cast<size_t>(input);
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

    std::cout << amount_of_coincidences << std::endl;

    delete[] marbles;
  } else {
    std::cout << input << "Incorrect data entered\n";
  }
}

}  // namespace procedural_programming
