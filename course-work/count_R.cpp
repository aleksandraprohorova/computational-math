#include <iostream>
#include "../cmath.h"
#include <cmath>

double object(int n, double x[])
{
  return 2 * x[0] * (1 - pow(0.5, x[0])) + pow(0.25, x[0]) + pow(x[0] - 1, 2);
}

int main()
{
  double xmin[10], step[10];
double fmin, reqmin, reltol, abstol;
//double object();
int    n, konvge, maxfe, numres, flag, nfe;

n       = 1;
reqmin  = 1.0e-16;
abstol  = 1.0e-12;
reltol  = 1.0e-12;
konvge  = 5;
maxfe   = 1000;
step[0] = 0.1;
step[1] = 0.1;
//xmin[0] = -1.0;
xmin[0] = 0.1;
xmin[1] =  1.0;

printf ("\n\n  --- CMATH --- Design Software 1989\n");
printf ("\nExercise the function minimizer nelmin().\n\n");

nelmin (object, n, xmin, &fmin, reqmin, step,
        konvge, &nfe, maxfe, &numres, &flag,
        reltol, abstol);
//printf ("%s\n\n", cmathmsg(NELMIN_C, flag));

if (flag == 0 || flag == 2)
   {
   printf ("Minimum objective value of ");
   printf ("%e", fmin);
   printf ("  found at ..\n");
   printf ("x[0] = %f  .. x[1] = %f\n\n", xmin[0], xmin[1]);
   printf ("Statistics ... ");
   printf ("nfe = %d .. numres = %d\n\n",
            nfe, numres);

   printf ("Expected solution ...\n");
   printf ("x0 = 0.5   x1 = -1.0   objective = 0.0\n");
   }

   double result = 1.559554 * xmin[0];
   std::cout << "result = " << result << "\n";
  return 0;
}
