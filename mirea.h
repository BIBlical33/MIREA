#ifndef MIREA_H_
#define MIREA_H_

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

#endif  // !MIREA_H_