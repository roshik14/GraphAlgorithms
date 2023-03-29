#include "s21_console_view.h"

#include <exception>
#include <iostream>

using s21::View;

void View::Run() {
  ClearScreen();
  std::cout << "Welcome to the Graph Algorithms program!\n";
  int option;
  while (!stop) {
    PrintOption();
    std::cin >> option;
    ClearScreen();
    try {
      ChooseOption(static_cast<ViewOption>(option));
    } catch (const std::exception& msg) {
      std::cout << msg.what() << '\n';
    }
  }
}

void View::PrintOption() {
  std::cout << "Please choose option to continue!\n";
  std::cout << "1) Load Graph from file\n2) Use the DFS algorithm\n3) Use the "
               "BFS algorithm\n";
  std::cout
      << "4) Use Dijkstra's algorithm\n5) Use Floyd–Warshall's algorithm\n";
  std::cout
      << "6) Use Least Spanning Tree algorithm\n7) Solve salseman problem\n";
  std::cout << "8) Save Graph as image\n9) Exit\n";
}

void View::ChooseOption(ViewOption option) {
  if (!std::cin.fail()) {
    if (option == kLoad) {
      LoadGraphAndPrintStatement();
    } else if (option == kDFS) {
      DFSAndPrintStatement();
    } else if (option == kBFS) {
      BFSAndPrintStatement();
    } else if (option == kDijkstra) {
      DijkstraAndPrintStatement();
    } else if (option == kFloydWarshall) {
      FloydWarshallAndPrintStatement();
    } else if (option == kSpacingTree) {
      LSTAndPrintStatement();
    } else if (option == kSalesman) {
      TSPAndPrintStatement();
    } else if (option == kSave) {
      ExportGraphAndPrintStatement();
    } else if (option == kExit) {
      stop = true;
    } else {
      throw std::runtime_error("Wrong input!\n");
    }
  } else {
    std::cin.clear();
    std::cin.ignore(1000, '\n');
  }
}

void View::LoadGraphAndPrintStatement() {
  std::string filename;
  std::cout << "Please write filename to load the graph\n";
  std::cin >> filename;
  graph.LoadGraphFromFile(filename);
  std::cout << "Load success!\n\n";
}

void View::DFSAndPrintStatement() {
  int vertex;
  std::cout << "Please write start vertex\n";
  std::cin >> vertex;
  if (!std::cin.fail()) {
    auto result = algorithms.DepthFirstSearch(graph, vertex);
    PrintResult(result);
  } else {
    throw std::runtime_error("Error: Wrong input\n");
  }
}

void View::BFSAndPrintStatement() {
  int vertex;
  std::cout << "Please write start vertex\n";
  std::cin >> vertex;
  if (!std::cin.fail()) {
    auto result = algorithms.BreadthFirstSearch(graph, vertex);
    PrintResult(result);
  } else {
    throw std::runtime_error("Error: Wrong input\n");
  }
}

void View::DijkstraAndPrintStatement() {
  int firstVertex, secondVertex;
  std::cout << "Please write start and finish vertices\n";
  std::cin >> firstVertex >> secondVertex;
  if (!std::cin.fail()) {
    int result = algorithms.GetShortestPathBetweenVertices(graph, firstVertex,
                                                           secondVertex);
    std::cout << "Result path length: " << result << "\n";
  } else {
    throw std::runtime_error("Error: Wrong input\n");
  }
}

void View::FloydWarshallAndPrintStatement() {
  auto result = algorithms.GetShortestPathBetweenAllVertices(graph);
  std::cout << "Result path matrix:\n";
  PrintMatrix(result);
}

void View::LSTAndPrintStatement() {
  auto result = algorithms.GetLeastSpanningTree(graph);
  std::cout << "Result Least Spanning Tree matrix:\n";
  PrintMatrix(result);
}

void View::TSPAndPrintStatement() {
  auto result = algorithms.SolveTravelingSalesmanProblem(graph);
  if (result.distance == kInf) {
    std::cout << "Can't solve solutiion for this graph\n\n";
  } else {
    std::cout << "Sequence of traversing vertices: ";
    PrintResult(result.vertices, 1);
    std::cout << "Route length: " << result.distance << '\n';
  }
}

void View::ExportGraphAndPrintStatement() {
  std::string filename;
  std::cout << "Please write filename to export the graph\n";
  std::cin >> filename;
  graph.ExportGraphToDot(filename);
  std::cout << "Save success!\n\n";
}

template <typename T>
void View::PrintResult(std::vector<T> result, int offset) {
  for (auto i : result) {
    std::cout << i + offset << " ";
  }
  std::cout << "\n";
}

void View::PrintMatrix(Matrix matrix) {
  for (const auto& row : matrix) {
    PrintResult(row);
  }
  std::cout << "\n";
}

void View::ClearScreen() { std::cout << "\033[2J\033[H"; }
