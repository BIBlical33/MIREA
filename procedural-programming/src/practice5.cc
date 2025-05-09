﻿// Copyright 2025, github.com/BIBlical33
//
// Solving Practice5 tasks.
// Task descriptions (in Russian):
// https://drive.google.com/drive/folders/1WK_ulsyjzy_g6WYER9h5GWO-sKLsl-Zm?usp=sharing
//
// License: GNU General Public License v3.0
// See: https://www.gnu.org/licenses/gpl-3.0.html

#include <cassert>
#include <cmath>
#include <fstream>
#include <iostream>
#include <limits>
#include <numeric>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include "include/practices.h"
#include "src/create_txt_file.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;

namespace {

int EuclideanAlgorithmByDivision(int first_number, int second_number) {
  if (first_number == 0 or second_number == 0)
    return first_number + second_number;

  if (first_number > second_number)
    first_number %= second_number;
  else
    second_number %= first_number;

  return EuclideanAlgorithmByDivision(first_number, second_number);
}

int EuclideanAlgorithmBySubtraction(int first_number, int second_number) {
  if (first_number == 0 or second_number == 0)
    return first_number + second_number;

  if (first_number == second_number) return first_number;

  if (first_number > second_number)
    first_number -= second_number;
  else
    second_number -= first_number;

  return EuclideanAlgorithmBySubtraction(first_number, second_number);
}

// Task condition: Convert text to a column of ASCII codes
void ProcessingTextFilesSubtask9() {
  std::ifstream fout(procedural_programming::CreateTxtFile("task3"));
  if (not fout.is_open()) {
    std::cerr << "Program cannot open this txt file\n";
    return;
  }

  string file_content, number = "";
  while (getline(fout, file_content))
    for (size_t i = 0; i < file_content.size(); ++i)
      cout << static_cast<int>(file_content[i]) << endl;

  fout.close();
}

// Task condition: Encrypting a text file by shifting alphabetically
void ProcessingTextFilesSubtask32() {
  std::ifstream fout(procedural_programming::CreateTxtFile("task3"));
  int cipher_shift;
  cin >> cipher_shift;
  if (not fout.is_open()) {
    std::cerr << "Program cannot open this txt file\n";
    return;
  }

  string file_content, number = "";
  while (getline(fout, file_content)) {
    for (char character : file_content)
      character = static_cast<char>(static_cast<int>(character) +
                                    cipher_shift % static_cast<int>(character));
    cout << file_content << endl;
  }

  fout.close();
}

}  // namespace

