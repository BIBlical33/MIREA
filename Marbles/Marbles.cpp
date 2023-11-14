#include <algorithm>
#include <iostream>

using namespace std;

int main() {
  const int kMarblesSize = 10;
  int* marbles = new int[kMarblesSize];
  int amount_of_coincidences = 0;
  for (int i = 0; i < kMarblesSize; i++) marbles[i] = i + 1;
  do
    for (int i = 0; i < kMarblesSize; i++)
      if (marbles[i] == i + 1) {
        amount_of_coincidences++;
        break;
      }
  while (next_permutation(marbles, marbles + kMarblesSize));
  cout << amount_of_coincidences;
  delete[] marbles;
  return 0;
}
