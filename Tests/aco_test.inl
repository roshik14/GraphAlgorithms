bool CompareACO(const TsmResult &actual, const TsmResult &expected) {
  size_t equal_count = 0;
  for (size_t i = 0, size = actual.vertices.size(); i < size; ++i) {
      if (actual.vertices[i] == expected.vertices[i]) {
          equal_count++;
      }
  }
  return equal_count == actual.vertices.size() && actual.distance == expected.distance;
}

void TestACO(const std::string &filename, const TsmResult &expected) {
  Graph graph;
  graph.LoadGraphFromFile(filename);
  GraphAlgorithms alg;
  bool found = false;
  for (size_t i = 0; i < 30; ++i) {
      auto actual = alg.SolveTravelingSalesmanProblem(graph);
      if (CompareACO(actual, expected)) {
          found = true;
          break;
      }
  }
  ASSERT_EQ(found, true);
}

void ExceptionTest() {
  Graph graph;
  GraphAlgorithms alg;
  ASSERT_THROW(alg.SolveTravelingSalesmanProblem(graph), std::invalid_argument);
}

TEST(ACO_Algorithm, test1) {
  TsmResult expected {std::vector<int>{0, 1, 2, 3, 0}, 40};
  TestACO("Tests/aco_1.txt", expected);
}

TEST(ACO_Algorithm, test2) {
  TsmResult expected {std::vector<int>{0, 1, 2, 3, 4, 0}, 220};
  TestACO("Tests/aco_2.txt", expected);
}

TEST(ACO_Algorithm, test3) {
  TsmResult expected {std::vector<int>{1, 10, 8, 0, 7, 4, 3, 9, 5, 2, 6, 1}, 253 };
  TestACO("Tests/example.txt", expected);
}

TEST(ACO_Algorithm, no_solution_test) {
  TsmResult expected {std::vector<int>{0, 0}, 0}; 
  TestACO("Tests/aco_empty.txt", expected);
}

TEST(ACO_Algorithm, exception_test) { ExceptionTest(); }
