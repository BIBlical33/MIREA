#include "practice4.h"

namespace {
bool CustomIsDidgit(char symbol) {
  const int k0_ASCII_code = 48, kAmountOfDigits = 10;
  if (symbol >= k0_ASCII_code and symbol < k0_ASCII_code + kAmountOfDigits)
    return true;
  else
    return false;
}

void PushNumbersFromFileIntoVector(std::ifstream& fout, std::vector<double>& numbers) {
  std::string file_content, number = "";
  while (getline(fout, file_content)) {
    // Split the std::string into numbers and push them into a vector
    for (int i = 0; i < file_content.size(); i++) {
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
  std::ifstream fout(main_functions::CreateTxtFile());
  if (fout.is_open()) {
    std::vector<double> numbers;
    PushNumbersFromFileIntoVector(fout, numbers);
    std::cout << accumulate(numbers.begin(), numbers.end(), 0.0)
         << '\n';  // std::vector's elements summation
    fout.close();
  } else {
    std::cout << "Program cannot open this txt file\n";
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
  std::cout << "Enter x" << '\n';
  double number = main_functions::DoubleInput();
  if (number == kIncorrectUserData)
    std::cout << "Incorrect data entered\n";
  else
    std::cout << Sign(number) << '\n';
}

void RectangleAreaCalculation() {
  std::cout << "Enter length and width of rectangle\n";
  double rectangle_width = main_functions::DoubleInput(),
         rectangle_length = main_functions::DoubleInput();
  if (rectangle_length > 0 and rectangle_width > 0)
    std::cout << "S = " << rectangle_length * rectangle_width << '\n';
  else
    std::cout << "It isn't rectangle\n";
}

void TriangleAreaCalculation() {
  std::cout << "Enter three sides of triangle\n";
  double triangle_first_side = main_functions::DoubleInput(),
         triangle_second_side = main_functions::DoubleInput(),
         triangle_third_side = main_functions::DoubleInput(),
         p = (triangle_first_side + triangle_second_side +
              triangle_third_side) /
             2.0;
  if (triangle_first_side > 0 and triangle_second_side > 0 and
      triangle_third_side > 0 and
      triangle_first_side + triangle_second_side > triangle_third_side and
      triangle_second_side + triangle_third_side > triangle_first_side and
      triangle_first_side + triangle_third_side > triangle_second_side)
    std::cout << "S = "
         << sqrt(p * (p - triangle_first_side) * (p - triangle_second_side) *
                 (p - triangle_third_side))
         << '\n';
  else
    std::cout << "It isn't a triangle\n";
}

void CircleAreaCalculation() {
  std::cout << "Enter radius of circle\n";
  double r = main_functions::DoubleInput();
  if (r > 0)
    std::cout << "S = " << M_PI * r * r << '\n';
  else
    std::cout << "It isn't a circle\n";
}

void Task3() {
  std::cout << "What type of figure do u need? For:\nrectangle, enter "
          "'1'\ntriangle, enter '2'\ncircle, enter '3'\n";
  enum class FigureType {
    kRectangle = 1,
    kTriangle,
    kCircle,
    kWrongType,
  };
  FigureType figure_type =
      static_cast<FigureType>(main_functions::IntegerInput());
  switch (figure_type) {
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
      std::cout << "Worng type\n";
      break;
  }
}

void Task4() {
  HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(handle, FOREGROUND_RED);
  std::cout << "               __________________________\n";
  for (int i = 0; i < 12; i++) {
    if (i < 6) {
      SetConsoleTextAttribute(handle, 0x1F);
      std::cout << "* * * * * * * *";
      SetConsoleTextAttribute(handle, 0xF4);
      std::cout << "==========================\n";
    } else {
      std::cout << "=========================================\n";
    }
  }
  SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_GREEN |
                                      FOREGROUND_BLUE | FOREGROUND_INTENSITY);
}

void Task5() {
  std::cout << "y = sin(x)\n\n";
  // Debugged for |x|<10 and |y|<10 only
  const double kYAxisBeginning = 1.2, kYAxisEnd = -1.2, kXAxisBeginning = -6.0,
               kXAxisEnd = 9.0, kStep = 0.1, kPrecision = 0.05;
  std::string auxiliary_line(abs(kXAxisBeginning / kStep) - 2.0, ' ');
  std::cout << auxiliary_line << "Y ^\n";
  for (double y = kYAxisBeginning; y >= kYAxisEnd;
       y = round((y - kStep) * 10) / 10) {
    for (double x = kXAxisBeginning; x <= kXAxisEnd;
         x = round((x + kStep) * 10) / 10) {
      if (abs(sin(x) - y) <= kPrecision) {
        std::cout << '*';
      } else if (x == -1 * kStep and y == kStep) {
        std::cout << '0';
      } else if (x == 0) {
        std::cout << '|';
      } else if (y == 0 and x == kXAxisEnd) {
        std::cout << "-> X";
      } else if (y == 0) {
        std::cout << '-';
      } else if (y == -1 * kStep and x > 0 and x == static_cast<int>(x)) {
        std::cout << x;
      } else if (y == -1 * kStep and x < 0 and
                 (x + kStep) == static_cast<int>((x + kStep))) {
        std::cout << x + kStep;
        x += kStep;
      } else if (x == -1 * kStep and y > 0 and y == static_cast<int>(y)) {
        std::cout << y;
      } else if (x == -2 * kStep and y < 0 and y == static_cast<int>(y)) {
        std::cout << y;
        x += kStep;
      } else {
        std::cout << ' ';
      }
    }
    std::cout << '\n';
  }
}

int RomanToDec(std::string roman_number) {
  // Check for 3 consecutive characters
  char extra_char = ' ';
  int count_of_similar_symbols_in_row = 0;
  for (int i = 0; i < roman_number.size(); i++) {
    if (extra_char != roman_number[i]) {
      extra_char = roman_number[i];
      count_of_similar_symbols_in_row = 1;
    } else {
      count_of_similar_symbols_in_row++;
    }
    if (count_of_similar_symbols_in_row == 4) {
      return kIncorrectUserData;
    }
  }

  const char kCombinationSymbol = '1';
  int dec_number = 0;
  for (int i = 0; i < roman_number.size(); i++) {
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
            return kIncorrectUserData;
          } else {
            dec_number++;
          }
        } else {
          dec_number++;
        }
        break;
      case 'V':
        if (i != roman_number.size() - 1 and roman_number[i + 1] != 'I')
          return kIncorrectUserData;
        else if (i != 0 and roman_number[i - 1] != kCombinationSymbol or i == 0)
          dec_number += 5;
        break;
      case 'X':
        if ((roman_number[i + 1] == 'L' or roman_number[i + 1] == 'C') and
            i != roman_number.size() - 1) {
          if (i != 0 and roman_number[i - 1] == kCombinationSymbol) {
            return kIncorrectUserData;
          } else {
            if (roman_number[i + 1] == 'L')
              dec_number += 40;
            else
              dec_number += 90;
            roman_number[i] = kCombinationSymbol;
          }
        } else if ((i != 0 and roman_number[i - 1] != kCombinationSymbol or
                    i == 0) and
                   ((i != roman_number.size() - 1 and
                     (roman_number[i + 1] == 'X' or
                      roman_number[i + 1] == 'V' or
                      roman_number[i + 1] == 'I')) or
                    i == roman_number.size() - 1)) {
          dec_number += 10;
        } else {
          return kIncorrectUserData;
        }
        break;
      case 'L':
        if (i != roman_number.size() - 1 and roman_number[i + 1] != 'I' and
            roman_number[i + 1] != 'V' and roman_number[i + 1] != 'X')
          return kIncorrectUserData;
        else if (i != 0 and roman_number[i - 1] != kCombinationSymbol or i == 0)
          dec_number += 50;
        break;
      case 'C':
        if ((roman_number[i + 1] == 'D' or roman_number[i + 1] == 'M') and
            i != roman_number.size() - 1) {
          if (i != 0 and roman_number[i - 1] == kCombinationSymbol) {
            return kIncorrectUserData;
          } else {
            if (roman_number[i + 1] == 'D')
              dec_number += 400;
            else
              dec_number += 900;
            roman_number[i] = kCombinationSymbol;
          }
        } else if ((i != 0 and roman_number[i - 1] != kCombinationSymbol or
                    i == 0) and
                   ((i != roman_number.size() - 1 and
                     (roman_number[i + 1] != 'C' and
                      roman_number[i + 1] != 'D' and
                      roman_number[i + 1] != 'M')) or
                    i == roman_number.size() - 1)) {
          dec_number += 100;
        } else {
          return kIncorrectUserData;
        }
        break;
      case 'D':
        if (i != roman_number.size() - 1 and
            (roman_number[i + 1] == 'M' or roman_number[i + 1] != 'D'))
          return kIncorrectUserData;
        else if (i != 0 and roman_number[i - 1] != kCombinationSymbol or i == 0)
          dec_number += 500;
        break;
      case 'M':
        if (i != roman_number.size() - 1 and roman_number[i + 1] == 'M')
          return kIncorrectUserData;
        else if (i != 0 and roman_number[i - 1] != kCombinationSymbol or i == 0)
          dec_number += 1000;
        break;
      default:
        return kIncorrectUserData;
    }
  }
  return dec_number;
}

