﻿#define NOMINMAX
#include <Windows.h>

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <string>
#include <vector>

#include "main_functions.h"
#include "practices.h"

namespace {

using std::cin;
using std::cout;
using std::endl;
using std::string;

bool CustomIsDidgit(char symbol) {
  const int k0_ASCII_code = 48, kAmountOfDigits = 10;
  if (symbol >= k0_ASCII_code and symbol < k0_ASCII_code + kAmountOfDigits)
    return true;
  else
    return false;
}

void PushNumbersFromFileIntoVector(std::ifstream& fout,
                                   std::vector<double>& numbers) {
  string file_content, number = "";

  while (getline(fout, file_content)) {
    // Split the string into numbers and push them into a vector
    for (size_t i = 0, iend = file_content.size(); i != iend; ++i) {
      if (CustomIsDidgit(file_content[i]) or
          (file_content[i] == '-' and CustomIsDidgit(file_content[i + 1]) and
           i != file_content.size() - 1) or
          (file_content[i] == '.' and CustomIsDidgit(file_content[i - 1]) and
           CustomIsDidgit(file_content[i + 1]) and i != 0 and
           i != file_content.size() - 1)) {
        number += file_content[i];
      } else if (i != 0 and CustomIsDidgit(file_content[i - 1])) {
        numbers.push_back(stod(number));
        number = "";
      }
    }
  }
}

void Task1() {
  std::ifstream fout(main_functions::CreateTxtFile("task1"));

  if (fout.is_open()) {
    std::vector<double> numbers;
    PushNumbersFromFileIntoVector(fout, numbers);

    cout << accumulate(numbers.begin(), numbers.end(), 0.0) << endl;

    fout.close();
  } else {
    cout << "Program cannot open this txt file\n";
  }
}

int Sign(double x) {
  if (x > 0)
    return 1;
  else if (x == 0)
    return 0;
  else
    return -1;
}

void Task2() {
  cout << "Enter x" << endl;
  double number = main_functions::DoubleInput();

  if (number == main_functions::kIncorrectUserData)
    cout << "Incorrect data entered\n";
  else
    cout << Sign(number) << endl;
}

void RectangleAreaCalculation() {
  cout << "Enter length and width of rectangle\n";
  double rectangle_width = main_functions::DoubleInput(),
         rectangle_length = main_functions::DoubleInput();

  if (rectangle_length > 0 and rectangle_width > 0)
    cout << "S = " << rectangle_length * rectangle_width << endl;
  else
    cout << "It isn't rectangle\n";
}

bool IsTriangleValid(const double& first_side, const double& second_side,
                     const double& third_side) {
  if (first_side > 0 and second_side > 0 and third_side > 0 and
      first_side + second_side > third_side and
      second_side + third_side > first_side and
      first_side + third_side > second_side)
    return true;
  else
    return false;
}

void TriangleAreaCalculation() {
  cout << "Enter three sides of triangle\n";
  double first_side = main_functions::DoubleInput(),
         second_side = main_functions::DoubleInput(),
         third_side = main_functions::DoubleInput(),
         p = (first_side + second_side + third_side) / 2.0;

  if (IsTriangleValid(first_side, second_side, third_side))
    cout << "S = "
         << sqrt(p * (p - first_side) * (p - second_side) * (p - third_side))
         << endl;
  else
    cout << "It isn't a triangle\n";
}

void CircleAreaCalculation() {
  cout << "Enter radius of circle\n";
  double r = main_functions::DoubleInput();

  if (r > 0) {
    const double kPi = std::acos(-1.0);
    cout << "S = " << kPi * r * r << endl;
  } else {
    cout << "It isn't a circle\n";
  }
}

void Task3() {
  cout << "What type of figure do u need? For:\nrectangle, enter "
          "'1'\ntriangle, enter '2'\ncircle, enter '3'\n";

  enum class FigureType {
    kRectangle = 1,
    kTriangle,
    kCircle,
    kWrongType,
  };

  switch (static_cast<FigureType>(main_functions::IntegerInput())) {
    case FigureType::kRectangle:
      RectangleAreaCalculation();
      break;
    case FigureType::kTriangle:
      TriangleAreaCalculation();
      break;
    case FigureType::kCircle:
      CircleAreaCalculation();
      break;
    default:
      cout << "Worng type\n";
      break;
  }
}

void Task4() {
  HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(handle, FOREGROUND_RED);

  cout << "               __________________________\n";

  for (int i = 0; i != 12; ++i) {
    if (i < 6) {
      SetConsoleTextAttribute(handle, 0x1F);
      cout << "* * * * * * * *";
      SetConsoleTextAttribute(handle, 0xF4);
      cout << "==========================\n";
    } else {
      cout << "=========================================\n";
    }
  }

  SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_GREEN |
                                      FOREGROUND_BLUE | FOREGROUND_INTENSITY);
}

