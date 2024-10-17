#ifndef MAIN_H_
#define MAIN_H_

#include <algorithm>
#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

const int kIncorrectUserData = INT_MIN;

namespace main_functions {

// Creates a txt file and writes user input to it. Returns filename
string CreateTxtFile();

// Checks input value and returns it if double else returns kIncorrectUserData
double DoubleInput();

// Checks DoubleInput() value and returns it if int else returns
// kIncorrectUserData
int IntegerInput();

}  // namespace main_functions

#endif  // MAIN_H_