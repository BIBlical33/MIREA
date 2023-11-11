#include <math.h>

#include <fstream>
#include <iostream>
#include <string>
using namespace std;

float formula(float S, float p, float n);
string create_file();
bool CustomIsDidgit(char symbol);

void Task1() {
  cout << "Enter 3 numbers: S, p and n.\n";
  float S, p, n;
  cin >> S >> p >> n;
  cout << "m = " << formula(S, p, n) << endl;
}

float formula(float S, float p, float n) {
  if (p != 0) {
    float r;
    r = p / 100.0;
    float expression = pow(1 + r, n);
    return S * r * expression / (12 * (expression - 1));
  } else
    return S / 12 / n;
}

void Task2() {
  float S, m, n, p = 0, step = 10000.0;
  cout << "Enter 3 nubmers: S, m and n.\n";
  cin >> S >> m >> n;
  while (abs(m - formula(S, p, n)) > 0.0001) {
    if (m > formula(S, p, n))
      p += step;
    else
      p -= step;
    step /= 2.0;
  }
  cout << "p = " << p << endl;
}

string create_file() {
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
  } else
    cout << "Program cannot open this txt file\n";
  return filename + ".txt";
}

void Task3() {
  string file_content;
  ifstream fout(create_file());
  if (fout.is_open()) {
    while (getline(fout, file_content)) cout << file_content << endl;
    fout.close();
  } else
    cout << "Program cannot open this txt file\n";
}

bool CustomIsDidgit(char symbol) {
  const int kNill_ASCII_code = 48;
  if (symbol >= kNill_ASCII_code and symbol <= kNill_ASCII_code + 9)
    return true;
  return false;
}

void Task4() {
  string file_content, digits_line = "";
  ifstream fout(create_file());
  if (fout.is_open()) {
    while (getline(fout, file_content)) {
      for (int i = 0; i < file_content.size(); i++) {
        if (CustomIsDidgit(file_content[i]))
          digits_line += file_content[i];
        else if (i != 0 and CustomIsDidgit(file_content[i - 1]))
          digits_line += ' ';
      }
    }
    fout.close();
    cout << digits_line << endl;
  } else {
    cout << "Program cannot open this txt file\n";
  }
}

void Task5() {
  const __int8 amount_of_letters = 26, A_ASCII_code = 65;
  string letters_line, sorted_line = "";
  cout << "Enter line of letters\n";
  cin >> letters_line;
  for (int i = A_ASCII_code; i < A_ASCII_code + amount_of_letters; i++) {
    char capital_letter = i, small_letter = i + 32;
    for (int j = 0; j < letters_line.size(); j++) {
      if (letters_line[j] == capital_letter) sorted_line += capital_letter;
    }
    for (int j = 0; j < letters_line.size(); j++) {
      if (letters_line[j] == small_letter) sorted_line += small_letter;
    }
  }
  cout << sorted_line << endl;
}

int main() {
  cout << "Greetings. The program was written by Ilya Kramarenko, IVBO-10-23.\
 If you want to run:\ntask1, then enter '1';\ntask2, then enter '2';\
\ntask3, then enter '3';\ntask4, then enter '4';\
\ntask5, then enter '5',\nIf u want to exit, enter '0'.\n";
  int command = 1;
  while (command != 0) {
    cin >> command;
    if (command == 1) Task1();
    if (command == 2) Task2();
    if (command == 3) Task3();
    if (command == 4) Task4();
    if (command == 5) Task5();
    if (command == 0) break;
  }
  return 0;
}