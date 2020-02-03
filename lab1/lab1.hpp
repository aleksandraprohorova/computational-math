#ifndef COMPUTATIONAL_MATH_LAB1
#define COMPUTATIONAL_MATH_LAB1

#include <iosfwd>
#include <vector>

#define CUSTOM_EPSILON 1e-17

struct point_t
{
  double x;
  double y;
};

struct function_t
{
  std::vector<double> x;
  std::vector<double> y;

  function_t();
  function_t(size_t n);

  size_t size() const;
  double* X();
  double* Y();
};
std::istream& operator>>(std::istream& in, function_t& function);
std::ostream& operator<<(std::ostream& out, const function_t& function);

struct spline_t
{
  std::vector<double> b;
  std::vector<double> c;
  std::vector<double> d;

  spline_t(size_t n);
  double* B();
  double* C();
  double* D();
  size_t size() const;
};
std::ostream& operator<<(std::ostream& out, const spline_t& factors);



#endif // COMPUTATIONAL_MATH_LAB1
