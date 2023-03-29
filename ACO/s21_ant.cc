#include "s21_ant.h"

#include <algorithm>

#include "s21_aco_constants.h"
#include "s21_propabilites.h"

using s21::ACO_Constants;
using s21::Ant;
using s21::Propabilites;
using s21::Random;

Ant::Ant(size_t start_point, size_t count)
    : distance_(0.0), tabu_(std::vector<bool>(count)) {
  path_.push_back(start_point);
  tabu_[start_point] = true;
  rnd_ = std::make_unique<Random>();
}

void Ant::BuildPath(const Graph &graph, const Matrix &pheromones) {
  for (size_t i = 0, sz = graph.Count(); i < sz; ++i) {
    int index = GetNextIndex(graph, pheromones, path_.back());
    if (index != -1) {
      visited_vertexes_.push_back(std::pair{path_.back(), index});
      path_.push_back(index);
      tabu_[index] = true;
    }
  }
  path_.push_back(path_.front());
}

int Ant::GetNextIndex(const Graph &graph, const Matrix &pheromones,
                      size_t from) {
  auto propabilities =
      std::make_unique<Propabilites>(graph, pheromones, tabu_, from)
          ->Calculate();
  auto rnd_value = rnd_->Next(0.0, 1.0);
  for (size_t i = 1; i < propabilities.size(); ++i) {
    if (!tabu_[i - 1] && rnd_value < propabilities[i]) {
      return i - 1;
    }
  }
  return -1;
}

void Ant::CalculateDistance(const Graph &graph) {
  for (size_t i = 0, length = path_.size() - 1; i < length; ++i) {
    distance_ += graph[path_[i]][path_[i + 1]];
  }
}

double Ant::GetDistance() const noexcept { return distance_; }

std::vector<int> Ant::GetPath() const noexcept { return path_; }

bool Ant::IsVisited(size_t i, size_t j) {
  for (auto itb = visited_vertexes_.begin(), ite = visited_vertexes_.end();
       itb != ite; ++itb) {
    if (itb->first == i && itb->second == j) {
      return true;
    }
  }
  return false;
}
