#include "marbles.h"
#include "practice4.h"
#include "practice5.h"
#include "practice6.h"

namespace main_functions {

string CreateTxtFile() {
  cout << "What do you want to name the text file?\n";
  string filename, file_content;
  cin >> filename;
  std::ofstream file(filename + ".txt");
  if (file.is_open()) {
    cout << "What do you want to enter in file? Enter 'break!' separate line "
            "for ending\n";
    cin >> file_content;
    while (file_content != "break!") {
      file << file_content << "\r\n";
      cin >> file_content;
    }
    file.close();
  } else {
    cout << "Program cannot open this txt file\n";
  }
  return filename + ".txt";
}

double DoubleInput() {
  string str_number;
  cin >> str_number;
  double number;
  try {
    number = stod(str_number);
  } catch (std::invalid_argument) {
    return kIncorrectUserData;
  } catch (std::out_of_range) {
    return kIncorrectUserData;
  }
  return number;
}

int IntegerInput() {
  double number = DoubleInput();
  if (number == static_cast<int>(number))
    return static_cast<int>(number);
  else
    return kIncorrectUserData;
}

}  // namespace main_functions

int main() {
  cout << "Greetings. The program was written by Ilya Kramarenko, "
          "IVBO-10-23.\n";
  string command = "initializing";
  while (command != "break!") {
    cout << "Enter name of practice separate line or '0' for exit. For "
            "instance, practice4 or marbles\n";
    cin >> command;
    if (command == "practice4")
      practice4::Practice4Run();
    else if (command == "practice5")
      practice5::Practice5Run();
    else if (command == "practice6")
      practice6::Practice6Run();
    else if (command == "marbles")
      marbles::MarblesRun();
    else if (command == "0")
      return 0;
    else
      cout << "Incorrect command\n";
  }
}