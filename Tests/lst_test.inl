void CompareLST(const Matrix &actual, const Matrix &expected) {
    ASSERT_EQ(actual.size(), expected.size());
    int size = actual.size();
    for (auto i = 0; i < size; ++i) {
        for (auto j = 0; j < size; ++j) {
            ASSERT_DOUBLE_EQ(actual[i][j], expected[i][j]);
        }
    }
}

void TestLST(const std::string &filename, const Matrix &expected) {
    Graph graph;
    graph.LoadGraphFromFile(filename);
    GraphAlgorithms alg;
    auto actual = alg.GetLeastSpanningTree(graph);
    CompareLST(actual, expected);
}

TEST(LeastSpanningTree, test1) {
    Matrix expected {
        std::vector<double> {0, 0, 0, 0, 0, 0, 0, 12, 4, 0, 0},
        std::vector<double> {0, 0, 0, 0, 0, 0, 72, 0, 0, 0, 12},
        std::vector<double> {0, 0, 0, 0, 0, 0, 0, 9, 0, 0, 13},
        std::vector<double> {0, 0, 0, 0, 4, 12, 0, 0, 0, 0, 0},
        std::vector<double> {0, 0, 0, 4, 0, 0, 0, 9, 0, 0, 0},
        std::vector<double> {0, 0, 0, 12, 0, 0, 0, 0, 0, 3, 0},
        std::vector<double> {0, 72, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        std::vector<double> {12, 0, 9, 0, 9, 0, 0, 0, 0, 0, 0},
        std::vector<double> {4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        std::vector<double> {0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0},
        std::vector<double> {0, 12, 13, 0, 0, 0, 0, 0, 0, 0, 0},
    };
    TestLST("Tests/example.txt", expected);
}

TEST(LeastSpanningTree, test2) {
    Matrix expected {
        std::vector<double> {0, 1, 0, 3, 3, 0},
        std::vector<double> {1, 0, 3, 0, 0, 3},
        std::vector<double> {0, 3, 0, 0, 0, 0},
        std::vector<double> {3, 0, 0, 0, 0, 0},
        std::vector<double> {3, 0, 0, 0, 0, 0},
        std::vector<double> {0, 3, 0, 0, 0, 0},
    };
    TestLST("Tests/lst.txt", expected);
}

TEST(LeastSpanningTree, empty_graph_test) {
    Matrix expected;
    Graph graph;
    GraphAlgorithms alg;
    ASSERT_THROW(alg.GetLeastSpanningTree(graph), std::invalid_argument);
}
