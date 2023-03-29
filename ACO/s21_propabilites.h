#ifndef S21_PROPABILITIES_H_
#define S21_PROPABILITIES_H_

#include <vector>

#include "../s21_graph.h"
#include "../s21_matrix_methods.h"

namespace s21 {
class Propabilites {
 public:
  Propabilites(const Graph &graph, const Matrix &pheromones,
               const std::vector<bool> &tabu, size_t from);
  std::vector<double> Calculate();

 private:
  void CalculateAllPropabilitiesAndSum();
  double MultiplyPheromoneAndVisibility(double pheromone, double length);
  void CalculatePropabilitiesDividedBySum();
  std::vector<double> GetCumulativePropabilites();

 private:
  const Graph &graph_;
  const Matrix &pheromones_;
  const std::vector<bool> tabu_;
  size_t from_;
  std::vector<double> propabilites_;
  double sum_;
};
}  // namespace s21

#endif  // S21_PROPABILITES_H_
