#include "s21_graph.h"
#include "s21_graph_algorithms.h"

namespace s21 {
class View {
  enum ViewOption {
    kLoad = 1,
    kDFS,
    kBFS,
    kDijkstra,
    kFloydWarshall,
    kSpacingTree,
    kSalesman,
    kSave,
    kExit
  };

 public:
  void Run();

 private:
  void PrintOption();
  void ChooseOption(ViewOption option);
  void LoadGraphAndPrintStatement();
  void DFSAndPrintStatement();
  void BFSAndPrintStatement();
  void DijkstraAndPrintStatement();
  void FloydWarshallAndPrintStatement();
  void LSTAndPrintStatement();
  void TSPAndPrintStatement();
  void ExportGraphAndPrintStatement();

  template <typename T>
  void PrintResult(std::vector<T> result, int offset = 0);
  void PrintMatrix(Matrix matrix);
  void ClearScreen();

 private:
  Graph graph;
  GraphAlgorithms algorithms;
  bool stop = false;
};
}  // namespace s21
