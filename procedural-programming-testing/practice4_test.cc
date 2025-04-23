// Copyright 2025, github.com/BIBlical33
//
// Testing Practice4 tasks.
// Task descriptions (in Russian):
// https://drive.google.com/drive/folders/1WK_ulsyjzy_g6WYER9h5GWO-sKLsl-Zm?usp=sharing
//
// License: GNU General Public License v3.0
// See: https://www.gnu.org/licenses/gpl-3.0.html

#include <iostream>
#include <stdexcept>
#include <vector>

#include "gtest/gtest.h"
#include "include/practices.h"

namespace {

using procedural_programming::practice4::AutomaticRecognizer;
using procedural_programming::practice4::CircleParams;
using procedural_programming::practice4::ConsistencyVariant;
using procedural_programming::practice4::FigureType;
using procedural_programming::practice4::NumberSystems;
using procedural_programming::practice4::PseudorandomNumberGenerator;
using procedural_programming::practice4::RectangleParams;
using procedural_programming::practice4::Sign;
using procedural_programming::practice4::TriangleParams;

using FigureParams =
    std::variant<TriangleParams, RectangleParams, CircleParams>;

TEST(SignTest, PositiveNumbers) {
  EXPECT_EQ(Sign(1.0), 1);
  EXPECT_EQ(Sign(1.5), 1);
  EXPECT_EQ(Sign(1000000.0), 1);
  EXPECT_EQ(Sign(0.0001), 1);
  EXPECT_EQ(Sign(1e300), 1);
}

TEST(SignTest, ZeroAndNegativeZero) {
  EXPECT_EQ(Sign(0.0), 0);
  EXPECT_EQ(Sign(-0.0), 0);
}

TEST(SignTest, NegativeNumbers) {
  EXPECT_EQ(Sign(-1.0), -1);
  EXPECT_EQ(Sign(-1.5), -1);
  EXPECT_EQ(Sign(-1000000.0), -1);
  EXPECT_EQ(Sign(-0.0001), -1);
  EXPECT_EQ(Sign(-1e300), -1);
}

TEST(SignTest, SmallestNumbers) {
  EXPECT_EQ(Sign(1e-300), 1);
  EXPECT_EQ(Sign(-1e-300), -1);
}

TEST(SignTest, RandomValues) {
  EXPECT_EQ(Sign(42.0), 1);
  EXPECT_EQ(Sign(-42.0), -1);
  EXPECT_EQ(Sign(0.000001), 1);
  EXPECT_EQ(Sign(-0.000001), -1);
}

TEST(GeometricFiguresTest, CircleAreaCalculationTest) {
  double tolerance = 0.0001;
  ASSERT_NEAR(
      78.5398,
      GeometricFigures(FigureType::kCircle, FigureParams(CircleParams(5.0))),
      tolerance);
  EXPECT_THROW(
      GeometricFigures(FigureType::kCircle, FigureParams(CircleParams(-100))),
      std::invalid_argument);
}

TEST(GeometricFiguresTest, RectangleAreaCalculationTest) {
  double tolerance = 0.0001;
  ASSERT_NEAR(20.0,
              GeometricFigures(FigureType::kRectangle,
                               FigureParams(RectangleParams(4.0, 5.0))),
              tolerance);
  EXPECT_THROW(GeometricFigures(FigureType::kRectangle,
                                FigureParams(RectangleParams(0.0, 5.0))),
               std::invalid_argument);
  EXPECT_THROW(GeometricFigures(FigureType::kRectangle,
                                FigureParams(RectangleParams(4.0, 0.0))),
               std::invalid_argument);
}

TEST(GeometricFiguresTest, TriangleAreaCalculationTest) {
  double tolerance = 0.0001;
  ASSERT_NEAR(6.0,
              GeometricFigures(FigureType::kTriangle,
                               FigureParams(TriangleParams(3.0, 4.0, 5.0))),
              tolerance);
}

TEST(GeometricFiguresTest, TriangleWithZeroSideThrows) {
  EXPECT_THROW(GeometricFigures(FigureType::kTriangle,
                                FigureParams(TriangleParams(0.0, 4.0, 5.0))),
               std::invalid_argument);

  EXPECT_THROW(GeometricFigures(FigureType::kTriangle,
                                FigureParams(TriangleParams(3.0, 0.0, 5.0))),
               std::invalid_argument);

  EXPECT_THROW(GeometricFigures(FigureType::kTriangle,
                                FigureParams(TriangleParams(3.0, 4.0, 0.0))),
               std::invalid_argument);
}

TEST(GeometricFiguresTest, TriangleWithNegativeSideThrows) {
  EXPECT_THROW(GeometricFigures(FigureType::kTriangle,
                                FigureParams(TriangleParams(-3.0, 4.0, 5.0))),
               std::invalid_argument);

  EXPECT_THROW(GeometricFigures(FigureType::kTriangle,
                                FigureParams(TriangleParams(3.0, -4.0, 5.0))),
               std::invalid_argument);

  EXPECT_THROW(GeometricFigures(FigureType::kTriangle,
                                FigureParams(TriangleParams(3.0, 4.0, -5.0))),
               std::invalid_argument);
}

TEST(GeometricFiguresTest, TriangleWithInvalidInequalityThrows) {
  EXPECT_THROW(GeometricFigures(FigureType::kTriangle,
                                FigureParams(TriangleParams(1.0, 2.0, 3.5))),
               std::invalid_argument);

  EXPECT_THROW(GeometricFigures(FigureType::kTriangle,
                                FigureParams(TriangleParams(10.0, 2.0, 3.0))),
               std::invalid_argument);
}

TEST(GeometricFiguresTest, WrongFigureType) {
  EXPECT_THROW(GeometricFigures(static_cast<FigureType>(0),
                                FigureParams(TriangleParams(3.0, 4.0, 5.0))),
               std::bad_variant_access);
  EXPECT_THROW(GeometricFigures(static_cast<FigureType>(99),
                                FigureParams(TriangleParams(3.0, 4.0, 5.0))),
               std::invalid_argument);
}

TEST(AutomaticRecognizerTest, ValidRomanNumerals) {
  EXPECT_EQ(AutomaticRecognizer("XI"), 11);
  EXPECT_EQ(AutomaticRecognizer("I"), 1);
  EXPECT_EQ(AutomaticRecognizer("II"), 2);
  EXPECT_EQ(AutomaticRecognizer("III"), 3);
  EXPECT_EQ(AutomaticRecognizer("IV"), 4);
  EXPECT_EQ(AutomaticRecognizer("V"), 5);
  EXPECT_EQ(AutomaticRecognizer("VI"), 6);
  EXPECT_EQ(AutomaticRecognizer("VII"), 7);
  EXPECT_EQ(AutomaticRecognizer("VIII"), 8);
  EXPECT_EQ(AutomaticRecognizer("IX"), 9);
  EXPECT_EQ(AutomaticRecognizer("X"), 10);
  EXPECT_EQ(AutomaticRecognizer("XII"), 12);
  EXPECT_EQ(AutomaticRecognizer("XIII"), 13);
  EXPECT_EQ(AutomaticRecognizer("XIV"), 14);
  EXPECT_EQ(AutomaticRecognizer("XV"), 15);
  EXPECT_EQ(AutomaticRecognizer("XVI"), 16);
  EXPECT_EQ(AutomaticRecognizer("XVII"), 17);
  EXPECT_EQ(AutomaticRecognizer("XVIII"), 18);
  EXPECT_EQ(AutomaticRecognizer("XIX"), 19);
  EXPECT_EQ(AutomaticRecognizer("XX"), 20);
  EXPECT_EQ(AutomaticRecognizer("XXIV"), 24);
  EXPECT_EQ(AutomaticRecognizer("XXIX"), 29);
  EXPECT_EQ(AutomaticRecognizer("XXXIV"), 34);
  EXPECT_EQ(AutomaticRecognizer("XL"), 40);
  EXPECT_EQ(AutomaticRecognizer("XLV"), 45);
  EXPECT_EQ(AutomaticRecognizer("XLIX"), 49);
  EXPECT_EQ(AutomaticRecognizer("L"), 50);
  EXPECT_EQ(AutomaticRecognizer("LII"), 52);
  EXPECT_EQ(AutomaticRecognizer("LXXXVIII"), 88);
  EXPECT_EQ(AutomaticRecognizer("XC"), 90);
  EXPECT_EQ(AutomaticRecognizer("XCIX"), 99);
  EXPECT_EQ(AutomaticRecognizer("C"), 100);
  EXPECT_EQ(AutomaticRecognizer("CI"), 101);
  EXPECT_EQ(AutomaticRecognizer("CXLIV"), 144);
  EXPECT_EQ(AutomaticRecognizer("CLX"), 160);
  EXPECT_EQ(AutomaticRecognizer("CLXXX"), 180);
  EXPECT_EQ(AutomaticRecognizer("CXC"), 190);
  EXPECT_EQ(AutomaticRecognizer("CXCIX"), 199);
  EXPECT_EQ(AutomaticRecognizer("CC"), 200);
  EXPECT_EQ(AutomaticRecognizer("CCCXLV"), 345);
  EXPECT_EQ(AutomaticRecognizer("CCCXCIX"), 399);
  EXPECT_EQ(AutomaticRecognizer("CD"), 400);
  EXPECT_EQ(AutomaticRecognizer("CDXLIV"), 444);
  EXPECT_EQ(AutomaticRecognizer("D"), 500);
  EXPECT_EQ(AutomaticRecognizer("DL"), 550);
  EXPECT_EQ(AutomaticRecognizer("DCCC"), 800);
  EXPECT_EQ(AutomaticRecognizer("DCCCXC"), 890);
  EXPECT_EQ(AutomaticRecognizer("CM"), 900);
  EXPECT_EQ(AutomaticRecognizer("CMXC"), 990);
  EXPECT_EQ(AutomaticRecognizer("CMXCIX"), 999);
  EXPECT_EQ(AutomaticRecognizer("M"), 1000);
  EXPECT_EQ(AutomaticRecognizer("MCM"), 1900);
  EXPECT_EQ(AutomaticRecognizer("MCMLXXX"), 1980);
  EXPECT_EQ(AutomaticRecognizer("MCMXC"), 1990);
  EXPECT_EQ(AutomaticRecognizer("MCMXCIV"), 1994);
  EXPECT_EQ(AutomaticRecognizer("MCMXCIX"), 1999);
  EXPECT_EQ(AutomaticRecognizer("MM"), 2000);
  EXPECT_EQ(AutomaticRecognizer("MMX"), 2010);
  EXPECT_EQ(AutomaticRecognizer("MMXIV"), 2014);
  EXPECT_EQ(AutomaticRecognizer("MMXXIII"), 2023);
  EXPECT_EQ(AutomaticRecognizer("MMMD"), 3500);
  EXPECT_EQ(AutomaticRecognizer("MMMCMXCIX"), 3999);
}

TEST(AutomaticRecognizerTest, InvalidRomanNumerals) {
  // Empty string
  EXPECT_THROW(AutomaticRecognizer(""), std::invalid_argument);

  // Too many repeated characters
  EXPECT_THROW(AutomaticRecognizer("IIII"), std::invalid_argument);
  EXPECT_THROW(AutomaticRecognizer("XXXX"), std::invalid_argument);
  EXPECT_THROW(AutomaticRecognizer("CCCC"), std::invalid_argument);
  EXPECT_THROW(AutomaticRecognizer("MMMM"), std::invalid_argument);

  // Invalid symbol combinations (nonexistent numerals)
  EXPECT_THROW(AutomaticRecognizer("IC"),
               std::invalid_argument);  // 99 should be XCIX
  EXPECT_THROW(AutomaticRecognizer("IL"), std::invalid_argument);
  EXPECT_THROW(AutomaticRecognizer("IM"), std::invalid_argument);
  EXPECT_THROW(AutomaticRecognizer("ID"), std::invalid_argument);
  EXPECT_THROW(AutomaticRecognizer("VX"), std::invalid_argument);
  EXPECT_THROW(AutomaticRecognizer("XD"), std::invalid_argument);
  EXPECT_THROW(AutomaticRecognizer("XM"), std::invalid_argument);

  // Symbols in incorrect order
  EXPECT_THROW(AutomaticRecognizer("IIV"), std::invalid_argument);
  EXPECT_THROW(AutomaticRecognizer("XXC"), std::invalid_argument);
  EXPECT_THROW(AutomaticRecognizer("CCM"), std::invalid_argument);
  EXPECT_THROW(AutomaticRecognizer("LC"), std::invalid_argument);
  EXPECT_THROW(AutomaticRecognizer("DM"), std::invalid_argument);

  // Repetition of non-repeatable characters
  EXPECT_THROW(AutomaticRecognizer("VV"), std::invalid_argument);
  EXPECT_THROW(AutomaticRecognizer("LL"), std::invalid_argument);
  EXPECT_THROW(AutomaticRecognizer("DD"), std::invalid_argument);

  // Unrecognized or non-Roman characters
  EXPECT_THROW(AutomaticRecognizer("A"), std::invalid_argument);
  EXPECT_THROW(AutomaticRecognizer("ZXC"), std::invalid_argument);
  EXPECT_THROW(AutomaticRecognizer("123"), std::invalid_argument);
  EXPECT_THROW(AutomaticRecognizer("MXM!"), std::invalid_argument);

  // Broken format combinations
  EXPECT_THROW(AutomaticRecognizer("IXI"), std::invalid_argument);
  EXPECT_THROW(AutomaticRecognizer("XIXIX"), std::invalid_argument);
  EXPECT_THROW(AutomaticRecognizer("IXX"), std::invalid_argument);

  // Extra characters after a valid numeral
  EXPECT_THROW(AutomaticRecognizer("XIIIABC"), std::invalid_argument);
}

TEST(PseudorandomNumberGeneratorTest, GeneratesCorrectFirstVariantSequence) {
  std::vector<int> expected = {0,
                               (37 * 0 + 3) % 64,
                               (37 * 3 + 3) % 64,
                               (37 * 50 + 3) % 64,
                               (37 * 61 + 3) % 64,
                               (37 * 20 + 3) % 64};

  auto result =
      PseudorandomNumberGenerator(ConsistencyVariant::kFirstVariant, 6);
  EXPECT_EQ(result, expected);
}

TEST(PseudorandomNumberGeneratorTest, GeneratesCorrectSecondVariantSequence) {
  std::vector<int> expected = {
      0, (25173 * 0 + 13849) % 65537, (25173 * 13849 + 13849) % 65537,
      (25173 * ((25173 * 13849 + 13849) % 65537) + 13849) % 65537};

  auto result =
      PseudorandomNumberGenerator(ConsistencyVariant::kSecondvariant, 4);
  EXPECT_EQ(result[0], expected[0]);
  EXPECT_EQ(result[1], expected[1]);
  EXPECT_EQ(result[2], expected[2]);
  EXPECT_EQ(result[3], expected[3]);
}

TEST(PseudorandomNumberGeneratorTest, GeneratesCorrectLength) {
  constexpr size_t length = 100;
  auto result1 =
      PseudorandomNumberGenerator(ConsistencyVariant::kFirstVariant, length);
  auto result2 =
      PseudorandomNumberGenerator(ConsistencyVariant::kSecondvariant, length);

  EXPECT_EQ(result1.size(), length);
  EXPECT_EQ(result2.size(), length);
}

TEST(PseudorandomNumberGeneratorTest, ThrowsOnInvalidVariant) {
  EXPECT_THROW(
      PseudorandomNumberGenerator(static_cast<ConsistencyVariant>(-1), 5),
      std::invalid_argument);
}

TEST(NumberSystemsTest, ValidConversions) {
  EXPECT_EQ(NumberSystems("0", 10, 2), "0");
  EXPECT_EQ(NumberSystems("0", 2, 10), "0");
  EXPECT_EQ(NumberSystems("1", 2, 10), "1");
  EXPECT_EQ(NumberSystems("10", 2, 10), "2");
  EXPECT_EQ(NumberSystems("1010", 2, 10), "10");
  EXPECT_EQ(NumberSystems("1111", 2, 10), "15");
  EXPECT_EQ(NumberSystems("11111111", 2, 16), "FF");
  EXPECT_EQ(NumberSystems("11111111", 2, 8), "377");

  EXPECT_EQ(NumberSystems("10", 10, 2), "1010");
  EXPECT_EQ(NumberSystems("255", 10, 16), "FF");
  EXPECT_EQ(NumberSystems("64", 10, 8), "100");
  EXPECT_EQ(NumberSystems("123", 10, 4), "1323");
  EXPECT_EQ(NumberSystems("26", 10, 16), "1A");
  EXPECT_EQ(NumberSystems("31", 10, 5), "111");

  EXPECT_EQ(NumberSystems("1A", 16, 10), "26");
  EXPECT_EQ(NumberSystems("1A", 16, 2), "11010");
  EXPECT_EQ(NumberSystems("FF", 16, 10), "255");
  EXPECT_EQ(NumberSystems("FF", 16, 8), "377");
  EXPECT_EQ(NumberSystems("ABC", 16, 10), "2748");

  EXPECT_EQ(NumberSystems("777", 8, 10), "511");
  EXPECT_EQ(NumberSystems("123", 8, 2), "1010011");
  EXPECT_EQ(NumberSystems("400", 8, 10), "256");

  EXPECT_EQ(NumberSystems("1323", 4, 10), "123");
  EXPECT_EQ(NumberSystems("111", 5, 10), "31");
  EXPECT_EQ(NumberSystems("100", 8, 10), "64");
}

TEST(NumberSystemsTest, InvalidBase) {
  EXPECT_THROW(NumberSystems("1010", 1, 10), std::invalid_argument);
  EXPECT_THROW(NumberSystems("1010", 2, 1), std::invalid_argument);
  EXPECT_THROW(NumberSystems("1010", 17, 10), std::invalid_argument);
  EXPECT_THROW(NumberSystems("1010", 10, 20), std::invalid_argument);
}

TEST(NumberSystemsTest, InvalidDigitsForBase) {
  EXPECT_THROW(NumberSystems("2", 2, 10),
               std::invalid_argument);  // 2 not allowed in base 2
  EXPECT_THROW(NumberSystems("G", 16, 10),
               std::invalid_argument);  // G is not a valid hex digit
  EXPECT_THROW(NumberSystems("19", 8, 10),
               std::invalid_argument);  // 9 not allowed in octal
}

}  // namespace
