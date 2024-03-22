#include "marbles.h"

#include "main.h"

namespace marbles {

void MarblesRun() {
  cout << "Enter amount of marbles (positive int required)\n";
  int marbles_amount = main_functions::IntegerInput();
  if (marbles_amount >= 2) {
    int* marbles = new int[marbles_amount];
    std::iota(marbles, marbles + marbles_amount, 1);
    int amount_of_coincidences = 0;
    do
      for (int i = 0; i < marbles_amount; i++)
        if (marbles[i] == i + 1) {
          amount_of_coincidences++;
          break;
        }
    while (std::next_permutation(marbles, marbles + marbles_amount));
    cout << amount_of_coincidences << endl;
    delete[] marbles;
  } else {
    cout << marbles_amount << "Incorrect data entered\n";
  }
}

}  // namespace marbles