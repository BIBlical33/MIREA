#ifndef MIREA_H_
#define MIREA_H_
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

const int kIncorrectUserData = INT_MIN;

double DoubleInput() {
  string str_number;
  cin >> str_number;
  double number;
  try {
    number = stod(str_number);
  } catch (invalid_argument) {
    return kIncorrectUserData;
  } catch (out_of_range) {
    return kIncorrectUserData;
  }
  return number;
}

int IntegerInput() {
  double number = DoubleInput();
  if (number == static_cast<int>(number)) {
    return static_cast<int>(number);
  }
  return kIncorrectUserData;
}
#endif  // MIREA_H_