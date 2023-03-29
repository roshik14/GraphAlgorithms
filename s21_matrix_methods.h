#ifndef S21_MATRIX_METHODS_H_
#define S21_MATRIX_METHODS_H_

#include <cstddef>
#include <vector>

namespace s21 {

class MatrixMethods {
 public:
  using Matrix = std::vector<std::vector<double>>;
  static Matrix CreateMatrix(size_t sz, double value = 0);
};

using Matrix = MatrixMethods::Matrix;

}  // namespace s21

#endif  // S21_MATRIX_METHODS_H_
