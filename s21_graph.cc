#include "s21_graph.h"

#include <fstream>
#include <stdexcept>

using s21::Graph;
using s21::Matrix;

Matrix::reference Graph::operator[](size_t i) { return adjacency_matrix_[i]; }

Matrix::const_reference Graph::operator[](size_t i) const {
  return adjacency_matrix_[i];
}

void Graph::LoadGraphFromFile(const std::string &filename) {
  std::ifstream input_stream(filename);
  if (!input_stream.is_open()) {
    throw std::runtime_error("No such file");
  }
  auto size = 0;
  input_stream >> size;
  ThrowExceptionIfInputError(input_stream);
  auto input_matrix = MatrixMethods::CreateMatrix(size);
  for (auto i = 0; i < size; ++i) {
    for (auto j = 0; j < size; ++j) {
      input_stream >> input_matrix[i][j];
      ThrowExceptionIfInputError(input_stream);
      if (!input_matrix[i][j] && i != j) {
        input_matrix[i][j] = kInf;
      }
    }
  }
  std::swap(adjacency_matrix_, input_matrix);
}

void Graph::ThrowExceptionIfInputError(std::ifstream &input_stream) {
  if (!input_stream.good()) {
    throw std::runtime_error("File is not correct");
  }
}

void Graph::ExportGraphToDot(const std::string &filename) {
  if (!adjacency_matrix_.size()) {
    throw std::runtime_error("Graph is empty");
  }
  std::ofstream output(filename);
  if (!output.is_open()) {
    throw std::runtime_error("Filename is not correct");
  }
  output << "graph graphname {\n";
  for (int i = 0, iend = adjacency_matrix_.size(); i != iend; ++i) {
    output << "\t" << i + 1 << ";\n";
  }
  for (int i = 0, iend = adjacency_matrix_.size(); i != iend; ++i) {
    for (int j = i, jend = adjacency_matrix_[i].size(); j != jend; ++j) {
      if (adjacency_matrix_[i][j] != 0) {
        output << "\t" << i + 1 << " -- " << j + 1 << ";\n";
      }
    }
  }
  output << "}";
  output.close();
}

size_t Graph::Count() const noexcept { return adjacency_matrix_.size(); }

Matrix Graph::GetMatrix() const { return adjacency_matrix_; }
