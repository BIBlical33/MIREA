#ifndef MAIN_H_
#define MAIN_H_
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

const int kIncorrectUserData = INT_MIN;

namespace main_functions {
string CreateTxtFile();
double DoubleInput();
int IntegerInput();
}  // namespace main_functions
#endif  // MAIN_H_