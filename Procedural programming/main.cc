#include "main_functions.h"

#include "marbles.h"
#include "practice4.h"
#include "practice5.h"
#include "practice6.h"

int main() {
  std::cout << "Greetings. This console app was written by Ilya Kramarenko, "
          "IVBO-13-23.\n";

  std::string command = "initializing";

  while (command != "break!") {
    std::cout << "Enter name of practice separate line or '0' for exit. For "
            "instance, practice4 or marbles\n";
    std::cin >> command;

    if (command == "practice4")
      procedural_programming::Practice4Run();
    else if (command == "practice5")
      procedural_programming::Practice5Run();
    else if (command == "practice6")
      procedural_programming::Practice6Run();
    else if (command == "marbles")
      procedural_programming::MarblesRun();
    else if (command == "0")
      return 0;
    else
      std::cout << "Incorrect command\n";
  }
}