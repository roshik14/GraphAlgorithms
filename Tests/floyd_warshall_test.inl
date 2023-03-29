void CheckMatrixFW(Matrix actual, Matrix expected);

void TestFW(const std::string &filename, const Matrix &expected) {
    Graph graph;
    graph.LoadGraphFromFile(filename);
    GraphAlgorithms alg;
    auto actual = alg.GetShortestPathBetweenAllVertices(graph);
    CheckMatrixFW(actual, expected);
}

void CheckMatrixFW(Matrix actual, Matrix expected) {
    int size = expected.size();
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            ASSERT_EQ(actual[i][j], expected[i][j]);
        }
    }
}

TEST(FloydWarshall, test1) {
    Matrix expected{
        {0, 2, 1, 2, 2}, {2, 0, 1, 1, 2}, {1, 1, 0, 2, 1}, {2, 1, 2, 0, 3}, {2, 2, 1, 3, 0}};
    TestFW("Tests/1.txt", expected);
}

TEST(FloydWarshall, test2) {
    Matrix expected{{0, 1, 3, 2, 4, 4}, {1, 0, 3, 1, 3, 4}, {3, 3, 0, 3, 5, 1},
                           {2, 1, 3, 0, 4, 4}, {4, 3, 5, 4, 0, 5}, {4, 4, 1, 4, 5, 0}};
    TestFW("Tests/2.txt", expected);
}

TEST(FloydWarshall, test3) {
    Matrix expected{{0, 1, 4, 3, 3, 6}, {1, 0, 3, 4, 4, 7}, {4, 3, 0, 3, 7, 10},
                           {3, 4, 3, 0, 6, 9}, {3, 4, 7, 6, 0, 3}, {6, 7, 10, 9, 3, 0}};
    TestFW("Tests/3.txt", expected);
}

TEST(FloydWarshall, test4) {
    Matrix expected{
        {0, 3, 23, 23, 13}, {43, 0, 20, 20, 45}, {kInf, kInf, 0, kInf, kInf}, {23, 20, 40, 0, 36}, {88, 45, 19, 65, 0}};
    TestFW("Tests/4.txt", expected);
}
