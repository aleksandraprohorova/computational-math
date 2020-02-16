#include "lab2.hpp"

#include <iostream>
#include <algorithm>
#include <numeric>

#include "matrix.hpp"

void fillMatrixOfVandermond(Matrix<double>& matrix, const std::vector<double>& x)
{
  if (matrix.size() != x.size())
  {
    throw std::invalid_argument("Size of matrix douesn't match the size of x vector.");
  }
  int exp = 0;
  for (auto it = matrix.begin(); it != matrix.end(); ++exp, it += matrix.size())
  {
    std::transform(x.begin(), x.end(), it,
        [=](double x){ return pow(x, exp); });
  }
}

void fillBvector(std::vector<double>& b)
{
  int k = 0;
  std::generate(b.begin(), b.end(), [&](){++k; return pow(2, k) + cos(k);});
}

void solveSystem(std::vector<double>& x, std::vector<double>& b, std::ostream& out)
{
  out << "\nX: ";
  std::copy(x.begin(), x.end(), std::ostream_iterator<double>(out, " ; "));

  size_t size = x.size();
  Matrix<double> matrix(size);
  fillMatrixOfVandermond(matrix, x);

  out << "\nOriginal matrix:\n" << matrix;

  double cond = 0;
  int flag = 0;

  std::vector<int> pivot(size);
  decomp(size, size, matrix.data(), &cond, pivot.data(), &flag);
  if (flag != 0)
  {
    throw std::runtime_error("Error occured in program decomp.\n");
  }

  out << "\nCond: " << cond;

  solve(size, size, matrix.data(), b.data(), pivot.data());
  std::cout << "\nAnswers: ";
  std::copy(b.begin(), b.end(), std::ostream_iterator<double>(std::cout, " ; "));
  std::cout << "\n";
}

void solveSystem(int size, std::ostream& out)
{
  std::vector<double> b(size);
  fillBvector(b);

  out << "\nN = " << size
      << "\nB: ";
  std::copy(b.begin(), b.end(), std::ostream_iterator<double>(out, " ; "));

  std::vector<double> x(size);
  std::iota(x.begin(), x.end(), 1);
  double divider = 1;
  while (divider *= 10, divider != 100000)
  {
    x.back() = 1 + 1 / divider;
    solveSystem(x, b, out);
  }
}

int main()
{
  solveSystem(5, std::cout);
  std::cout << "______________________________________\n";
  solveSystem(7, std::cout);
  std::cout << "______________________________________\n";
  solveSystem(9, std::cout);
  return 0;
}
