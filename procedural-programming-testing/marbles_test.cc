// Copyright 2025, github.com/BIBlical33
//
// Testing Marbles tasks.
// Task descriptions (in Russian):
// https://drive.google.com/drive/folders/1WK_ulsyjzy_g6WYER9h5GWO-sKLsl-Zm?usp=sharing
//
// License: GNU General Public License v3.0
// See: https://www.gnu.org/licenses/gpl-3.0.html

#include <stdexcept>

#include "gtest/gtest.h"
#include "include/practices.h"

namespace {

using procedural_programming::Marbles;

TEST(MarblesTest, HandlesCorrectInput) {
  EXPECT_EQ(Marbles(0), 0);
  EXPECT_EQ(Marbles(1), 1);
  EXPECT_EQ(Marbles(2), 1);
  EXPECT_EQ(Marbles(3), 4);
  EXPECT_EQ(Marbles(4), 15);
  EXPECT_EQ(Marbles(5), 76);
  EXPECT_EQ(Marbles(6), 455);
  EXPECT_EQ(Marbles(7), 3186);
  EXPECT_EQ(Marbles(8), 25487);
  EXPECT_EQ(Marbles(9), 229384);
}

TEST(MarblesTest, HandlesIncorrectInput) {
  EXPECT_THROW(Marbles(-1), std::invalid_argument);
  EXPECT_THROW(Marbles(-1000), std::invalid_argument);
  EXPECT_THROW(Marbles(20), std::invalid_argument);
  EXPECT_THROW(Marbles(1000), std::invalid_argument);
}

}  // namespace
