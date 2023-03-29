#include "s21_ant_system.h"

#include <cmath>
#include <stdexcept>

#include "../s21_matrix_methods.h"
#include "s21_aco_constants.h"

using s21::ACO_Constants;
using s21::AntSystem;
using s21::TsmResult;

TsmResult AntSystem::Solve(const Graph &graph) {
  count_ = graph.Count();
  auto result = TsmResult{std::vector<int>{}, kInf};
  if (!count_) {
    throw std::invalid_argument("Graph is empty");
  }
  InitPheromones();
  for (size_t i = 0; i < ACO_Constants::kIterationsCount; ++i) {
    UpdateAnts(graph);
    UpdateBestSolution(&result);
    UpdatePheromones();
  }
  return result;
}

void AntSystem::UpdateBestSolution(TsmResult *result) {
  auto solution = GetCurrentIterationBestSolution();
  if (solution.distance < result->distance) {
    *result = std::move(solution);
  }
}

void AntSystem::UpdateAnts(const Graph &graph) {
  InitAnts();
  for (const auto &ant : ants_) {
    ant->BuildPath(graph, pheromones_);
    ant->CalculateDistance(graph);
  }
}

void AntSystem::InitPheromones() {
  pheromones_ = MatrixMethods::CreateMatrix(count_, 0);
  for (size_t i = 0; i < count_; ++i) {
    for (size_t j = 0; j < count_; ++j) {
      if (i != j) {
        pheromones_[i][j] = ACO_Constants::kTau0;
      }
    }
  }
}

void AntSystem::InitAnts() {
  ants_ = std::vector<std::unique_ptr<Ant>>(count_);
  for (size_t i = 0; i < count_; ++i) {
    ants_[i] = std::make_unique<Ant>(i, count_);
  }
}

TsmResult AntSystem::GetCurrentIterationBestSolution() {
  std::sort(ants_.begin(), ants_.end(), [](auto &first, auto &second) {
    return first->GetDistance() < second->GetDistance();
  });
  const auto &best_result = ants_.front();
  return TsmResult{best_result->GetPath(), best_result->GetDistance()};
}

void AntSystem::UpdatePheromones() {
  for (size_t i = 0; i < count_; ++i) {
    for (size_t j = 0; j < count_; ++j) {
      for (size_t k = 0; k < ants_.size(); ++k) {
        if (ants_[k]->IsVisited(i, j)) {
          auto pheromones_sum = ACO_Constants::kQ / ants_[k]->GetDistance();
          pheromones_[i][j] +=
              (1 - ACO_Constants::kRho) * pheromones_[i][j] + pheromones_sum;
          pheromones_[j][i] = pheromones_[i][j];
        }
      }
    }
  }
}
