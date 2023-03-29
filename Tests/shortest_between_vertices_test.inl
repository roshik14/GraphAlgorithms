void CompareDjkstra(const std::string &filename, int start, int end, int expected) {
    Graph graph;
    graph.LoadGraphFromFile(filename);
    GraphAlgorithms alg;
    auto actual = alg.GetShortestPathBetweenVertices(graph, start, end);
    ASSERT_EQ(actual, expected);
}

TEST(ShortestPathBetweenVertices, test1) {
    auto expected = 23;
    CompareDjkstra("Tests/4.txt", 1, 3, expected);
}

TEST(ShortestPathBetweenVertices, test2) {
    auto expected = 88;
    CompareDjkstra("Tests/4.txt", 5, 1, expected);
}

TEST(ShortestPathBetweenVertices, test3) {
    auto expected = -1;
    CompareDjkstra("Tests/4.txt", 3, 1, expected);
}

TEST(ShortestPathBetweenVertices, test4) {
    auto expected = 16;
    CompareDjkstra("Tests/example.txt", 5, 1, expected);
}

TEST(ShortestPathBetweenVertices, test5) {
    auto expected = 98;
    CompareDjkstra("Tests/example.txt", 10, 7, expected);
}

TEST(ShortestPathBetweenVertices, test6) {
    auto expected = 10;
    CompareDjkstra("Tests/3.txt", 6, 3, expected);
}

TEST(ShortestPathBetweenVertices, test7) {
    auto expected = 6;
    CompareDjkstra("Tests/3.txt", 5, 4, expected);
}

TEST(ShortestPathBetweenVertices, test8) {
    auto expected = 2;
    CompareDjkstra("Tests/2.txt", 4, 1, expected);
}
