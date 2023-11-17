#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <limits>
#include <string>

using namespace std;

double DoubleInput() {
  string str_number;
  cin >> str_number;
  double number;
  try {
    number = stod(str_number);
  } catch (invalid_argument) {
    return INT_MIN;
  } catch (out_of_range) {
    return INT_MIN;
  }
  return number;
}

int IntegerInput() {
  double number = DoubleInput();
  if (number == int(number)) {
    return int(number);
  }
  return INT_MIN;
}

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

int EuclideanAlgorithmByDivision(int first_number, int second_number) {
  if (first_number != 0 and second_number != 0) {
    if (first_number > second_number)
      first_number %= second_number;
    else
      second_number %= first_number;
    return EuclideanAlgorithmByDivision(first_number, second_number);
  } else {
    return first_number + second_number;
  }
}

int EuclideanAlgorithmBySubtraction(int first_number, int second_number) {
  if (first_number != second_number) {
    if (first_number > second_number)
      first_number -= second_number;
    else
      second_number -= first_number;
    return EuclideanAlgorithmByDivision(first_number, second_number);
  } else {
    return first_number;
  }
}

void Task1() {
  cout << "Enter two positive integers\n";
  int first_number, second_number;
  try {
    cin >> first_number >> second_number;
    if (first_number <= 0 or second_number <= 0) {
      cout << "Incorrect data entered\n";
      return;
    }
  } catch (const char* error_message) {
  }
  int greatest_common_divisor =
      EuclideanAlgorithmByDivision(first_number, second_number);
  if (greatest_common_divisor ==
      EuclideanAlgorithmBySubtraction(first_number, second_number))
    cout << "Their reatest common divisor is " << greatest_common_divisor
         << endl;
  else
    cout << "Something went wrong\n";
}

int* EratosthenesSieve(int i, int consistency_integers_size,
                       int* consistency_integers) {
  while (i < consistency_integers_size) {
    if (consistency_integers[i] != 0) {
      int j = i * 2;
      while (j < consistency_integers_size) {
        consistency_integers[j] = 0;
        j += i;
      }
    }
    i++;
  }
  return consistency_integers;
}

void Task2() {
  int consistency_integers_ending;
  cout << "Enter positive integer value:\n";
  cin >> consistency_integers_ending;
  int consistency_integers_size = consistency_integers_ending + 1;
  int* consistency_integers = new int[consistency_integers_size];
  for (int number = 0; number < consistency_integers_size; number++)
    consistency_integers[number] = number;
  consistency_integers[1] = 0;
  EratosthenesSieve(2, consistency_integers_size, consistency_integers);
  for (int number = 1; number < consistency_integers_size; number++)
    if (number == consistency_integers[number]) cout << number << ' ';
  cout << endl;
  delete[] consistency_integers;
}

void Task3() {
  cout << "Enter task number: '9' or '32'\n";
  int task_number = 0;
  cin >> task_number;
  switch (task_number) {
    case 9: {
      ifstream fout(CreateFile());
      if (fout.is_open()) {
        string file_content, number = "";
        while (getline(fout, file_content))
          for (int i = 0; i < file_content.size(); i++)
            cout << (int)file_content[i] << endl;
      } else {
        cout << "Program cannot open this txt file\n";
      }
    } break;
    case 32: {
      ifstream fout(CreateFile());
      cout << "How many characters to shift the information by (enter positive "
              "int for right shift or negative int for left shift)?\n";
      int cipher_shift;
      cin >> cipher_shift;
      if (fout.is_open()) {
        string file_content, number = "";
        while (getline(fout, file_content)) {
          for (int i = 0; i < file_content.size(); i++)
            file_content[i] = (int)file_content[i] + cipher_shift;
          cout << file_content << endl;
        }
      } else {
        cout << "Program cannot open this txt file\n";
      }
    } break;
    default:
      cout << "Incorrect task number\n";
      break;
  }
}

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
      double* a = new double[new_a_size];
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
    double x = DoubleInput(), epsilon = DoubleInput();
    if (x == INT_MIN or epsilon == INT_MIN) {
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
    int N = IntegerInput();
    if (N == INT_MIN) {
      cout << "Incorrect data entered\n";
      return;
    }
    const int kASize = 3 * N + 1;
    int* a = new int[kASize];
    int x = 1, y = 1, z = 1;
    for (int i = 1; i < kASize; i++) {
      a[i] = IntegerInput();
      if (a[i] == INT_MIN) {
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

int* InitializingArray(ifstream& fout, int* array, int starting_index) {
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

// AI automaticly-generated functions
void swap(int* a, int* b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

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

void DrawingTableInFile(ofstream& fout, string** array, const int kRowsCount,
                        const int kColumnsCount) {
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
    swap(arr[i], arr[ending_element - i]);
}

void Task5() {
  cout << "Enter task number: '9' or '23'\n";
  int task_number;
  task_number = IntegerInput();
  switch (task_number) {
    case 9: {
      const int kFileCount = 2;
      ofstream fin("C.txt");
      for (int file_number = 0; file_number < kFileCount; file_number++) {
        ifstream fout(CreateFile());
        if (fout.is_open() and fin.is_open()) {
          const int kArraySize = 1000;
          int* array = new int[kArraySize];
          array[0] = kArraySize;
          InitializingArray(fout, array, 1);
          quickSort(array, 1, array[0] - 1);
          for (int i = 1; i < array[0]; i++) fin << to_string(array[i]) << " ";
          delete[] array;
          fout.close();
        } else {
          cout << "Program cannot open this txt files\n";
          break;
        }
      }
      fin.close();
      ifstream fout("C.txt");
      if (fout.is_open()) {
        string file_content;
        while (getline(fout, file_content)) cout << file_content;
        fout.close();
        fstream clear_file("C.txt", ios::out);
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
      int* olympic_results_by_golden_and_silver_medals = new int[kRowsCount];
      for (int i = 1; i < kRowsCount; i++) {
        olympic_results[i] = new string[kColumnsCount];
        olympic_results[i][0] = to_string(i);
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
          int temp = IntegerInput();
          if (temp < 0 or temp == INT_MIN) {
            cout << "Incorrect data entered\n";
            return;
          }
          if (j == 2 or j == 3) golden_and_silver_medals_count += temp;
          olympic_results[i][j] = to_string(temp);
        }
        olympic_results[i][5] = to_string(stoi(olympic_results[i][2]) +
                                          stoi(olympic_results[i][3]) +
                                          stoi(olympic_results[i][4]));
        olympic_results[i][6] = to_string(stoi(olympic_results[i][2]) * 7 +
                                          stoi(olympic_results[i][3]) * 6 +
                                          stoi(olympic_results[i][4]) * 5);
        olympic_results_by_golden_and_silver_medals[i] =
            golden_and_silver_medals_count;
      }
      fstream clear_file("olympic_games.txt", ios::out);
      clear_file.close();
      ofstream fin("olympic_games.txt");
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
              olympic_results[z][2] = "-1";
              olympic_results[z][3] = "-1";
              break;
            }
          }
        }
        fin.close();
      } else {
        cout << "Program cannot open this txt file\n";
      }
      ifstream fout("olympic_games.txt");
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
      break;
  }
}

int main() {
  cout << "Greetings. The program was written by Ilya Kramarenko, "
          "IVBO-10-23.\n";
  int command = 1;
  while (command != 0) {
    cout << "Enter task number separate digit or '0' for exit\n";
    command = IntegerInput();
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
    else if (command == 0)
      break;
    else
      cout << "Wrong command.\n";
  }
  return 0;
}