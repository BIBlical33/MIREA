// Copyright 2025, github.com/BIBlical33
//
// Testing Practice4 tasks.
// Task descriptions (in Russian):
// https://drive.google.com/drive/folders/1WK_ulsyjzy_g6WYER9h5GWO-sKLsl-Zm?usp=sharing
//
// License: GNU General Public License v3.0
// See: https://www.gnu.org/licenses/gpl-3.0.html

#include <gtest/gtest.h>

#include "include/practices.h"

using procedural_programming::practice5::EuclideanAlgorithm;

TEST(EuclideanAlgorithmTest, CommonCases) {
  EXPECT_EQ(EuclideanAlgorithm(48, 18), 6);
  EXPECT_EQ(EuclideanAlgorithm(56, 98), 14);
  EXPECT_EQ(EuclideanAlgorithm(100, 25), 25);
  EXPECT_EQ(EuclideanAlgorithm(270, 192), 6);
}

TEST(EuclideanAlgorithmTest, CoprimeNumbers) {
  EXPECT_EQ(EuclideanAlgorithm(17, 31), 1);
  EXPECT_EQ(EuclideanAlgorithm(13, 27), 1);
}

TEST(EuclideanAlgorithmTest, EqualNumbers) {
  EXPECT_EQ(EuclideanAlgorithm(42, 42), 42);
  EXPECT_EQ(EuclideanAlgorithm(1, 1), 1);
}

TEST(EuclideanAlgorithmTest, OneNumberIsZero) {
  EXPECT_EQ(EuclideanAlgorithm(0, 7), 7);
  EXPECT_EQ(EuclideanAlgorithm(25, 0), 25);
}

TEST(EuclideanAlgorithmTest, BothNumbersZero) {
  EXPECT_EQ(EuclideanAlgorithm(0, 0), 0);
}
