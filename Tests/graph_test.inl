void CompareGraph(const Matrix &actual, const Matrix &expected) {
    ASSERT_EQ(actual.size(), expected.size());
    int size = actual.size();
    for (auto i = 0; i < size; ++i) {
        for (auto j = 0; j < size; ++j) {
            if (!expected[i][j] && i != j) {
                ASSERT_DOUBLE_EQ(actual[i][j], kInf);
            } else {
                ASSERT_DOUBLE_EQ(actual[i][j], expected[i][j]);
            }
        }
    }
}

TEST(GraphTest, load_test) {
    Graph graph;
    graph.LoadGraphFromFile("Tests/example.txt");
    Matrix expected {
        std::vector<double> {0, 29, 20, 21, 16, 31, 100, 12, 4, 31, 18},
        std::vector<double> {29, 0, 15, 29, 28, 40, 72, 21, 29, 41, 12},
        std::vector<double> {20, 15, 0, 15, 14, 25, 81, 9, 23, 27, 13},
        std::vector<double> {21, 29, 15, 0, 4, 12, 92, 12, 25, 13, 25},
        std::vector<double> {16, 28, 14, 4, 0, 16, 94, 9, 20, 16, 22},
        std::vector<double> {31, 40, 25, 12, 16, 0, 95, 24, 36, 3, 37},
        std::vector<double> {100, 72, 81, 92, 94, 95, 0, 90, 101, 99, 84},
        std::vector<double> {12, 21, 9, 12, 9, 24, 90, 0, 15, 25, 13},
        std::vector<double> {4, 29, 23, 25, 20, 36, 101, 15, 0, 35, 18},
        std::vector<double> {31, 41, 27, 13, 16, 3, 99, 25, 35, 0, 38},
        std::vector<double> {18, 12, 13, 25, 22, 37, 84, 13, 18, 38, 0},
    };
    CompareGraph(graph.GetMatrix(), expected);
}

void TestDotFileWithPoint(std::ifstream &input_stream, size_t start_point, size_t count) {
    std::string line;
    auto next = start_point; 
    for (size_t i = start_point; i < start_point + count; ++i) {
        std::getline(input_stream, line);
        auto expected = "\t" + std::to_string(start_point) + " -- " + std::to_string(++next) + ';';
        ASSERT_EQ(line, expected);
    }
}

void TestDotFile(const std::string &filename, const Graph &graph) {
    std::ifstream input_stream(filename);
    std::string line;
    std::getline(input_stream, line);
    ASSERT_EQ(line, "graph graphname {");
    for (size_t i = 1; i <= graph.Count(); ++i) {
        std::getline(input_stream, line);
        auto expected = "\t" + std::to_string(i) + ';';
        ASSERT_EQ(line, expected);
    }
    TestDotFileWithPoint(input_stream, 1, 3);
    TestDotFileWithPoint(input_stream, 2, 2);
    TestDotFileWithPoint(input_stream, 3, 1);
}

TEST(GraphTest, export_test) {
    Graph graph;
    graph.LoadGraphFromFile("Tests/aco_1.txt");
    const std::string output_file = "test.dot";
    graph.ExportGraphToDot(output_file);
    TestDotFile(output_file, graph);
}

TEST(GraphTest, count_test) {
    Graph graph;
    graph.LoadGraphFromFile("Tests/1.txt");
    auto expected = 5;
    ASSERT_EQ(graph.Count(), expected);
}

TEST(GraphTest, no_file_test) {
    Graph graph;
    ASSERT_THROW(graph.LoadGraphFromFile("no_such_file.txt"), std::runtime_error);
}

TEST(GraphTest, emtpy_graph) {
    Graph graph;
    auto actual = graph.GetMatrix();
    Matrix expected;
    CompareGraph(actual, expected);
}
