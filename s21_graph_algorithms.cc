#include "s21_graph_algorithms.h"

#include <algorithm>
#include <climits>
#include <cmath>
#include <map>
#include <stdexcept>

#include "s21_graph.h"
#include "s21_queue.h"
#include "s21_stack.h"

using s21::GraphAlgorithms;
using s21::Matrix;
using s21::TsmResult;

std::vector<int> GraphAlgorithms::DepthFirstSearch(const Graph &graph,
                                                   int start_vertex) const {
  ThrowExceptionIfError(graph.Count(), start_vertex - 1);
  std::vector<Color> node_colors(graph.Count(), kWhite);
  std::vector<int> result;
  s21::Stack temp_stack;

  temp_stack.push(start_vertex - 1);

  while (!temp_stack.empty()) {
    int top = temp_stack.peek();
    if (node_colors[top] == kWhite) {
      node_colors[top] = kGray;
      for (int i = graph.Count() - 1; i >= 0; --i) {
        if (graph[top][i] && !std::isinf(graph[top][i]) &&
            node_colors[i] == kWhite)
          temp_stack.push(i);
      }
    } else if (node_colors[top] == kGray) {
      result.push_back(top);
      temp_stack.pop();
      node_colors[top] = kBlack;
    } else {
      temp_stack.pop();
    }
  }
  std::reverse(result.begin(), result.end());
  for (auto i = result.begin(); i < result.end(); ++i) (*i)++;
  return result;
}

std::vector<int> GraphAlgorithms::BreadthFirstSearch(const Graph &graph,
                                                     int start_vertex) const {
  auto vertices_count = graph.Count();
  --start_vertex;
  ThrowExceptionIfError(vertices_count, start_vertex);
  std::vector<int> resultVertices;
  Queue queue;
  queue.push(start_vertex);
  std::vector<bool> visited(vertices_count, false);
  visited.at(start_vertex) = true;
  while (!queue.empty()) {
    auto current_vertex = queue.peek();
    queue.pop();
    for (size_t i = 0; i < vertices_count; ++i) {
      if (!std::isinf(graph[current_vertex][i]) && !visited[i]) {
        visited[i] = true;
        queue.push(i);
      }
    }
    resultVertices.push_back(current_vertex + 1);
  }
  return resultVertices;
}

double GraphAlgorithms::GetShortestPathBetweenVertices(const Graph &graph,
                                                       int start,
                                                       int end) const {
  auto count = graph.Count();
  start--;
  end--;
  ThrowExceptionIfError(count, start, end);
  std::vector<double> distances(count, kInf);
  std::vector<bool> visited(count, false);
  distances[start] = 0;
  for (size_t i = 0; i != count; ++i) {
    auto u = GetMinIndex(distances, visited);
    visited[u] = true;
    for (size_t j = 0; j < count; j++) {
      auto sum = distances[u] + graph[u][j];
      if (!visited[j] && !std::isinf(graph[u][j]) &&
          !std::isinf(distances[u]) && sum < distances[j]) {
        distances[j] = sum;
      }
    }
  }
  auto result = distances[end];
  return !std::isinf(result) ? result : -1;
}

Matrix GraphAlgorithms::GetShortestPathBetweenAllVertices(
    const Graph &graph) const {
  ThrowExceptionIfError(graph.Count());
  std::vector<std::vector<double>> result(graph.GetMatrix());

  for (int k = 0, n = result.size(); k != n; ++k) {
    for (int i = 0; i != n; ++i) {
      for (int j = 0; j != n; ++j) {
        result[i][j] = std::min(result[i][j], result[i][k] + result[k][j]);
      }
    }
  }
  return result;
}

Matrix GraphAlgorithms::GetLeastSpanningTree(const Graph &graph) const {
  auto vertices_count = graph.Count();
  ThrowExceptionIfError(vertices_count);
  std::vector<bool> visited(vertices_count, false);
  visited[0] = true;
  std::map<std::pair<int, int>, double> weights;
  for (size_t start_v = 0; start_v < vertices_count - 1; ++start_v) {
    auto vertices = GetVerticesPair(graph, visited, vertices_count);
    auto v = vertices.first;
    auto u = vertices.second;
    weights[vertices] = graph[u][v];
    visited[u] = true;
  }
  return GetSpanningTreeMatrix(weights, vertices_count);
}

TsmResult GraphAlgorithms::SolveTravelingSalesmanProblem(
    const Graph &graph) const {
  const size_t count = 100;
  auto ant_system = std::make_unique<AntSystem>();
  TsmResult result{std::vector<int>{}, kInf};
  for (size_t i = 0; i < count; ++i) {
    auto current = ant_system->Solve(graph);
    if (current.distance < result.distance) {
      result = std::move(current);
    }
  }
  return result;
}

void GraphAlgorithms::ThrowExceptionIfError(size_t count, int start_vertex,
                                            int end_vertex) const {
  if (!count) {
    throw std::invalid_argument("Graph is empty");
  }
  auto c = static_cast<int>(count);
  if (start_vertex < 0 || start_vertex > c || end_vertex < 0 ||
      end_vertex > c) {
    throw std::invalid_argument("Vertex parameters not correct");
  }
}

std::pair<int, int> GraphAlgorithms::GetVerticesPair(
    const Graph &graph, const std::vector<bool> &visited, size_t count) const {
  auto min = kInf;
  std::pair<int, int> vertices{0, 0};
  for (size_t i = 0; i < count; ++i) {
    if (!visited[i]) {
      continue;
    }
    for (size_t j = 0; j < count; ++j) {
      if (!visited[j] && !std::isinf(graph[i][j]) && min > graph[i][j]) {
        min = graph[i][j];
        vertices.first = i;
        vertices.second = j;
      }
    }
  }
  return vertices;
}

Matrix GraphAlgorithms::GetSpanningTreeMatrix(
    const std::map<std::pair<int, int>, double> &weights, size_t sz) const {
  auto matrix = MatrixMethods::CreateMatrix(sz);
  for (auto itb = weights.begin(), ite = weights.end(); itb != ite; ++itb) {
    auto v = itb->first.first;
    auto u = itb->first.second;
    matrix[v][u] = itb->second;
    matrix[u][v] = itb->second;
  }
  return matrix;
}

int GraphAlgorithms::GetMinIndex(const std::vector<double> &distances,
                                 const std::vector<bool> &visited) const {
  int min = INT_MAX;
  int index = 0;
  for (size_t i = 0, sz = distances.size(); i != sz; ++i) {
    if (!visited[i] && distances[i] <= min) {
      min = distances[i];
      index = i;
    }
  }
  return index;
}
