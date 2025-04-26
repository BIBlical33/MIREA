// Copyright 2025, github.com/BIBlical33
//
// CreateTxtFile function that are used in several modules.
//
// License: GNU General Public License v3.0
// See: https://www.gnu.org/licenses/gpl-3.0.html

#include "include/create_txt_file.h"

#include <fstream>
#include <iostream>
#include <string>

namespace procedural_programming {

// Creates a txt file and writes user input to it. Returns filename
std::string CreateTxtFile(const std::string& filename) {
  std::ofstream file(filename + ".txt");

  if (not file.is_open())
    std::cerr << "The program cannot open this txt file\n";

  std::string file_content;
  std::cin >> file_content;
  while (file_content != "break!") {
    file << file_content << "\r\n";
    std::cin >> file_content;
  }

  file.close();
  return filename + ".txt";
}

}  // namespace procedural_programming
