#ifndef MAIN_FINCTIONS_H_
#define MAIN_FINCTIONS_H_

#include <iostream>
#include <string>

namespace main_functions {

const int constexpr inline kIncorrectUserData = -214748364;

// Creates a txt file and writes user input to it. Returns filename
std::string CreateTxtFile(std::string filename);

// Checks input value and returns it if double else returns
// main_functions::kIncorrectUserData
double DoubleInput();

// Checks DoubleInput() value and returns it if int else returns
// main_functions::kIncorrectUserData
int IntegerInput();

}  // namespace main_functions

#endif  // MAIN_FINCTIONS_H_