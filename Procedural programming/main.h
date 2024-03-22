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

// Check input value and return it if double else return kIncorrectUserData
double DoubleInput();

// Check DoubleInput() value and return it if int else return kIncorrectUserData
int IntegerInput();

}  // namespace main_functions

#endif  // MAIN_H_