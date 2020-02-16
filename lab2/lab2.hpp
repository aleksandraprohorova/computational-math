#ifndef COMPUTATIONAL_MATH_LAB2
#define COMPUTATIONAL_MATH_LAB2

#include "matrix.hpp"
#include "../cmath.h"

void fillMatrixOfVandermond(Matrix<double>& matrix, const std::vector<double>& x);
void fillXvector(std::vector<double>& x, double start, double end);
void solveSystem(std::vector<double>& x, std::vector<double>& b, std::ostream& out);
void solveSystem(int size, std::ostream& out);
#endif // COMPUTATIONAL_MATH_LAB2
