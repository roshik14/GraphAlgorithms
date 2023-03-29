#include "../s21_graph.h"
#include "../s21_graph_algorithms.h"
#include "../s21_tsm_result.h"
#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <stdexcept>
#include <climits>
#include <fstream>

using namespace s21;
using Matrix = std::vector<std::vector<double>>;

#include "bfs_test.inl"
#include "dfs_test.inl"
#include "shortest_between_vertices_test.inl"
#include "floyd_warshall_test.inl"
#include "lst_test.inl"
#include "aco_test.inl"
#include "graph_test.inl"

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
