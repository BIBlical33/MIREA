#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

double DoubleInput() {
  string str_number;
  cin >> str_number;
  double number;
  try {
    number = stod(str_number);
  } catch (invalid_argument) {
    return INT_MIN;
  } catch (out_of_range) {
    return INT_MIN;
  }
  return number;
}

int IntegerInput() {
  double number = DoubleInput();
  if (number == int(number)) {
    return int(number);
  }
  return INT_MIN;
}

int main() {
  cout << "Enter amount of marbles (positive int required)\n";
  int marbles_size = IntegerInput();
  marbles_size++;
  if (marbles_size < 1) {
    cout << marbles_size << "Incorrect data entered\n";
    return 0;
  }
  int* marbles = new int[marbles_size];
  int amount_of_coincidences = 0;
  for (int i = 0; i < marbles_size; i++) marbles[i] = i + 1;
  do
    for (int i = 0; i < marbles_size; i++)
      if (marbles[i] == i + 1) {
        amount_of_coincidences++;
        break;
      }
  while (next_permutation(marbles, marbles + marbles_size));
  cout << amount_of_coincidences;
  delete[] marbles;
  return 0;
}
