// Copyright 2025, github.com/BIBlical33
//
// Practice functions
// Task descriptions (in Russian):
// https://drive.google.com/drive/folders/1WK_ulsyjzy_g6WYER9h5GWO-sKLsl-Zm?usp=sharing
//
// License: GNU General Public License v3.0
// See: https://www.gnu.org/licenses/gpl-3.0.html

#ifndef PROCEDURAL_PROGRAMMING_INCLUDE_PRACTICES_H_
#define PROCEDURAL_PROGRAMMING_INCLUDE_PRACTICES_H_

#include <string>
#include <variant>
#include <vector>

namespace procedural_programming {

// Run marbles task
int Marbles(size_t marbles_amount);

}  // namespace procedural_programming

namespace procedural_programming::practice4 {

struct TriangleParams {
  double first_side = 0.0, second_side = 0.0, third_side = 0.0;
};

struct RectangleParams {
  double width = 0.0, height = 0.0;
};

struct CircleParams {
  double radius = 0.0;
};

enum class FigureType {
  kRectangle,
  kTriangle,
  kCircle,
};

enum class ConsistencyVariant { kFirstVariant, kSecondvariant };

double File();

int Sign(double x) noexcept;

double GeometricFigures(
    FigureType figure_type,
    const std::variant<TriangleParams, RectangleParams, CircleParams>& params);

void FormerGlory();

void SineWave();

int AutomaticRecognizer(const std::string& roman_number);

std::vector<int> PseudorandomNumberGenerator(
    ConsistencyVariant consistency_variant, size_t consistency_length);

void MatrixMultiplication();

std::string NumberSystems(std::string number, int old_base, int new_base);

}  // namespace procedural_programming::practice4

namespace procedural_programming::practice5 {

int EuclideanAlgorithm(int first_number, int second_number);

std::vector<int> EratosthenesSieve(int last_number);

}

#endif  // PROCEDURAL_PROGRAMMING_INCLUDE_PRACTICES_H_
