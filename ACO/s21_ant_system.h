#ifndef S21_ANT_SYSTEM_H_
#define S21_ANT_SYSTEM_H_

#include <algorithm>
#include <memory>
#include <vector>

#include "../s21_graph.h"
#include "../s21_tsm_result.h"
#include "s21_ant.h"

namespace s21 {

class AntSystem {
 public:
  AntSystem() = default;
  TsmResult Solve(const Graph &graph);

 private:
  void InitAnts();
  void InitPheromones();
  void UpdatePheromones();
  void UpdateAnts(const Graph &graph);
  void UpdateBestSolution(TsmResult *result);
  TsmResult GetCurrentIterationBestSolution();

 private:
  size_t count_;
  std::vector<std::unique_ptr<Ant>> ants_;
  Matrix pheromones_;
};

}  // namespace s21

#endif  // S21_ANT_SYSTEM_H_