void Task6() {
  std::cout << "Enter roman number\n";
  std::string roman_number;
  std::cin >> roman_number;
  int answer = RomanToDec(roman_number);
  if (answer != kIncorrectUserData)
    std::cout << "Dec translation of this number is " << answer << '\n';
  else
    std::cout << "It isn't roman number!\n";
}

void Task7() {
  std::cout << "Enter length of consistency (integer required)\n";
  int consistency_length = main_functions::IntegerInput();
  std::vector<int> s;
  s.push_back(0);
  std::cout << "What variant of consistency do u need? (1 or 2 required)\n";
  std::string variant;
  std::cin >> variant;
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
    std::cout << "Incorrect command\n";
    return;
  }
  std::cout << s[0] << ' ';
  for (int i = 1; i < consistency_length; i++) {
    s.push_back((m * s[i - 1] + b) % c);
    std::cout << s[i] << ' ';
  }
  std::cout << '\n';
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
  for (int vendor = 0; vendor < 3; vendor++)
    for (int product = 0; product < 4; product++) {
      C[vendor][0] += A[vendor][product] * (B[product][0] - B[product][1]);
      C[vendor][1] += A[vendor][product] * B[product][1];
      C[vendor][2] += A[vendor][product] * B[product][0];
    }
  std::cout << "Max revenue = " << max(C[0][0], C[1][0], C[2][0]) << " for "
       << GetVendor(C, 0, 1)
       << " vendor\nMin revenue = " << min(C[0][0], C[1][0], C[2][0]) << " for "
       << GetVendor(C, 0, 0)
       << " vendor\nMax commissions = " << max(C[0][1], C[1][1], C[2][1])
       << " for " << GetVendor(C, 1, 1)
       << " vendor\nMin commissions = " << min(C[0][1], C[1][1], C[2][1])
       << " for " << GetVendor(C, 1, 0)
       << " vendor\nTotal revenue = " << C[0][0] + C[1][0] + C[2][0]
       << "\nTotal commissions = " << C[1][1] + C[0][1] + C[2][1]
       << "\nTotal money = " << C[0][2] + C[1][2] + C[2][2] << '\n';
}

