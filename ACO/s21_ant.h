#ifndef S21_ANT_
#define S21_ANT_

#include <memory>

#include "../s21_graph.h"
#include "../s21_matrix_methods.h"
#include "../s21_random.h"

namespace s21 {

class Ant {
 public:
  Ant(size_t start_point, size_t count);
  double GetDistance() const noexcept;
  std::vector<int> GetPath() const noexcept;
  void BuildPath(const Graph &graph, const Matrix &pheromones);
  void CalculateDistance(const Graph &graph);
  bool IsVisited(size_t i, size_t j);

 private:
  int GetNextIndex(const Graph &graph, const Matrix &pheromones, size_t from);

 private:
  double distance_;
  std::vector<bool> tabu_;
  std::vector<int> path_;
  std::vector<std::pair<size_t, size_t>> visited_vertexes_;
  std::unique_ptr<Random> rnd_;
};

}  // namespace s21

#endif  // S21_ANT_
