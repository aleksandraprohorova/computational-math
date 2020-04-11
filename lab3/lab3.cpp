#include <iostream>
#include <cmath>
#include "../cmath.h"

int getSystem(int n, double t, double x[], double dx[])
{
  dx[0] = -40 * x[0] + 260 * x[1] + 1 / (10 * t * t + 1);
  dx[1] = 30 * x[0] - 270 * x[1] + std::exp(-2 * t);
  return 0;
}
int main()
{
  int fail = 0;
  double hprint = 0.02;

  const int n = 2;
  double x[2] = {0, 1};
  double dx[2];
  int flag = 1;
  double h;
  int nfe;
  int maxfe  = 5000;
  double relerr = 1.0e-4;
  double abserr = 1.0e-4;


  rkfinit(n, &fail);
  if (fail != 0)
  {
    std::cout << "Error occured in rkfinit.\n";
    return 1;
  }
  for (double t = 0; t < 0.4; /*t += hprint*/)
  {
    rkf45(getSystem, n, x, dx, &t, t + hprint, &relerr, abserr,
             &h, &nfe, maxfe, &flag);
    std::cout << "t = " << t << "; x1 = " << x[0] << "; x2 = " << x[1] << "; flag = " << flag << "\n";
  }
  rkfend();
  std::cout << "Adams: \n";

  x[0] = 0;
  x[1] = 1;
  double f[3][2];
  double t = 0;
  rkfinit(n, &fail);
  hprint = 0.0002;
  for (int i = 0; i < 3; ++i)
  {
    rkf45(getSystem, n, x, f[i], &t, t + hprint, &relerr, abserr,
             &h, &nfe, maxfe, &flag);
    std::cout << "t = " << t << "; x1 = " << x[0] << "; x2 = " << x[1] << "; flag = " << flag << "\n";
  }
  rkfend();
  double hint = 0.002;
  hprint = 0.02;
  int counter = 0;
  for (double t = 0.0006; t < 0.4; t += hint)
  {
    x[0] = x[0] +
        hint * (23 * f[2][0] - 16 * f[1][0] + 5 * f[0][0]) / 12;
    x[1] = x[1] +
        hint * (23 * f[2][1] - 16 * f[1][1] + 5 * f[0][1]) / 12;
    if (counter++ % 10 == 0)
    {
      std::cout << "t = " << t + hint << "; x1 = " << x[0] << "; x2 = " << x[1] << "\n";
    }
    f[0][0] = f[1][0];
    f[1][0] = f[2][0];
    f[0][1] = f[1][1];
    f[1][1] = f[2][1];

    getSystem(n, t, x, f[2]);
  }


  return 0;
}