void Task5() {
  cout << "Open the window in full screen mode\n\ny = sin(x)\n\n";

  // Debugged for |x|<10 and |y|<10 only
  const double kYAxisBeginning = 1.2, kYAxisEnd = -1.2, kXAxisBeginning = -6.0,
               kXAxisEnd = 9.0, kStep = 0.1, kPrecision = 0.05;
  const string auxiliary_line(
      static_cast<size_t>(abs(kXAxisBeginning / kStep) - 2.0), ' ');

  // Draw sin(x)
  cout << auxiliary_line << "Y ^\n";
  for (double y = kYAxisBeginning; y >= kYAxisEnd;
       y = std::round((y - kStep) * 10) / 10) {
    for (double x = kXAxisBeginning; x <= kXAxisEnd;
         x = std::round((x + kStep) * 10) / 10) {
      if (std::abs(std::sin(x) - y) <= kPrecision) {
        cout << '*';
      } else if (x == -kStep and y == kStep) {
        cout << '0';
      } else if (x == 0) {
        cout << '|';
      } else if (y == 0 and x == kXAxisEnd) {
        cout << "-> X";
      } else if (y == 0) {
        cout << '-';
      } else if (y == -1 * kStep and x > 0 and x == static_cast<int>(x)) {
        cout << x;
      } else if (y == -1 * kStep and x < 0 and
                 (x + kStep) == static_cast<int>((x + kStep))) {
        cout << x + kStep;
        x += kStep;
      } else if (x == -1 * kStep and y > 0 and y == static_cast<int>(y)) {
        cout << y;
      } else if (x == -2 * kStep and y < 0 and y == static_cast<int>(y)) {
        cout << y;
        x += kStep;
      } else {
        cout << ' ';
      }
    }
    cout << endl;
  }
}

bool HasStringFourSameCharacters(const string& str) {
  char extra_char = ' ';
  int count_of_similar_symbols_in_row = 0;
  for (size_t i = 0, iend = str.size(); i != iend; ++i) {
    if (extra_char != str[i]) {
      extra_char = str[i];
      count_of_similar_symbols_in_row = 1;
    } else {
      count_of_similar_symbols_in_row++;
    }
    if (count_of_similar_symbols_in_row == 4) {
      return true;
    }
  }
  return false;
}

