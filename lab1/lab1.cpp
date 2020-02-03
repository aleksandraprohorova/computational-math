#include <iostream>
#include <iomanip>
#include <algorithm>
#include <iterator>

#include "../cmath.h"
#include "lab1.hpp"

double RightPart(double x)
{
  return 1.8 * x * x;
}

double bisection(function_t& function, spline_t& factors,
    double leftX, double rightX, double (*rightPart)(double))
{
  double middleX = -1;
  double middleY = -4;
  int last = 5;

  while (abs(middleY) > CUSTOM_EPSILON)
  {
    middleX = (leftX + rightX) / 2;
    middleY = seval(function.size(), middleX,
        function.X(), function.Y(),
        factors.B(), factors.C(), factors.D(), &last) -
        rightPart(middleX);

    double rightY = seval(function.size(), rightX,
        function.X(), function.Y(),
        factors.B(), factors.C(), factors.D(), &last) -
        rightPart(rightX);
    double leftY = seval(function.size(), leftX,
        function.X(), function.Y(),
        factors.B(), factors.C(), factors.D(), &last) -
        rightPart(leftX);

    if (leftY * rightY > 0)
    {
      std::cout << leftY << " " << rightY << "\n";
      throw std::runtime_error("LeftY and RightY must be of different signs.");
    }
    if (leftY * middleY < 0)
    {
      rightX = middleX;
    }
    else if (middleY * rightY < 0)
    {
      leftX = middleX;
    }
    else
    {
      throw std::runtime_error("middleY must have different sign with one of the border.");
    }
  }
  return middleX;
}



int main()
{
  function_t function;
  std::cin >> function;
  std::cout << "Original function f(x):\n" << function << "\n";

  spline_t factors(function.size());

  int flag = 0;
  spline(function.size(), 0, 0, 0, 0, function.X(), function.Y(), factors.B(), factors.C(), factors.D(), &flag);
  if (flag != 0)
  {
    std::cout << "Error occured in spline function.\n";
    return 1;
  }
  std::cout << "Spline coefficients:\n" << factors << "\n";

  function_t newFunction(function.size());
  std::copy(function.x.begin(), function.x.end(), newFunction.x.begin());
  int last = 0;
  std::transform(newFunction.x.begin(), newFunction.x.end(), newFunction.y.begin(),
      [&](double x){
          return seval(function.size(), x,
            function.X(), function.Y(),
            factors.B(), factors.C(), factors.D(), &last) -
            RightPart(x);
        });

  std::cout << "Function given by equation f(x) = rightPart(x)\n" << newFunction << "\n";

  std::vector<double> ans;
  for (int i = 1; i < newFunction.size(); ++i)
  {
    if (newFunction.y[i] * newFunction.y[i - 1] < 0)
    {
      ans.push_back(bisection(function, factors,
          newFunction.x[i - 1], newFunction.x[i], RightPart));
    }
  }

  std::cout << "Number of roots: " << ans.size() << "\n";
  std::copy(ans.begin(), ans.end(), std::ostream_iterator<double>(std::cout, " "));
  std::cout << "\n";

  return 0;
}
