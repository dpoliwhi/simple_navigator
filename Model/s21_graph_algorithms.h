#pragma once

#include <limits.h>

#include <algorithm>
#include <iostream>
#include <vector>
#include <ctime>

#include "../Containers/s21_queue.h"
#include "../Containers/s21_stack.h"
#include "../Model/aco.h"
#include "../Model/sa.h"
#include "../Model/s21_graph.h"
// #include "../Model/simple_timer.h"

namespace s21 {

class GraphAlgorithms {
 private:
  std::vector<int> correctOutput(std::vector<int> vec);
  void checkGraph(const Graph &graph);
  void checkGraphsSymmetric(const Graph &graph);

 public:
  std::vector<int> depthFirstSearch(const Graph &graph, int startVertex);
  std::vector<int> breadthFirstSearch(const Graph &graph, int startVertex);
  int getShortestPathBetweenVertices(const Graph &graph, int vertex1, int vertex2);
  Matrix getShortestPathsBetweenAllVertices(const Graph &graph);
  Matrix getLeastSpanningTree(const Graph &graph);
  TsmResult solveTravelingSalesmanProblem(const Graph &graph);
  TsmResult solveTravelingSalesmanProblem_SA(const Graph &graph);
  TsmResult solveTravelingSalesmanProblemBruteForce(const Graph &graph);
  std::vector<std::pair<double, double>> comparasing(const Graph &graph, int N);
};

}  // namespace s21
