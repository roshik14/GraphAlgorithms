void CompareBFS(const std::vector<int> &actual, const std::vector<int> &expected) {
  ASSERT_EQ(actual.size(), expected.size());
  for (size_t i = 0, size = actual.size(); i < size; ++i) {
    ASSERT_EQ(actual[i], expected[i]);
  }
}

void TestBFS(const std::string &filename, int startVertex,
             const std::vector<int> &expected) {
  Graph graph;
  graph.LoadGraphFromFile(filename);
  GraphAlgorithms alg;
  auto actual = alg.BreadthFirstSearch(graph, startVertex);
  CompareBFS(actual, expected);
}

void ExceptionTestBFS(const std::string &filename, int startVertex) {
  Graph graph;
  graph.LoadGraphFromFile(filename);
  GraphAlgorithms alg;
  ASSERT_THROW(alg.BreadthFirstSearch(graph, startVertex), std::invalid_argument);
}

TEST(BreadthFirstSearch, test1) {
  std::vector<int> expected{1, 3, 4, 5, 2};
  TestBFS("Tests/1.txt", 1, expected);
}

TEST(BreadthFirstSearch, test2) {
  std::vector<int> expected{3, 1, 2, 5, 4};
  TestBFS("Tests/1.txt", 3, expected);
}

TEST(BreadthFirstSearch, test3) {
  std::vector<int> expected{5, 1, 3, 4, 2};
  TestBFS("Tests/1.txt", 5, expected);
}

TEST(BreadthFirstSearch, test4) {
  std::vector<int> expected{1, 2, 3, 4, 5, 6};
  TestBFS("Tests/2.txt", 1, expected);
}

TEST(BreadthFirstSearch, test5) {
  std::vector<int> expected{4, 1, 2, 3, 6, 5};
  TestBFS("Tests/2.txt", 4, expected);
}

TEST(BreadthFirstSearch, test6) {
  std::vector<int> expected{4, 1, 3, 6, 2, 5};
  TestBFS("Tests/3.txt", 4, expected);
}

TEST(BreadthFirstSearch, test7) {
  std::vector<int> expected{6, 4, 5, 1, 3, 2};
  TestBFS("Tests/3.txt", 6, expected);
}

TEST(BreadthFirstSearch, test8) {
  std::vector<int> expected{5, 1, 6, 2, 4, 3};
  TestBFS("Tests/3.txt", 5, expected);
}

TEST(BreadthFirstSearch, exception_test1) { ExceptionTestBFS("Tests/1.txt", -1); }

TEST(BreadthFirstSearch, exception_test2) { ExceptionTestBFS("Tests/1.txt", 10); }
