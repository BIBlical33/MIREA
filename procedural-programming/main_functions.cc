#include "main_functions.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

namespace main_functions {

// Creates a txt file and writes user input to it. Returns filename
std::string CreateTxtFile(std::string filename) {
  std::ofstream file(filename + ".txt");

  std::string file_content;
  if (file.is_open()) {
    std::cin >> file_content;
    while (file_content != "break!") {
      file << file_content << "\r\n";
      std::cin >> file_content;
    }
    file.close();
  } else {
    std::cerr << "Program cannot open this txt file\n";
  }
  return filename + ".txt";
}

// Checks input value and return it if double else return
// main_functions::kIncorrectUserData
double DoubleInput() {
  std::string str_number;
  std::cin >> str_number;

  try {
    double number = stod(str_number);
    return number;
  } catch (std::invalid_argument) {
    return main_functions::kIncorrectUserData;
  } catch (std::out_of_range) {
    return main_functions::kIncorrectUserData;
  }
}

// Check DoubleInput() value and return it if int else return
// main_functions::kIncorrectUserData
int IntegerInput() {
  if (double number = DoubleInput(); number == static_cast<int>(number))
    return static_cast<int>(number);
  else
    return main_functions::kIncorrectUserData;
}

}  // namespace main_functions
