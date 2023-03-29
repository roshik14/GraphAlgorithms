#include "s21_propabilites.h"

#include <cmath>

#include "s21_aco_constants.h"

using s21::Propabilites;

Propabilites::Propabilites(const Graph &graph, const Matrix &pheromones,
                           const std::vector<bool> &tabu, size_t from)
    : graph_(graph),
      pheromones_(pheromones),
      tabu_(tabu),
      from_(from),
      propabilites_(std::vector<double>(graph.Count())),
      sum_(0) {}

std::vector<double> Propabilites::Calculate() {
  CalculateAllPropabilitiesAndSum();
  CalculatePropabilitiesDividedBySum();
  return GetCumulativePropabilites();
}

void Propabilites::CalculateAllPropabilitiesAndSum() {
  for (size_t i = 0, count = propabilites_.size(); i < count; ++i) {
    if (graph_[from_][i] && !tabu_[i]) {
      propabilites_[i] = MultiplyPheromoneAndVisibility(pheromones_[from_][i],
                                                        graph_[from_][i]);
      sum_ += propabilites_[i];
    } else {
      propabilites_[i] = kInf;
    }
  }
}

double Propabilites::MultiplyPheromoneAndVisibility(double pheromone,
                                                    double length) {
  return std::pow(pheromone, ACO_Constants::kAlpha) *
         std::pow(1 / length, ACO_Constants::kBeta);
}

std::vector<double> Propabilites::GetCumulativePropabilites() {
  std::vector<double> cumul_propabilities(propabilites_.size() + 1);
  for (size_t i = 0, count = propabilites_.size(); i < count; ++i) {
    cumul_propabilities[i + 1] = cumul_propabilities[i] + propabilites_[i];
  }
  return cumul_propabilities;
}

void Propabilites::CalculatePropabilitiesDividedBySum() {
  for (size_t i = 0, count = propabilites_.size(); i < count; ++i) {
    propabilites_[i] =
        !std::isinf(propabilites_[i]) ? propabilites_[i] / sum_ : 0;
  }
}
