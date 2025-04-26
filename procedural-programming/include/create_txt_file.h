// Copyright 2025, github.com/BIBlical33
//
// CreateTxtFile function that are used in several modules.
//
// License: GNU General Public License v3.0
// See: https://www.gnu.org/licenses/gpl-3.0.html

#ifndef PROCEDURAL_PROGRAMMING_INCLUDE_CREATE_TXT_FILE_H_
#define PROCEDURAL_PROGRAMMING_INCLUDE_CREATE_TXT_FILE_H_

#include <string>

namespace procedural_programming {

// Creates a txt file and writes user input to it. Returns filename
std::string CreateTxtFile(const std::string& filename);

}  // namespace procedural_programming

#endif  // PROCEDURAL_PROGRAMMING_INCLUDE_CREATE_TXT_FILE_H_
