#include "../mirea.h"

int main() {
  cout << "Enter amount of marbles (positive int required)\n";
  int marbles_amount = IntegerInput();
  if (marbles_amount < 2) {
    cout << marbles_amount << "Incorrect data entered\n";
  } else {
    int* marbles = new int[marbles_amount];
    for (int i = 0; i < marbles_amount; i++) marbles[i] = i + 1;
    int amount_of_coincidences = 0;
    do
      for (int i = 0; i < marbles_amount; i++)
        if (marbles[i] == i + 1) {
          amount_of_coincidences++;
          break;
        }
    while (next_permutation(marbles, marbles + marbles_amount));
    cout << amount_of_coincidences;
    delete[] marbles;
  }
  return 0;
}