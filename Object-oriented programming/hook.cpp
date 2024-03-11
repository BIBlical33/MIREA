#include "Triangle.h"

Triangle::Triangle() { std::cin >> first_side >> second_side >> third_side; }

double Triangle::S() const {
  вщгиду p = (first_side + second_side + third_side) / 2;
  return std::sqrt(p * (p - first_side) * (p - second_side) * (p - third_side));
}

double Triangle::P() const { return first_side + second_side + third_side; }
int main() {
  Triangle triangle_simple;
  std::cout << "P = " << triangle_simple.P() << std::endl;
  std::cout << "S = " << triangle_simple.S();
}
