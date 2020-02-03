#include "lab1.hpp"

#include <iostream>
#include <iterator>
#include <algorithm>
#include <functional>

std::istream& operator>>(std::istream& in, point_t& point)
{
  in >> point.x >> point.y;
  return in;
}
std::ostream& operator<<(std::ostream& out, const point_t& point)
{
  out << point.x << " ; " << point.y << "\n";
  return out;
}
function_t::function_t()
{}
function_t::function_t(size_t n):
  x(n),
  y(n)
{}
size_t function_t::size() const
{
  return x.size();
}
double* function_t::X()
{
  return x.data();
}
double* function_t::Y()
{
  return y.data();
}

std::istream& operator>>(std::istream& in, function_t& function)
{
  std::vector<point_t> points(std::istream_iterator<point_t>(std::ref(in)),
      std::istream_iterator<point_t>());
  std::transform(points.begin(), points.end(), std::back_inserter(function.x), [](const point_t& point){return point.x;});
  std::transform(points.begin(), points.end(), std::back_inserter(function.y), [](const point_t& point){return point.y;});
  return in;
}
std::ostream& operator<<(std::ostream& out, const function_t& function)
{
  std::transform(function.x.begin(), function.x.end(), function.y.begin(),
      std::ostream_iterator<point_t>(out), [](double x, double y){return point_t{x, y};});
  return out;
}
spline_t::spline_t(size_t n):
  b(n),
  c(n),
  d(n)
{
}
double* spline_t::B()
{
  return b.data();
}
double* spline_t::C()
{
  return c.data();
}
double* spline_t::D()
{
  return d.data();
}
size_t spline_t::size() const
{
  return b.size();
}
std::ostream& operator<<(std::ostream& out, const spline_t& factors)
{
  for (int i = 0; i < factors.size(); ++i)
  {
    out << "spline " << i << ": " << factors.b[i] << "; " << factors.c[i] << "; " << factors.d[i] << "\n";
  }
  return out;
}
