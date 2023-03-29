#ifndef S21_GRAPH_H_
#define S21_GRAPH_H_

#include <limits>
#include <string>
#include <vector>

#include "s21_matrix_methods.h"

namespace s21 {
static constexpr double kInf = std::numeric_limits<double>::infinity();

class Graph {
 public:
  void LoadGraphFromFile(const std::string &filename);
  void ExportGraphToDot(const std::string &filename);
  size_t Count() const noexcept;
  Matrix GetMatrix() const;

  Matrix::reference operator[](size_t i);
  Matrix::const_reference operator[](size_t i) const;

 private:
  void ThrowExceptionIfInputError(std::ifstream &input_stream);

 private:
  Matrix adjacency_matrix_;
};
}  // namespace s21

#endif  // S21_GRAPH_H_