std::string ConversionTo10NumberSystem(std::string number, int old_base,
                                  std::map<char, int> SymbolsOfNumbersSystemsToDec) {
  int dec_number = 0, reverse_digit_index = 0;
  for (int i = number.size() - 1; i >= 0; i--) {
    dec_number += SymbolsOfNumbersSystemsToDec[number[i]] *
                  pow(old_base, reverse_digit_index);
    reverse_digit_index++;
  }
  return std::to_string(dec_number);
}

std::string ConversionBetweenNumberSystems(std::string number, int old_base,
                                      int new_base) {
  if (old_base < 2 or new_base < 2) return "It isn't correct number system";
  if (old_base > 36 or new_base > 36)
    return "The program support numbers of systems with base <= 36 only";

  // Fill with values in 10 number system the symbols of number systems with
  // base <= 36 and vice versa
  std::map<char, int> SymbolsOfNumbersSystemsToDec;
  std::map<int, char> SearchDigitsByValue;
  const int kNumberOfCharacters32NumberSystem = 36, kA_ASCII_Index = 65,
            k0_ASCII_Index = 48;
  int key = 0;
  for (int i = k0_ASCII_Index; i <= k0_ASCII_Index + 9; i++) {
    char digit = i;
    SearchDigitsByValue[key] = digit;
    SymbolsOfNumbersSystemsToDec[i] = key++;
  }
  for (int i = kA_ASCII_Index; i <= kA_ASCII_Index + 25; i++) {
    char digit = i;
    SearchDigitsByValue[key] = digit;
    SymbolsOfNumbersSystemsToDec[i] = key++;
  }

  // Check for non-existent number symbols in the given number system
  for (int i = 0; i < number.size(); i++) {
    if (SymbolsOfNumbersSystemsToDec.count(number[i]) == 0 or
        SymbolsOfNumbersSystemsToDec[number[i]] >= old_base)
      return "Incorrect number\n";
  }

  // Convert to 10 number system and to new_base number system
  number = ConversionTo10NumberSystem(number, old_base,
                                      SymbolsOfNumbersSystemsToDec);
  if (new_base == 10) return number;
  std::string conversion_number;
  int dec_number = stoi(number);
  while (dec_number > new_base - 1) {
    conversion_number += SearchDigitsByValue[dec_number % new_base];
    dec_number /= new_base;
  }
  conversion_number += SearchDigitsByValue[dec_number];
  reverse(conversion_number.begin(), conversion_number.end());
  return conversion_number;
}

void Task9() {
  std::cout << "Enter positive integer\n";
  std::string number;
  std::cin >> number;
  std::cout << "Enter two positive integers in separate lines: the original number "
          "system and the new "
          "number system to convert\n";
  int old_base = main_functions::IntegerInput(),
      new_base = main_functions::IntegerInput();
  std::cout << ConversionBetweenNumberSystems(number, old_base, new_base) << '\n';
}
}  // namespace

namespace practice4 {
void Practice4Run() {
  int command = 1;
  while (command != 0) {
    std::cout << "Enter task number separate digit or '0' for exit\n";
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
      std::cout << "Wrong command.\n";
  }
}
}  // namespace practice4