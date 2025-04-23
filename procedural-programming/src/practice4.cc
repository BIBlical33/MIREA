// Copyright 2025, github.com/BIBlical33
//
// Solving Practice4 tasks.
// Task descriptions (in Russian):
// https://drive.google.com/drive/folders/1WK_ulsyjzy_g6WYER9h5GWO-sKLsl-Zm?usp=sharing
//
// License: GNU General Public License v3.0
// See: https://www.gnu.org/licenses/gpl-3.0.html

#define NOMINMAX
#include <Windows.h>

#include <algorithm>
#include <array>
#include <cmath>
#include <format>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <numbers>
#include <numeric>
#include <regex>
#include <stdexcept>
#include <string>
#include <string_view>
#include <unordered_map>
#include <utility>
#include <variant>
#include <vector>

#include "include/main_functions.h"
#include "include/practices.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;

namespace {

bool CustomIsDidgit(char symbol) {
  const int k0_ASCII_code = 48, kAmountOfDigits = 10;
  if (symbol >= k0_ASCII_code and symbol < k0_ASCII_code + kAmountOfDigits)
    return true;
  else
    return false;
}

std::vector<double> PushNumbersFromFileIntoVector(std::ifstream& fout) {
  string file_content, number = "";
  std::vector<double> numbers;

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

  return numbers;
}

double RectangleAreaCalculation(double rectangle_width,
                                double rectangle_length) {
  if (rectangle_length > 0 and rectangle_width > 0)
    return rectangle_length * rectangle_width;
  else
    throw std::invalid_argument("It isn't rectangle");
}

constexpr bool IsTriangleValid(double first_side, double second_side,
                               double third_side) noexcept {
  if (first_side > 0 and second_side > 0 and third_side > 0 and
      first_side + second_side > third_side and
      second_side + third_side > first_side and
      first_side + third_side > second_side)
    return true;
  else
    return false;
}

constexpr double TriangleAreaCalculation(double first_side, double second_side,
                                         double third_side) {
  double p = (first_side + second_side + third_side) / 2.0;

  if (IsTriangleValid(first_side, second_side, third_side))
    return std::sqrt(p * (p - first_side) * (p - second_side) *
                     (p - third_side));
  else
    throw std::invalid_argument("It isn't a triangle");
}

double CircleAreaCalculation(double radius) {
  if (radius > 0)
    return std::numbers::pi * radius * radius;
  else
    throw std::invalid_argument("It isn't a circle");
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

std::pair<std::unordered_map<char, int>, std::unordered_map<int, char>>
FillingMapsOfDigits() {
  std::unordered_map<char, int> dec_representation;
  std::unordered_map<int, char> search_digits_by_dec_value;
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

  return std::pair{dec_representation, search_digits_by_dec_value};
}

string ConversionToDemical(
    const string& number, const int old_base,
    const std::unordered_map<char, int>& dec_representation) {
  if (old_base == 10) return number;

  int dec_number = 0, reverse_digit_index = 0;

  for (int i = static_cast<int>(number.size() - 1); i >= 0; i--) {
    dec_number += dec_representation.at(number[i]) *
                  static_cast<int>(pow(old_base, reverse_digit_index));
    reverse_digit_index++;
  }

  return std::to_string(dec_number);
}

string DemicalToNewBase(
    int number, const int new_base,
    const std::unordered_map<int, char>& search_digits_by_dec_value) {
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

}  // namespace

namespace procedural_programming::practice4 {

double File() {
  std::ifstream fout(procedural_programming::CreateTxtFile("task1"));

  if (not fout.is_open()) {
    std::cerr << "Program cannot open this txt file\n";
    return 0;
  }

  std::vector<double> numbers{PushNumbersFromFileIntoVector(fout)};

  double result = std::accumulate(numbers.begin(), numbers.end(), 0.0);
  fout.close();
  return result;
}

int Sign(double x) noexcept {
  if (x > 0)
    return 1;
  else if (x == 0)
    return 0;
  else
    return -1;
}

double GeometricFigures(
    FigureType figure_type,
    const std::variant<TriangleParams, RectangleParams, CircleParams>& params) {
  switch (figure_type) {
    case FigureType::kRectangle: {
      RectangleParams rectangle_params = std::get<RectangleParams>(params);
      return RectangleAreaCalculation(rectangle_params.width,
                                      rectangle_params.height);
    }
    case FigureType::kTriangle: {
      TriangleParams triangle_params = std::get<TriangleParams>(params);
      return TriangleAreaCalculation(triangle_params.first_side,
                                     triangle_params.second_side,
                                     triangle_params.third_side);
    }
    case FigureType::kCircle: {
      CircleParams circle_params = std::get<CircleParams>(params);
      return CircleAreaCalculation(circle_params.radius);
    }
    default:
      throw std::invalid_argument("Worng type");
  }
}

void FormerGlory() {
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

void SineWave() {
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

int AutomaticRecognizer(const std::string& roman_number) {
  static const std::unordered_map<char, int> roman_digits = {
      {'I', 1},   {'V', 5},   {'X', 10},  {'L', 50},
      {'C', 100}, {'D', 500}, {'M', 1000}};

  static const std::regex valid_roman(
      R"(^(M{0,3})(CM|CD|D?C{0,3})(XC|XL|L?X{0,3})(IX|IV|V?I{0,3})$)");

  if (!std::regex_match(roman_number, valid_roman) or roman_number.size() == 0)
    throw std::invalid_argument(
        std::format("Invalid Roman number: {}", roman_number));

  int dec_number = 0, previous_dec_value_by_roman_digit = 0;

  for (int i = static_cast<int>(roman_number.size() - 1); i >= 0; --i) {
    int dec_value_by_roman_digit = roman_digits.at(roman_number[i]);
    if (dec_value_by_roman_digit < previous_dec_value_by_roman_digit)
      dec_number -= dec_value_by_roman_digit;
    else
      dec_number += dec_value_by_roman_digit;
    previous_dec_value_by_roman_digit = dec_value_by_roman_digit;
  }

  return dec_number;
}

std::vector<int> PseudorandomNumberGenerator(
    ConsistencyVariant consistency_variant, size_t consistency_length) {
  std::vector<int> s;
  s.reserve(consistency_length);

  s.push_back(0);

  int m, b, c;

  switch (consistency_variant) {
    case ConsistencyVariant::kFirstVariant:
      m = 37;
      b = 3;
      c = 64;
      break;
    case ConsistencyVariant::kSecondvariant:
      m = 25173;
      b = 13849;
      c = 65537;
      break;
    default:
      throw std::invalid_argument("Invalid consistency variant");
  }

  for (size_t i = 1; i != consistency_length; ++i)
    s.push_back((m * s[i - 1] + b) % c);

  return s;
}

void MatrixMultiplication() {
  const constexpr double A[3][4] = {{5, 2, 0, 10}, {3, 5, 2, 5}, {20, 0, 0, 0}};

  const std::unordered_map<int, std::vector<double>> B{
      {0, {1.2, 0.5}}, {1, {2.8, 0.4}}, {2, {5, 1}}, {3, {2, 1.5}}};

  double C[3][3] = {};

  for (int vendor = 0; vendor != 3; ++vendor)
    for (int product = 0; product != 4; ++product) {
      C[vendor][0] +=
          A[vendor][product] * (B.at(product)[0] - B.at(product)[1]);
      C[vendor][1] += A[vendor][product] * B.at(product)[1];
      C[vendor][2] += A[vendor][product] * B.at(product)[0];
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

string NumberSystems(string number, const int old_base, const int new_base) {
  if (old_base < 2)
    throw std::invalid_argument("Incorrect number system: " +
                                std::to_string(old_base));
  if (new_base < 2)

    throw std::invalid_argument("Incorrect number system: " +
                                std::to_string(new_base));
  if (old_base > 16 || new_base > 16)
    throw std::invalid_argument("Supports bases <= 16 only");

  static auto maps_of_digits = FillingMapsOfDigits();
  static const std::unordered_map<char, int> dec_representation =
      maps_of_digits.first;
  static const std::unordered_map<int, char> search_digits_by_dec_value =
      maps_of_digits.second;

  // Check for incorrect symbols in number
  for (char ch : number) {
    if (not dec_representation.contains(ch) or
        dec_representation.at(ch) >= old_base)
      throw std::invalid_argument("Incorrect number " + number +
                                  " in number system " +
                                  std::to_string(old_base));
  }

  return DemicalToNewBase(
      std::stoi(ConversionToDemical(number, old_base, dec_representation)),
      new_base, search_digits_by_dec_value);
}

}  // namespace procedural_programming::practice4
