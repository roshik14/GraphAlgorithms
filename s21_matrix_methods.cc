#include "s21_matrix_methods.h"

using s21::MatrixMethods;

MatrixMethods::Matrix MatrixMethods::CreateMatrix(size_t sz, double value) {
  Matrix result(sz);
  for (size_t i = 0; i < sz; ++i) {
    result[i] = std::vector<double>(sz, value);
  }
  return result;
}
