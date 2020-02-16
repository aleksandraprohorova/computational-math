#ifndef COMPUTATIONAL_MATH_LAB2_MATRIX
#define COMPUTATIONAL_MATH_LAB2_MATRIX

#include <vector>
#include <iosfwd>
#include <cmath>
#include <stdexcept>
#include <iterator>

template<typename T>
class Matrix
{
public:
  using iterator = typename std::vector<T>::iterator;
  using const_iterator = typename std::vector<T>::const_iterator;
  class Row
  {
  public:
    Row(T* begin, size_t size);
    T& operator[](size_t index);
  private:
    T* begin_;
    size_t size_;
  };

  Matrix(size_t size);
  Row operator[](size_t index);
  iterator begin();
  iterator end();
  const_iterator begin() const;
  const_iterator end() const;
  size_t size() const;
  void resize(size_t size);
  T* data();

private:
  std::vector<T> data_;
};

template<typename T>
Matrix<T>::Row::Row(T* begin, size_t size):
  begin_(begin),
  size_(size)
{
}
template<typename T>
T& Matrix<T>::Row::operator[](size_t index)
{
  if (index > size_)
  {
    throw std::invalid_argument("Index is out of bounds.");
  }
  return begin_[index];
}
template<typename T>
typename Matrix<T>::Row Matrix<T>::operator[](size_t index)
{
  return Row(&data_[0] + index * size(), size());
}
template<typename T>
Matrix<T>::Matrix(size_t size):
  data_(size * size)
{
}
template<typename T>
typename Matrix<T>::const_iterator Matrix<T>::begin() const
{
  return data_.begin();
}
template<typename T>
typename Matrix<T>::const_iterator Matrix<T>::end() const
{
  return data_.end();
}
template<typename T>
typename Matrix<T>::iterator Matrix<T>::begin()
{
  return data_.begin();
}
template<typename T>
typename Matrix<T>::iterator Matrix<T>::end()
{
  return data_.end();
}
template<typename T>
size_t Matrix<T>::size() const
{
  return sqrt(data_.size());
}
template<typename T>
void Matrix<T>::resize(size_t size)
{
  data_.resize(size * size);
}
template<typename T>
T* Matrix<T>::data()
{
  return &data_[0];
}

template <typename T>
std::ostream& operator<<(std::ostream& out, Matrix<T>& matrix)
{
  for (auto it = matrix.begin(); it != matrix.end(); it += matrix.size())
  {
    std::copy(it, it + matrix.size(), std::ostream_iterator<T>(out, " ; "));
    out << "\n";
  }
  return out;
}

#endif // COMPUTATIONAL_MATH_LAB2_MATRIX
