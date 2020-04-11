#include <iostream>
#include <cmath>
#include "../cmath.h"

double function(double x)
{
  return sqrt(x) * std::exp(x);
}

int main()
{
  double a = 0.000000001;
  //double b = 1.0 / 9;
  double b = 0.111111111;
  double epsrel = 1.0e-10;
  double epsabs = 0.0;
  double result = -1;
  double errest = -1;
  int nfe = -1;
  double posn = -1;
  int flag = 0;
  quanc8(function, a, b, epsabs, epsrel, &result, &errest, &nfe, &posn, &flag);
  if (flag < 0)
  {
    std::cout << "trouble spot at x = " << posn << "\n";
    std::cout << "unconverged subintervals " << abs(flag) << "\n";
    return 1;
  }
  result -= 0.026392602;
  result = pow(result, 4);
  std::cout << "result = " << result << "\n";
  return 0;
}