int RomanToDec(string roman_number) {
  if (HasStringFourSameCharacters(roman_number)) {
    return main_functions::kIncorrectUserData;
  }

  const char kCombinationSymbol = '1';
  int dec_number = 0;

  for (size_t i = 0, iend = roman_number.size(); i != iend; ++i) {
    switch (roman_number[i]) {
      case 'I':
        if (i != roman_number.size() - 1) {
          if (roman_number[i + 1] == 'V') {
            roman_number[i] = kCombinationSymbol;
            dec_number += 4;
          } else if (roman_number[i + 1] == 'X') {
            roman_number[i] = kCombinationSymbol;
            dec_number += 9;
          } else if (roman_number[i + 1] != 'I') {
            return main_functions::kIncorrectUserData;
          } else {
            dec_number++;
          }
        } else {
          dec_number++;
        }
        break;
      case 'V':
        if (i != roman_number.size() - 1 and roman_number[i + 1] != 'I')
          return main_functions::kIncorrectUserData;
        else if ((i != 0 and roman_number[i - 1] != kCombinationSymbol) or
                 i == 0)
          dec_number += 5;
        break;
      case 'X':
        if ((roman_number[i + 1] == 'L' or roman_number[i + 1] == 'C') and
            i != roman_number.size() - 1) {
          if (i != 0 and roman_number[i - 1] == kCombinationSymbol) {
            return main_functions::kIncorrectUserData;
          } else {
            if (roman_number[i + 1] == 'L')
              dec_number += 40;
            else
              dec_number += 90;
            roman_number[i] = kCombinationSymbol;
          }
        } else if (((i != 0 and roman_number[i - 1] != kCombinationSymbol) or
                    i == 0) and
                   ((i != roman_number.size() - 1 and
                     (roman_number[i + 1] == 'X' or
                      roman_number[i + 1] == 'V' or
                      roman_number[i + 1] == 'I')) or
                    i == roman_number.size() - 1)) {
          dec_number += 10;
        } else {
          return main_functions::kIncorrectUserData;
        }
        break;
      case 'L':
        if (i != roman_number.size() - 1 and roman_number[i + 1] != 'I' and
            roman_number[i + 1] != 'V' and roman_number[i + 1] != 'X')
          return main_functions::kIncorrectUserData;
        else if ((i != 0 and roman_number[i - 1] != kCombinationSymbol) or
                 i == 0)
          dec_number += 50;
        break;
      case 'C':
        if ((roman_number[i + 1] == 'D' or roman_number[i + 1] == 'M') and
            i != roman_number.size() - 1) {
          if (i != 0 and roman_number[i - 1] == kCombinationSymbol) {
            return main_functions::kIncorrectUserData;
          } else {
            if (roman_number[i + 1] == 'D')
              dec_number += 400;
            else
              dec_number += 900;
            roman_number[i] = kCombinationSymbol;
          }
        } else if (((i != 0 and roman_number[i - 1] != kCombinationSymbol) or
                    i == 0) and
                   ((i != roman_number.size() - 1 and
                     (roman_number[i + 1] != 'C' and
                      roman_number[i + 1] != 'D' and
                      roman_number[i + 1] != 'M')) or
                    i == roman_number.size() - 1)) {
          dec_number += 100;
        } else {
          return main_functions::kIncorrectUserData;
        }
        break;
      case 'D':
        if (i != roman_number.size() - 1 and
            (roman_number[i + 1] == 'M' or roman_number[i + 1] != 'D'))
          return main_functions::kIncorrectUserData;
        else if ((i != 0 and roman_number[i - 1] != kCombinationSymbol) or
                 i == 0)
          dec_number += 500;
        break;
      case 'M':
        if (i != roman_number.size() - 1 and roman_number[i + 1] == 'M')
          return main_functions::kIncorrectUserData;
        else if ((i != 0 and roman_number[i - 1] != kCombinationSymbol) or
                 i == 0)
          dec_number += 1000;
        break;
      default:
        return main_functions::kIncorrectUserData;
    }
  }
  return dec_number;
}

void Task6() {
  cout << "Enter roman number\n";
  string roman_number;
  cin >> roman_number;

  int answer = RomanToDec(roman_number);

  if (answer != main_functions::kIncorrectUserData)
    cout << "Dec translation of this number is " << answer << endl;
  else
    cout << "It isn't roman number!\n";
}

void Task7() {
  cout << "Enter length of consistency (integer required)\n";
  int consistency_length = main_functions::IntegerInput();
  if (consistency_length >= 0) {
    std::vector<int> s;
    s.push_back(0);
    cout << "What variant of consistency do u need? (1 or 2 required)\n";
    string variant;
    cin >> variant;
    int m, b, c;
    if (variant == "1") {
      m = 37;
      b = 3;
      c = 64;
    } else if (variant == "2") {
      m = 25173;
      b = 13849;
      c = 65537;
    } else {
      cout << "Incorrect command\n";
      return;
    }
    cout << s[0] << ' ';
    for (int i = 1; i != consistency_length; ++i) {
      s.push_back((m * s[i - 1] + b) % c);
      cout << s[i] << ' ';
    }
    cout << endl;
  } else {
    cout << "Incorrect data entered\n";
  }
}

int GetVendor(double C[3][3], int row, bool option) {
  if (option == true) {
    if (C[0][row] >= C[1][row] and C[0][row] >= C[2][row]) return 1;
    if (C[1][row] >= C[2][row]) return 2;
    return 3;
  } else {
    if (C[0][row] <= C[1][row] and C[0][row] <= C[2][row]) return 1;
    if (C[1][row] <= C[2][row]) return 2;
    return 3;
  }
}

void Task8() {
  const double A[3][4] = {{5, 2, 0, 10}, {3, 5, 2, 5}, {20, 0, 0, 0}};

  std::map<int, std::vector<double>> B;

  B[0] = {1.2, 0.5};
  B[1] = {2.8, 0.4};
  B[2] = {5, 1};
  B[3] = {2, 1.5};

  double C[3][3] = {};

  for (int vendor = 0; vendor != 3; ++vendor)
    for (int product = 0; product != 4; ++product) {
      C[vendor][0] += A[vendor][product] * (B[product][0] - B[product][1]);
      C[vendor][1] += A[vendor][product] * B[product][1];
      C[vendor][2] += A[vendor][product] * B[product][0];
    }

  cout << "Max revenue = " << std::max(C[0][0], std::max(C[1][0], C[2][0]))
       << " for " << GetVendor(C, 0, 1) << " vendor\nMin revenue = "
       << std::min(C[0][0], std::min(C[1][0], C[2][0])) << " for "
       << GetVendor(C, 0, 0) << " vendor\nMax commissions = "
       << std::max(C[0][1], std::max(C[1][1], C[2][1])) << " for "
       << GetVendor(C, 1, 1) << " vendor\nMin commissions = "
       << std::min(C[0][1], std::min(C[1][1], C[2][1])) << " for "
       << GetVendor(C, 1, 0)
       << " vendor\nTotal revenue = " << C[0][0] + C[1][0] + C[2][0]
       << "\nTotal commissions = " << C[1][1] + C[0][1] + C[2][1]
       << "\nTotal money = " << C[0][2] + C[1][2] + C[2][2] << endl;
}

