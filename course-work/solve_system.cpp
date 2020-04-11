#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include "../cmath.h"
#include "matrix.hpp"
#include <cmath>

void fillRightPart(double h, std::vector<double>& y,
  std::vector<double>& b, double Q, double R)
{
  b[0] = - (y[1] - 2 * y[0] + Q - h * h * y[0] * y[0]  + h*h);
  int n = b.size();
  for (int i = 1; i < n; ++i)
  {
    b[i] = - (y[i+1] - 2 * y[i] + y[i-1] - h*h* y[i] * y[i] + h*h);
  }
  b[n-1] = - (R - 2 * y[n - 1] + y[n-2] - h*h* y[n -1] * y[n-1] + h*h);
}
void Jacoby(int n, double h, double* x, Matrix<double>& matrix)
{
  for (int i = 0; i < n; ++i)
  {
    matrix[i][i] = -2 - 2 * h * h * x[i];
    if (i > 0)
    {
      matrix[i][i-1] = 1;
    }
    if (i < n-1)
    {
      matrix[i][i+1] = 1;
    }
  }
}
bool checkEpsilon(int n, double* epsilon)
{
  for (int i = 0; i < n; ++i)
  {
    if (std::abs(epsilon[i]) > 0.00001)
    {
      return true;
    }
  }
  return false;
}
void solveSystem(int n, double h)
{
  Matrix<double> matrix(n);
  for (int i = 0; i < n; ++i)
  {
    for (int j = 0; j < n; ++j)
    {
      matrix[i][j] = 0;
    }
  }
  std::vector<int> pivot(n);
  std::vector<double> b(n);
  std::vector<double> y(n);
  std::vector<double> y0(n);
  double Q = 0;
  double R = 1;
  for (int i = 0; i < n; ++i)
  {
    y0[i] = i / 10;
    y[i] = y0[i];
  }
  Jacoby(n, h, y0.data(), matrix);
  double cond = 0;
  int flag = 0;


  decomp(n, n, matrix.data(), &cond, pivot.data(), &flag);

  if (flag != 0)
  {
    throw std::runtime_error("Error occured in program decomp.\n");
  }

  std::cout << "\nCond: " << cond << "\n";

  do {
    fillRightPart(h, y, b, Q, R);

    solve(n, n, matrix.data(), b.data(), pivot.data());

    for (int i = 0; i < n; ++i)
    {
      y[i] += b[i];
    }
  }
  while(checkEpsilon(n, b.data()));
  std::cout << "answers: ";
  std::copy(y.begin(), y.end(), std::ostream_iterator<double>(std::cout, " ; "));
  std::cout << "\nepsilon: ";
  std::copy(b.begin(), b.end(), std::ostream_iterator<double>(std::cout, " ; "));
  std::cout << "\n";
}
int main()
{
  int n = 9;
  double h = 0.1;
  std::cout << "For n = 10:\n";
  solveSystem(n, h);
  n = 19;
  h = 0.05;
  std::cout << "For n = 20:\n";
  solveSystem(n, h);
  return 0;
}
