void CompareDFS(const std::vector<int> &actual, const std::vector<int> &expected) {
    ASSERT_EQ(actual.size(), expected.size());
    int size = actual.size();
    for (auto i = 0; i < size; ++i) {
        ASSERT_EQ(actual[i], expected[i]);
    }
}

void TestDFS(const std::string &filename, int startVertex, const std::vector<int> &expected) {
    Graph graph;
    graph.LoadGraphFromFile(filename);
    GraphAlgorithms alg;
    auto actual = alg.DepthFirstSearch(graph, startVertex);
    CompareDFS(actual, expected);
}

void ExceptionTestDFS(const std::string &filename, int startVertex) {
    Graph graph;
    graph.LoadGraphFromFile(filename);
    GraphAlgorithms alg;
    ASSERT_THROW(alg.DepthFirstSearch(graph, startVertex), std::invalid_argument);
}

TEST(DepthFirstSearch, test1) {
    std::vector<int> expected{1, 3, 5, 2, 4};
    TestDFS("Tests/1.txt", 1, expected);
}

TEST(DepthFirstSearch, test2) {
    std::vector<int> expected{3, 1, 5, 4, 2};
    TestDFS("Tests/1.txt", 3, expected);
}

TEST(DepthFirstSearch, test3) {
    std::vector<int> expected{5, 1, 3, 2, 4};
    TestDFS("Tests/1.txt", 5, expected);
}

TEST(DepthFirstSearch, test4) {
    std::vector<int> expected{1, 2, 3, 4, 6, 5};
    TestDFS("Tests/2.txt", 1, expected);
}

TEST(DepthFirstSearch, test5) {
    std::vector<int> expected{4, 1, 2, 3, 5, 6};
    TestDFS("Tests/2.txt", 4, expected);
}

TEST(DepthFirstSearch, test6) {
    std::vector<int> expected{4, 1, 5, 6, 2, 3};
    TestDFS("Tests/3.txt", 4, expected);
}

TEST(DepthFirstSearch, test7) {
    std::vector<int> expected{6, 4, 1, 5, 2, 3};
    TestDFS("Tests/3.txt", 6, expected);
}

TEST(DepthFirstSearch, test8) {
    std::vector<int> expected{5, 1, 2, 3, 4, 6};
    TestDFS("Tests/3.txt", 5, expected);
}

TEST(DepthFirstSearch, exception_test1) { ExceptionTestDFS("Tests/1.txt", -1); }

TEST(DepthFirstSearch, exception_test2) { ExceptionTestDFS("Tests/1.txt", 10); }