namespace procedural_programming::practice5 {

// Task condition: find the greatest common divisor of two numbers
// by division and subtraction
int EuclideanAlgorithm(int first_number, int second_number) {
  int greatest_common_divisor =
      EuclideanAlgorithmByDivision(first_number, second_number);
  assert(greatest_common_divisor ==
         EuclideanAlgorithmBySubtraction(first_number, second_number));
  assert(greatest_common_divisor == std::gcd(first_number, second_number));
  return greatest_common_divisor;
}

// Task condition: Find all prime numbers in the range from 2 to last_number
std::vector<int> EratosthenesSieve(int last_number) {
  if (last_number < 2) throw std::invalid_argument("Incorrect argument");

  std::vector<int> numbers(last_number - 1);
  std::iota(numbers.begin(), numbers.end(), 2);

  for (size_t i = 0, iend = numbers.size() / 2; i != iend; ++i)
    if (numbers[i] != 0) {
      size_t j = i + numbers[i];
      while (j < numbers.size()) {
        numbers[j] = 0;
        j += numbers[i];
      }
    }

  std::vector<int> prime_dividers;
  for (int& number : numbers)
    if (number != 0) prime_dividers.push_back(number);

  return prime_dividers;
}

enum class ProcessingTextFilesSubtasks {
  kSubtask9 = 9,
  kSubtask32 = 32,
  kWrong
};

void ProcessingTextFiles(ProcessingTextFilesSubtasks subtask_number) {
  switch (subtask_number) {
    case ProcessingTextFilesSubtasks::kSubtask9: {
      ProcessingTextFilesSubtask9();
    } break;
    case ProcessingTextFilesSubtasks::kSubtask32: {
      ProcessingTextFilesSubtask32();
    } break;
    default:
      cout << "Incorrect task number\n";
  }
}

// It's an old code that I have no desire to improve.
#if 0
double* SetAConsistency(double* a, int n, const int kAConsistensySize,
                        double x) {
  if (n < kAConsistensySize) {
    if ((a[n - 3] >= 0 and a[n - 2] * a[n - 2] * sqrt(a[n - 3]) != 0)) {
      a[n] = (12 - a[n - 1] * x) / (a[n - 2] * a[n - 2] * sqrt(a[n - 3]));
      cout << n << ' ' << a[n] << endl;
    } else {
      int new_a_size = n + 1;
      double* temp_array = new double[new_a_size];
      for (int i = 1; i < new_a_size; i++) temp_array[i] = a[i];
      delete[] a;
      a = new double[new_a_size];
      for (int i = 1; i < new_a_size; i++) a[i] = temp_array[i];
      a[0] = new_a_size;
      delete[] temp_array;
      return a;
    }
    return SetAConsistency(a, n + 1, kAConsistensySize, x);
  } else {
    return a;
  }
}

void Task4() {
  cout << "Enter task number: '9' or '60'\n";
  string task_number;
  cin >> task_number;
  if (task_number == "9") {
    cout << "Enter 2 integers: x and epsilon\n";
    double x = main_functions::DoubleInput(),
           epsilon = main_functions::DoubleInput();
    if (x == main_functions::kIncorrectUserData or
        epsilon == main_functions::kIncorrectUserData) {
      cout << "Incorrect data entered\n";
      return;
    }
    const int kAConsistensySize = 1000;
    double* a = new double[kAConsistensySize]{
        kAConsistensySize, 1, x, x * x * x};  // First element is a.size
    a = SetAConsistency(a, 4, kAConsistensySize, x);
    bool flag = 0;
    for (int n = 16; n < a[0]; n++)
      if (abs(a[n] - a[n - 1]) < epsilon) {
        cout << a[n] << endl;
        flag = 1;
        break;
      }
    if (flag == 0) cout << "Consistency doesn't contain this element\n";
    delete[] a;
  } else if (task_number == "60") {
    cout << "Enter N positive integer\n";
    int N = main_functions::IntegerInput();
    if (N < 1) {
      cout << "Incorrect data entered\n";
      return;
    }
    const int kASize = 3 * N + 1;
    int* a = new int[kASize];
    int x = 1, y = 1, z = 1;
    for (int i = 1; i < kASize; i++) {
      a[i] = main_functions::IntegerInput();
      if (a[i] == main_functions::kIncorrectUserData) {
        cout << "Incorrect data entered\n";
        return;
      }
      if (i <= N)
        x *= a[i];
      else if (i <= 2 * N)
        y *= a[i];
      else
        z *= a[i];
    }
    cout << "Q = " << x * x + y * y + z * z << endl;
    delete[] a;
  } else {
    cout << "Incorrect task number\n";
  }
}

int* InitializingArray(std::ifstream& fout, int* array, int starting_index) {
  if (fout.is_open()) {
    int array_index = starting_index;
    string file_content, number = "";
    while (getline(fout, file_content)) {
      for (int i = 0; i < file_content.size(); i++) {
        if (isdigit(file_content[i]) or
            (file_content[i] == '-' and isdigit(file_content[i + 1]) and
             i != file_content.size() - 1) or
            (file_content[i] == '.' and isdigit(file_content[i - 1]) and
             isdigit(file_content[i + 1]) and i != 0 and
             i != file_content.size() - 1)) {
          number += file_content[i];
        } else if (i != 0 and isdigit(file_content[i - 1])) {
          array[array_index++] = stoi(number);
          number = "";
        }
      }
    }
    array[0] = array_index;
    fout.close();
    return array;
  } else {
    cout << "Program cannot open this txt file\n";
    return array;
  }
}

void swap(int* a, int* b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

// AI automaticly-generated functions
int partition(int arr[], int low, int high) {
  int pivot = arr[high];  // выбираем последний элемент в качестве опорного
  int i = (low - 1);      // индекс меньшего элемента

  for (int j = low; j <= high - 1; j++) {
    // Если текущий элемент меньше или равен опорному
    if (arr[j] <= pivot) {
      i++;  // увеличиваем индекс меньшего элемента
      swap(&arr[i], &arr[j]);
    }
  }
  swap(&arr[i + 1], &arr[high]);
  return (i + 1);
}

void quickSort(int arr[], int low, int high) {
  if (low < high) {
    // Получаем индекс опорного элемента после разделения массива
    int pi = partition(arr, low, high);

    // Рекурсивно сортируем элементы до опорного и после него
    quickSort(arr, low, pi - 1);
    quickSort(arr, pi + 1, high);
  }
}
// Ending AI auto-generated functions

void DrawingTableInFile(std::ofstream& fout, string** array,
                        const int kRowsCount, const int kColumnsCount) {
  if (fout.is_open()) {
    string horizontal_line(83, '-');
    horizontal_line = "|" + horizontal_line + "|";
    fout << horizontal_line << "\r\n";
    fout << "|           |Country    |Golden     |Silver     |Bronze     "
            "|Total      |Score      |"
         << "\r\n";
    fout << horizontal_line << "\r\n";
    for (int i = 1; i < kRowsCount; i++) {
      fout << '|';
      for (int j = 0; j < kColumnsCount; j++) {
        fout << array[i][j];
        for (int k = 0; k < 11 - array[i][j].size(); k++) fout << ' ';
        fout << '|';
      }
      fout << "\r\n" << horizontal_line << "\r\n";
    }
  } else {
    cout << "Program cannot open this txt file\n";
  }
}

void ReverseArray(int arr[], int starting_element, int ending_element) {
  for (int i = starting_element; i < ending_element % 2; i++)
    std::swap(arr[i], arr[ending_element - i]);
}

void Task5() {
  cout << "Enter task number: '9' or '23'\n";
  int task_number;
  task_number = main_functions::IntegerInput();
  switch (task_number) {
    case 9: {
      const int kFilesCount = 2;
      std::ofstream fin("C.txt");
      for (int file_number = 0; file_number < kFilesCount; file_number++) {
        std::ifstream fout(main_functions::CreateTxtFile("task5"));
        if (fout.is_open() and fin.is_open()) {
          const int kArraySize = 1000;
          int* array = new int[kArraySize];
          array[0] = kArraySize;
          InitializingArray(fout, array, 1);
          quickSort(array, 1, array[0] - 1);
          for (int i = 1; i < array[0]; i++)
            fin << std::to_string(array[i]) << " ";
          delete[] array;
          fout.close();
          cout << endl;
        } else {
          cout << "Program cannot open this txt files\n";
          break;
        }
      }
      fin.close();
      std::ifstream fout("C.txt");
      if (fout.is_open()) {
        string file_content;
        while (getline(fout, file_content)) cout << file_content;
        fout.close();
        std::fstream clear_file("C.txt", std::ios::out);
        clear_file.close();
      } else {
        cout << "Program cannot open this txt file\n";
      }
    } break;
    case 23: {
      string** olympic_results;
      const int kRowsCount = 11;  // First row'll be skiped
      const int kColumnsCount = 7;
      olympic_results = new string*[kRowsCount];
      olympic_results[0] = 0;
      int* olympic_results_by_golden_and_silver_medals = new int[kRowsCount];
      for (int i = 1; i < kRowsCount; i++) {
        olympic_results[i] = new string[kColumnsCount];
        olympic_results[i][0] = std::to_string(i);
        switch (i) {
          case 1:
            olympic_results[i][1] = "German";
            break;
          case 2:
            olympic_results[i][1] = "Norwaynian";
            break;
          case 3:
            olympic_results[i][1] = "Russian";
            break;
          case 4:
            olympic_results[i][1] = "Austritch";
            break;
          case 5:
            olympic_results[i][1] = "Canadian";
            break;
          case 6:
            olympic_results[i][1] = "American";
            break;
          case 7:
            olympic_results[i][1] = "Finnish";
            break;
          case 8:
            olympic_results[i][1] = "Japan";
            break;
          case 9:
            olympic_results[i][1] = "China";
            break;
          case 10:
            olympic_results[i][1] = "Coreean";
            break;
        }
      }
      for (int i = 1; i < kRowsCount; i++) {
        cout << "Enter " << olympic_results[i][1]
             << " amount of golden medals, silver medals, bronze medals (3 "
                "integers "
                "required)\n";
        int golden_and_silver_medals_count = 0;
        for (int j = 2; j < kColumnsCount - 2; j++) {
          int temp = main_functions::IntegerInput();
          if (temp < 0) {
            cout << "Incorrect data entered\n";
            return;
          }
          if (j == 2 or j == 3) golden_and_silver_medals_count += temp;
          olympic_results[i][j] = std::to_string(temp);
        }
        olympic_results[i][5] = std::to_string(stoi(olympic_results[i][2]) +
                                               stoi(olympic_results[i][3]) +
                                               stoi(olympic_results[i][4]));
        olympic_results[i][6] = std::to_string(stoi(olympic_results[i][2]) * 7 +
                                               stoi(olympic_results[i][3]) * 6 +
                                               stoi(olympic_results[i][4]) * 5);
        olympic_results_by_golden_and_silver_medals[i] =
            golden_and_silver_medals_count;
      }
      std::fstream clear_file("olympic_games.txt", std::ios::out);
      clear_file.close();
      std::ofstream fin("olympic_games.txt");
      DrawingTableInFile(fin, olympic_results, kRowsCount, kColumnsCount);
      fin.close();
      clear_file.open("olympic_games.txt");
      clear_file.close();
      quickSort(olympic_results_by_golden_and_silver_medals, 1, kRowsCount - 1);
      ReverseArray(olympic_results_by_golden_and_silver_medals, 1,
                   kRowsCount - 1);
      fin.open("olympic_games.txt");
      if (fin.is_open()) {
        string horizontal_line(83, '-');
        horizontal_line = "|" + horizontal_line + "|";
        fin << horizontal_line << "\r\n"
            << "|           |Country    |Golden     |Silver     |Bronze     "
               "|Total      |Score      |"
            << "\r\n"
            << horizontal_line << "\r\n";
        for (int i = 1; i < kRowsCount; i++) {
          fin << '|';
          for (int z = 1; z < kRowsCount; z++) {
            if (olympic_results_by_golden_and_silver_medals[i] ==
                stoi(olympic_results[z][2]) + stoi(olympic_results[z][3])) {
              for (int j = 0; j < kColumnsCount; j++) {
                fin << olympic_results[z][j];
                for (int k = 0; k < 11 - olympic_results[z][j].size(); k++)
                  fin << ' ';
                fin << '|';
              }
              fin << "\r\n" << horizontal_line << "\r\n";
              break;
            }
          }
        }
        fin.close();
      } else {
        cout << "Program cannot open this txt file\n";
      }
      std::ifstream fout("olympic_games.txt");
      string file_content;
      if (fout.is_open()) {
        while (getline(fout, file_content)) cout << file_content << endl;
        fout.close();
      } else {
        cout << "Program cannot open this txt file\n";
      }
      delete[] olympic_results_by_golden_and_silver_medals;
      for (int i = 0; i < kRowsCount; i++) delete[] olympic_results[i];
      delete[] olympic_results;
    } break;
    default:
      cout << "Incorrect task number\n";
  }
}
#endif

}  // namespace procedural_programming::practice5
