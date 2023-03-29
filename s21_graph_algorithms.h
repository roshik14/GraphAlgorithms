#ifndef S21_GRAPH_ALGORITHMS_H_
#define S21_GRAPH_ALGORITHMS_H_

#include <map>
#include <vector>

#include "ACO/s21_ant_system.h"
#include "s21_graph.h"
#include "s21_matrix_methods.h"
#include "s21_tsm_result.h"

namespace s21 {

class GraphAlgorithms {
 public:
  std::vector<int> DepthFirstSearch(const Graph &graph, int startVertex) const;
  std::vector<int> BreadthFirstSearch(const Graph &graph,
                                      int startVertex) const;
  double GetShortestPathBetweenVertices(const Graph &graph, int start,
                                        int end) const;
  Matrix GetShortestPathBetweenAllVertices(const Graph &graph) const;
  Matrix GetLeastSpanningTree(const Graph &graph) const;
  TsmResult SolveTravelingSalesmanProblem(const Graph &graph) const;

 private:
  void ThrowExceptionIfError(size_t count, int start_vertex = 0,
                             int end_vertex = 0) const;
  int GetMinIndex(const std::vector<double> &distances,
                  const std::vector<bool> &visited) const;
  Matrix GetSpanningTreeMatrix(
      const std::map<std::pair<int, int>, double> &weights, size_t sz) const;
  std::pair<int, int> GetVerticesPair(const Graph &graph,
                                      const std::vector<bool> &visited,
                                      size_t count) const;

 private:
  enum Color { kWhite, kGray, kBlack };
};
}  // namespace s21

#endif  // S21_GRAPH_ALGORITHMS_H_
