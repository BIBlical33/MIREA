// Copyright 2025, github.com/BIBlical33
//
// Solving Practice6 tasks.
// Task descriptions (in Russian):
// https://drive.google.com/drive/folders/1WK_ulsyjzy_g6WYER9h5GWO-sKLsl-Zm?usp=sharing
//
// License: GNU General Public License v3.0
// See: https://www.gnu.org/licenses/gpl-3.0.html

// It's an old code that I have no desire to improve.
#if 0

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <limits>
#include <string>

#include "include/practices.h"

namespace {

using std::cin;
using std::cout;
using std::endl;
using std::string;

void Task60(int n) {
  if (n < 1)
    throw std::invalid_argument("Incorrect matrix size: " + std::to_string(n));

  int **square_matrix = new int *[n], side_diagonal_j = n - 1,
      desired_min_element = std::numeric_limits<int>::max();

  for (int i = 0; i < n; i++) {
    cout << "Enter " << n << " numbers\n";

    square_matrix[i] = new int[n];

    for (int j = 0; j < n; j++) {
      square_matrix[i][j] = main_functions::IntegerInput();

      if (square_matrix[i][j] == main_functions::kIncorrectUserData) {
        cout << "Incorrect data entered\n";

        for (int z = 0; z <= i; z++) delete[] square_matrix[z];
        delete[] square_matrix;
        return;
      }

      if (j >= side_diagonal_j - 1 and j <= side_diagonal_j + 1 and
          square_matrix[i][j] < desired_min_element)
        desired_min_element = square_matrix[i][j];
    }
    side_diagonal_j--;
  }

  cout << desired_min_element << endl;

  for (int i = 0; i < n; i++) delete[] square_matrix[i];
  delete[] square_matrix;
}

int LCM(int first_number, int second_number) {
  if (first_number != 0 and second_number != 0) {
    if (first_number > second_number)
      first_number %= second_number;
    else
      second_number %= first_number;
    return LCM(first_number, second_number);
  } else {
    return 0;
  }
}

void Task74() {
  cout << "Enter 4 positive integers: A, B, C, D\n";

  int A = main_functions::IntegerInput(), B = main_functions::IntegerInput(),
      C = main_functions::IntegerInput(), D = main_functions::IntegerInput();

  if (A < 0 or B < 0 or C < 0 or D < 0) {
    cout << "Incorrect data entered\n";
    return;
  }

  cout << "LCM(A,B) = " << LCM(A, B) << endl
       << "LCM(A,C) = " << LCM(A, C) << endl
       << "LCM(A,D) = " << LCM(A, D) << endl;
}

void Task82() {
  cout << "Enter 2 positive integers\n";

  int fist_number = main_functions::IntegerInput(),
      second_number = main_functions::IntegerInput();

  if (fist_number < 1 or second_number < 1) {
    cout << "Incorrect data entered\n";
    return;
  }

  cout << "Their LCM = " << LCM(fist_number, second_number) << endl;
}

// AI generated function
int* findLCS(const int* x, int m, const int* y, int n, int& lcsLength) {
  int** dp = new int*[m + 1];
  for (int i = 0; i <= m; ++i) {
    dp[i] = new int[n + 1];
  }
  for (int i = 0; i <= m; ++i) {
    for (int j = 0; j <= n; ++j) {
      if (i == 0 || j == 0) {
        dp[i][j] = 0;
      }
    }
  }
  for (int i = 1; i <= m; ++i) {
    for (int j = 1; j <= n; ++j) {
      if (x[i - 1] == y[j - 1]) {
        dp[i][j] = dp[i - 1][j - 1] + 1;
      } else {
        dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
      }
    }
  }
  lcsLength = dp[m][n];
  int* lcs = new int[lcsLength];
  int i = m, j = n, index = lcsLength - 1;

  while (i > 0 && j > 0) {
    if (x[i - 1] == y[j - 1]) {
      lcs[index] = x[i - 1];
      i--;
      j--;
      index--;
    } else if (dp[i - 1][j] > dp[i][j - 1]) {
      i--;
    } else {
      j--;
    }
  }

  for (i = 0; i <= m; ++i) {
    delete[] dp[i];
  }

  delete[] dp;
  return lcs;
}

void Task85() {
  cout << "Enter 2 positive integers: n and m\n";

  int n = main_functions::IntegerInput(), m = main_functions::IntegerInput();

  if (n < 1 or m < 1) {
    cout << "Incorrect data entered\n";
    return;
  }

  int* x = new int[n];

  cout << "Enter " << n << " numbers\n";

  for (int i = 0; i < n; i++) {
    x[i] = main_functions::IntegerInput();

    if (x[i] == main_functions::kIncorrectUserData) {
      delete[] x;
      cout << "Incorrect data entered\n";
      return;
    }
  }

  int* y = new int[m];

  cout << "Enter " << m << " numbers\n";

  for (int i = 0; i < m; i++) {
    y[i] = main_functions::IntegerInput();

    if (y[i] == main_functions::kIncorrectUserData) {
      cout << "Incorrect data entered\n";
      delete[] x, delete[] y;
      return;
    }
  }

  int lcs_length = 0, *lcs = findLCS(x, m, y, n, lcs_length);

  if (lcs_length == 0) {
    cout << "This sequences don't have any subsequences\n";
  } else {
    cout << "Largest common subsequence: ";

    for (int i = 0; i < lcs_length; ++i) {
      cout << lcs[i] << " ";
    }
    cout << endl;
  }
  delete[] lcs, delete[] x;
  delete[] y;
}

void Task89() {
  cout << "Enter 2 positive integers: n and m\n";

  int n = main_functions::IntegerInput(), m = main_functions::IntegerInput();

  if (n < 1 or m < 1) {
    cout << "Incorrect data entered\n";
    return;
  }

  int* a = new int[n + 1];

  a[0] = 0;

  cout << "Enter " << n << " numbers\n";

  for (int i = 1; i <= n; i++) {
    a[i] = main_functions::IntegerInput();

    if (a[i] < 1) {
      cout << "Incorrect data entered\n";
      delete[] a;
      return;
    }
  }

  for (int i = 1; i <= n; i++) {
    if (a[i] > m) a[i] = 0;
    if (a[i] == m) {
      cout << a[i] << endl;
      return;
    }
  }

  for (int i = 1; i <= n; i++) {
    if (a[i] != 0) {
      int sum = 0;

      for (int j = i; j <= n and sum > m; j++) {
        if (a[j] == 0) break;

        sum += a[j];

        if (sum == m) {
          for (int z = i; z <= j; z++) cout << a[z] << ' ';
          cout << endl;

          delete[] a;
          return;
        }
      }
    }
  }

  delete[] a;
  cout << "This sequence doesn't have a desired sequence\n";
}
}  // namespace

}  // namespace procedural_programming

#endif