void FillingMapsOfDigits(std::map<char, int>& dec_representation,
                         std::map<int, char>& search_digits_by_dec_value) {
  for (int digit = 0; digit != 10; ++digit) {
    search_digits_by_dec_value[digit] = static_cast<char>(digit) + '0';
    dec_representation[static_cast<char>(digit) + '0'] = digit;
  }

  const int kA_ASCII_Index = 65, kF_ASCII_Index = 70;
  int dec_letter_representation = 10;

  for (char digit = kA_ASCII_Index; digit <= kF_ASCII_Index; ++digit) {
    search_digits_by_dec_value[dec_letter_representation] = digit;
    dec_representation[digit] = dec_letter_representation++;
  }
}

string ConversionToDemical(const string& number, const int old_base,
                           const std::map<char, int>& dec_representation) {
  if (old_base == 10) return number;

  int dec_number = 0, reverse_digit_index = 0;

  for (auto i = number.size() - 1; i >= 0; i--) {
    dec_number += dec_representation.at(number[i]) *
                  static_cast<int>(pow(old_base, reverse_digit_index));
    reverse_digit_index++;
  }

  return std::to_string(dec_number);
}

string DemicalToNewBase(int number, const int new_base,
                        const std::map<int, char>& search_digits_by_dec_value) {
  if (new_base == 10) return std::to_string(number);

  string conversion_number;

  while (number > new_base - 1) {
    conversion_number += search_digits_by_dec_value.at(number % new_base);
    number /= new_base;
  }

  conversion_number += search_digits_by_dec_value.at(number);
  std::reverse(conversion_number.begin(), conversion_number.end());

  return conversion_number;
}

string ConversionBetweenNumberSystems(string number, const int old_base,
                                      const int new_base) {
  if (old_base < 2)
    return "Incorrect number system: " + std::to_string(old_base);
  if (new_base < 2)
    return "Incorrect number system: " + std::to_string(new_base);
  if (old_base > 16 || new_base > 16) return "Supports bases <= 16 only";

  static std::map<char, int> dec_representation;
  static std::map<int, char> search_digits_by_dec_value;

  if (static bool is_filling_maps_of_digits_called;
      !is_filling_maps_of_digits_called) {
    FillingMapsOfDigits(dec_representation, search_digits_by_dec_value);
    is_filling_maps_of_digits_called = true;
  }

  // Check for incorrect symbols in number
  for (char ch : number) {
    if (dec_representation.count(ch) == 0 || dec_representation[ch] >= old_base)
      return "Incorrect number\n";
  }

  return DemicalToNewBase(
      std::stoi(ConversionToDemical(number, old_base, dec_representation)),
      new_base, search_digits_by_dec_value);
}

void Task9() {
  cout << "Enter positive integer\n";
  string number;
  cin >> number;

  cout << "Enter two positive integers in separate lines: the original number "
          "system and the new "
          "number system to convert\n";
  int old_base = main_functions::IntegerInput(),
      new_base = main_functions::IntegerInput();

  cout << ConversionBetweenNumberSystems(number, old_base, new_base) << endl;
}

}  // namespace

namespace procedural_programming {

void Practice4Run() {
  int command = 1;

  while (command != 0) {
    cout << "Enter task number separate digit or '0' for exit\n";
    command = main_functions::IntegerInput();

    if (command == 1)
      Task1();
    else if (command == 2)
      Task2();
    else if (command == 3)
      Task3();
    else if (command == 4)
      Task4();
    else if (command == 5)
      Task5();
    else if (command == 6)
      Task6();
    else if (command == 7)
      Task7();
    else if (command == 8)
      Task8();
    else if (command == 9)
      Task9();
    else if (command == 0)
      break;
    else
      cout << "Wrong command.\n";
  }
}

}  // namespace procedural_programming
