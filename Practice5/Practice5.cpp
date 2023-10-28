#define _USE_MATH_DEFINES
#include <Windows.h>

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

string CreateFile();
bool CustomIsDidgit(char symbol);
int sign(double x);
void TriangleAreaCalculation();
void RectangleAreaCalculation();
void CircleAreaCalculation();
string ConversionBetweenNumberSystems(string number, int old_base,
                                      int new_base);
string ConversionTo10NumberSystem(string number, int old_base,
                                  map<char, int> SymbolsOfNumbersSystemsToDec);

string CreateFile() {
  cout << "What do you want to name the text file?\n";
  string filename, file_content;
  cin >> filename;
  ofstream file(filename + ".txt");
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

void Task1() {
  ifstream fout(CreateFile());
  if (fout.is_open()) {
    vector<double> numbers;
    string file_content, number = "";
    while (getline(fout, file_content)) {
      // Разбиваем строку на числа и записываем их в вектор
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
    double sum = 0;
    for (int i = 0; i < numbers.size(); i++) sum += numbers[i];

    cout << sum << endl;
    fout.close();
  } else {
    cout << "Program cannot open this txt file\n";
  }
}

bool CustomIsDidgit(char symbol) {
  const int kNill_ASCII_code = 48;
  if (symbol >= kNill_ASCII_code and symbol <= kNill_ASCII_code + 9)
    return true;
  return false;
}

int sign(double x) {
  if (x > 0) return 1;
  if (x == 0) return 0;
  return -1;
}

void Task2() {
  double number;
  cout << "Enter x" << endl;
  cin >> number;
  cout << sign(number) << endl;
}

void Task3() {
  cout << "What type of figure do u need? For:\nrectangle, enter "
          "'1'\ntriangle, enter '2'\ncircle, enter '3'\n";
  int figure_type;
  cin >> figure_type;
  switch (figure_type) {
    case 1:
      RectangleAreaCalculation();
      break;
    case 2:
      TriangleAreaCalculation();
      break;
    case 3:
      CircleAreaCalculation();
      break;
    default:
      cout << "Worng type\n";
      break;
  }
}

void RectangleAreaCalculation() {
  cout << "Enter length and width of rectangle\n";
  double rectangle_width, rectangle_length;
  cin >> rectangle_length >> rectangle_width;
  if (rectangle_length > 0 and rectangle_width > 0)
    cout << "S = " << rectangle_length * rectangle_width << endl;
  else
    cout << "It isn't rectangle\n";
}

void TriangleAreaCalculation() {
  cout << "Enter three sides of triangle\n";
  double triangle_first_side, triangle_second_side, triangle_third_side;
  cin >> triangle_first_side >> triangle_second_side >> triangle_third_side;
  double p =
      (triangle_first_side + triangle_second_side + triangle_third_side) / 2.0;
  if (triangle_first_side > 0 and triangle_second_side > 0 and
      triangle_third_side > 0 and
      triangle_first_side + triangle_second_side > triangle_third_side and
      triangle_second_side + triangle_third_side > triangle_first_side and
      triangle_first_side + triangle_third_side > triangle_second_side)
    cout << "S = "
         << sqrt(p * (p - triangle_first_side) * (p - triangle_second_side) *
                 (p - triangle_third_side))
         << endl;
  else
    cout << "It isn't a triangle\n";
}

void CircleAreaCalculation() {
  cout << "Enter radius of circle\n";
  double r;
  cin >> r;
  if (r > 0)
    cout << "S = " << M_PI * r * r << endl;
  else
    cout << "It isn't a circle\n";
}

void Task4() {
  HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(handle, FOREGROUND_RED);
  cout << "               __________________________\n";
  for (int i = 0; i < 12; i++) {
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
  cout << "y = sin(x)\n\n";
  // Отлажено только для |x|<10 и |y|<10
  const double kYAxisBeginning = 1.2, kYAxisEnd = -1.2, kXAxisBeginning = -6.0,
               kXAxisEnd = 9.0, kStep = 0.1, kPrecision = 0.05;
  string auxiliary_line(abs(kXAxisBeginning / kStep) - 2.0, ' ');
  cout << auxiliary_line << "Y ^\n";
  for (double y = kYAxisBeginning; y >= kYAxisEnd;
       y = round((y - kStep) * 10) / 10) {
    for (double x = kXAxisBeginning; x <= kXAxisEnd;
         x = round((x + kStep) * 10) / 10) {
      if (abs(sin(x) - y) <= kPrecision) {
        cout << '*';
      } else if (x == -1 * kStep and y == kStep) {
        cout << '0';
      } else if (x == 0) {
        cout << '|';
      } else if (y == 0 and x == kXAxisEnd) {
        cout << "-> X";
      } else if (y == 0) {
        cout << '-';
      } else if (y == -1 * kStep and x > 0 and x == (int)x) {
        cout << x;
      } else if (y == -1 * kStep and x < 0 and
                 (x + kStep) == (int)(x + kStep)) {
        cout << x + kStep;
        x += kStep;
      } else if (x == -1 * kStep and y > 0 and y == (int)y) {
        cout << y;
      } else if (x == -2 * kStep and y < 0 and y == (int)y) {
        cout << y;
        x += kStep;
      } else {
        cout << ' ';
      }
    }
    cout << endl;
  }
}

void Task6() {
  cout << "Enter roman number\n";
  string roman_number;
  cin >> roman_number;
  // Проверяем на существование символов и их количество
  char extra_char = ' ';
  int count_of_similar_symbols_in_row = 0;
  for (int i = 0; i < roman_number.size(); i++) {
    if (extra_char != roman_number[i]) {
      extra_char = roman_number[i];
      count_of_similar_symbols_in_row = 1;
    } else {
      count_of_similar_symbols_in_row++;
    }
    if (roman_number[i] != 'I' and roman_number[i] != 'V' and
            roman_number[i] != 'X' and roman_number[i] != 'C' and
            roman_number[i] != 'D' and roman_number[i] != 'M' and
            roman_number[i] != 'M' or
        count_of_similar_symbols_in_row == 4) {
      cout << "It isn't roman number!\n";
      return;
    }
  }
  int dec_number = 0;
  for (int i = 0; i < roman_number.size(); i++) {
    switch (roman_number[i]) {
      case 'I':
        if (i != roman_number.size() - 1) {
          if (roman_number[i + 1] == 'V') {
            dec_number += 4;
            i++;
          } else if (roman_number[i + 1] == 'X') {
            dec_number += 9;
            i++;
          } else if (roman_number[i + 1] != 'I') {
            cout << "It isn't roman number\n";
            return;
          } else {
            dec_number++;
          }
        } else {
          dec_number++;
        }
        break;
      case 'V':
        if (i != roman_number.size() - 1 and roman_number[i + 1] != 'I') {
          cout << "It isn't roman number\n";
          return;
        } else {
          dec_number += 5;
        }
        break;
      case 'X':
        if (i != roman_number.size() - 1) {
          if (roman_number[i + 1] == 'L') {
            dec_number += 40;
            i++;
          } else if (roman_number[i + 1] == 'XC') {
            dec_number += 90;
            i++;
          } else if (roman_number[i + 1] != 'X' and
                     roman_number[i + 1] != 'V' and
                     roman_number[i + 1] != 'I') {
            cout << "It isn't roman number\n";
            return;
          } else {
            dec_number += 10;
          }
        } else {
          dec_number += 10;
        }
        break;
      case 'L':
        if (i != roman_number.size() - 1 and roman_number[i + 1] != 'X' and
            roman_number[i + 1] != 'V' and roman_number[i + 1] != 'I') {
          cout << "It isn't roman number\n";
          return;
        } else {
          dec_number += 50;
        }
        break;
      case 'C':
        if (i != roman_number.size() - 1) {
          if (roman_number[i + 1] == 'D') {
            dec_number += 400;
            i++;
          } else if (roman_number[i + 1] == 'XC') {
            dec_number += 900;
            i++;
          } else if (roman_number[i + 1] != 'L' and
                     roman_number[i + 1] != 'X' and
                     roman_number[i + 1] != 'V' and
                     roman_number[i + 1] != 'I' and
                     roman_number[i + 1] != 'C') {
            cout << "It isn't roman number\n";
            return;
          } else {
            dec_number += 100;
          }
        } else {
          dec_number += 100;
        }
        break;
      case 'D':
        if (i != roman_number.size() - 1 and
            (roman_number[i + 1] == 'D' or roman_number[i + 1] == 'M')) {
          cout << "It isn't roman number\n";
          return;
        } else {
          dec_number += 500;
        }
        break;
      case 'M':
        if (i != roman_number.size() - 1 and roman_number[i + 1] != 'M') {
          cout << "It isn't roman number\n";
          return;
        } else {
          dec_number += 1000;
        }
        break;
    }
  }
  cout << "Decimal notation of ur number is " << dec_number << endl;
}

void Task7() {
  cout << "Enter length of consistency (integer required)\n";
  int consistency_length;
  cin >> consistency_length;
  vector<int> s;
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
  for (int i = 1; i < consistency_length; i++) {
    s.push_back((m * s[i - 1] + b) % c);
    cout << s[i] << ' ';
  }
  cout << endl;
}

int GetVendor(double C[3][3], int row, bool option) {
  if (option == true) {
    if (C[0][row] >= C[1][row] and C[0][row] >= C[2][row]) return 1;
    if (C[1][row] >= C[2][row]) return 2;
    return 3;
  }
  if (option == false) {
    if (C[0][row] <= C[1][row] and C[0][row] <= C[2][row]) return 1;
    if (C[1][row] <= C[2][row]) return 2;
    return 3;
  }
}

void Task8() {
  const double A[3][4] = {{5, 2, 0, 10}, {3, 5, 2, 5}, {20, 0, 0, 0}};
  map<int, vector<double>> B;
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
  cout << "Max revenue = " << max(C[0][0], C[1][0], C[2][0]) << " for "
       << GetVendor(C, 0, 1)
       << " vendor\nMin revenue = " << min(C[0][0], C[1][0], C[2][0]) << " for "
       << GetVendor(C, 0, 0)
       << " vendor\nMax commissions = " << max(C[0][1], C[1][1], C[2][1])
       << " for " << GetVendor(C, 1, 1)
       << " vendor\nMin commissions = " << min(C[0][1], C[1][1], C[2][1])
       << " for " << GetVendor(C, 1, 0)
       << " vendor\nTotal revenue = " << C[0][0] + C[1][0] + C[2][0]
       << "\nTotal commissions = " << C[1][1] + C[0][1] + C[2][1]
       << "\nTotal money = " << C[0][2] + C[1][2] + C[2][2] << endl;
}

string ConversionTo10NumberSystem(string number, int old_base,
                                  map<char, int> SymbolsOfNumbersSystemsToDec) {
  int dec_number = 0, reverse_digit_index = 0;
  for (int i = number.size() - 1; i >= 0; i--) {
    dec_number += SymbolsOfNumbersSystemsToDec[number[i]] *
                  pow(old_base, reverse_digit_index);
    reverse_digit_index++;
  }
  return to_string(dec_number);
}

string ConversionBetweenNumberSystems(string number, int old_base,
                                      int new_base) {
  if (old_base < 2 or new_base < 2) return "It isn't correct number system";
  if (old_base > 36 or new_base > 36)
    return "The program support numbers of systems with base <= 36 only";
  map<char, int> SymbolsOfNumbersSystemsToDec;
  map<int, char> SearchDigitsByValue;
  // Заполняем значениями в 10сс символы систем счисления с основанием <= 36 и
  // наоборот
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
  // Проверяем наличие несуществующих символов числа в заданной сс
  char symbol;
  for (int i = 0; i < number.size(); i++) {
    if (SymbolsOfNumbersSystemsToDec.count(number[i]) == 0 or
        SymbolsOfNumbersSystemsToDec[i] >= new_base)
      return "Incorrect number\n";
  }
  if (new_base == old_base or number == "0" or number == "1") return number;
  if (new_base == 10)
    return ConversionTo10NumberSystem(number, old_base,
                                      SymbolsOfNumbersSystemsToDec);
  // Переводим из 10 сс в new_base сс
  number = ConversionTo10NumberSystem(number, old_base,
                                      SymbolsOfNumbersSystemsToDec);
  string conversion_number;
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
  cout << "Enter positive integer\n";
  string number;
  cin >> number;
  cout << "Enter two positive integers: the original number system and the "
          "new "
          "number "
          "system to convert\n";
  int new_base, old_base;
  cin >> old_base >> new_base;
  cout << ConversionBetweenNumberSystems(number, old_base, new_base) << endl;
}

int main() {
  cout << "Greetings. The program was written by Ilya Kramarenko, "
          "IVBO-10-23. Enter task number separate digit\n";
  int command = 1;
  while (command != 0) {
    cin >> command;
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
  return 0;
}