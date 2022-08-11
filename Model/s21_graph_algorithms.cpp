#include "s21_graph_algorithms.h"

namespace s21 {

std::vector<int> GraphAlgorithms::depthFirstSearch(const Graph &graph, int startVertex) {
  if (startVertex > graph.getSize() || startVertex <= 0) {
    throw std::invalid_argument("Invalid start index");
  }
  std::vector<int> path;
  std::vector<bool> detected;
  detected.resize(graph.getSize(), false);
  stack<int> visitStack;
  Matrix graphData = graph.getData();
  startVertex -= 1;

  visitStack.push(startVertex);
  while (!visitStack.empty()) {
    int node = visitStack.top();
    visitStack.pop();
    if (detected[node]) continue;
    detected[node] = true;
    for (int i = graph.getSize() - 1; i >= 0; i--) {
      if (graphData(node, i) >= 1 && !detected[i]) {
        visitStack.push(i);
      }
    }
    path.push_back(node + 1);
  }
  return path;
}

std::vector<int> GraphAlgorithms::breadthFirstSearch(const Graph &graph, int startVertex) {
  if (startVertex > graph.getSize() || startVertex <= 0) {
    throw std::invalid_argument("Invalid start index");
  }
  std::vector<int> path;
  std::vector<bool> detected;
  detected.resize(graph.getSize(), false);
  queue<int> visitQueue;
  Matrix graphData = graph.getData();
  startVertex -= 1;

  detected[startVertex] = true;
  visitQueue.push(startVertex);
  while (!visitQueue.empty()) {
    int node = visitQueue.front();
    visitQueue.pop();
    for (int i = 0; i < graph.getSize(); i++) {
      if (graphData(node, i) >= 1 && !detected[i]) {
        detected[i] = true;
        visitQueue.push(i);
      }
    }
    path.push_back(node + 1);
  }
  return path;
}

int GraphAlgorithms::getShortestPathBetweenVertices(const Graph &graph, int vertex1, int vertex2) {
  if (vertex1 > graph.getSize() || vertex1 <= 0 || vertex2 > graph.getSize() || vertex2 <= 0) {
    throw std::invalid_argument("Invalid start index");
  }
  vertex1 -= 1;
  std::vector<int> distance;
  distance.resize(graph.getSize(), INT_MAX);
  distance[vertex1] = 0;
  std::vector<bool> visited;
  visited.resize(graph.getSize(), false);
  Matrix graphData = graph.getData();
  int minIndex = 0, temp;
  while (minIndex < INT_MAX) {
    int minDistanse;
    minIndex = minDistanse = INT_MAX;
    for (int i = 0; i < graph.getSize(); i++) {
      if (!visited[i] && distance[i] < minDistanse) {
        minDistanse = distance[i];
        minIndex = i;
      }
    }
    if (minIndex != INT_MAX) {
      for (int i = 0; i < graph.getSize(); i++) {
        if (graphData(minIndex, i) > 0) {
          temp = minDistanse + graphData(minIndex, i);
          distance[i] = std::min(distance[i], temp);
        }
      }
      visited[minIndex] = true;
    }
  }
  return distance[vertex2 - 1];
}

Matrix GraphAlgorithms::getShortestPathsBetweenAllVertices(const Graph &graph) {
  Matrix resMtrx = graph.getData();
  for (int k = 0; k < graph.getSize(); k++) {
    for (int i = 0; i < graph.getSize(); i++) {
      for (int j = 0; j < graph.getSize(); j++) {
        if (resMtrx(i, k) > 0 && resMtrx(k, j) > 0 && i != j) {
          if (resMtrx(i, j) == 0) resMtrx(i, j) = resMtrx(i, k) + resMtrx(k, j);
          resMtrx(i, j) = std::min(resMtrx(i, j), resMtrx(i, k) + resMtrx(k, j));
        }
      }
    }
  }
  return resMtrx;
}

Matrix GraphAlgorithms::getLeastSpanningTree(const Graph &graph) {
  if (graph.getDirectionType() == directed) {
    throw std::invalid_argument("Invalid direction type");
  }
  int size = graph.getSize();
  Matrix data = graph.getData();
  Matrix resMtrx(size, size);

  std::vector<bool> visited(size, false);
  visited[0] = true;
  for (int l = 0; l < size - 1; l++) {
    int minx = 0, miny = 0;
    for (int i = 0; i < size; i++) {
      if (visited[i]) {
        for (int j = 0; j < size; j++) {
          if (!visited[j] && data(i, j) > 0 && (miny == -1 || data(i, j) < data(miny, minx))) {
            miny = i, minx = j;
          }
        }
      }
    }
    visited[minx] = true;
    resMtrx(miny, minx) = resMtrx(minx, miny) = data(miny, minx);
  }
  return resMtrx;
}

std::vector<int> GraphAlgorithms::correctOutput(std::vector<int> vec) {
  std::vector<int> result;
  for (size_t i = 0; i < vec.size(); i++) {
    result.push_back(vec[i] + 1);
  }
  return result;
}


void GraphAlgorithms::checkGraph(const Graph &graph) {
  if (graph.getDirectionType() == directed || graph.getWeightType() == unweighted || graph.getSize() <= 2) {
    throw std::invalid_argument("Wrong graph");
  }
}

void GraphAlgorithms::checkGraphsSymmetric(const Graph &graph) {
  Matrix data = graph.getData();
  for (int i = 0; i < graph.getSize(); i++) {
    for (int j = 0; j < graph.getSize(); j++) {
      if (i != j && data(i, j) == 0) {
        throw std::invalid_argument("Wrong graph");
      }
    }
  }
}

TsmResult GraphAlgorithms::solveTravelingSalesmanProblem(const Graph &graph) {
  checkGraph(graph);
  ACO algo;
  TsmResult result = algo.TSPSolve(graph);
  result.vertices = correctOutput(result.vertices);
  return result;
}

TsmResult GraphAlgorithms::solveTravelingSalesmanProblem_SA(const Graph &graph) {
  checkGraph(graph);
  SimulatedAnnealing algo(graph);
  TsmResult result = algo.SA_TSPSolve();
  result.vertices = correctOutput(result.vertices);
  return result;
}

TsmResult GraphAlgorithms::solveTravelingSalesmanProblemBruteForce(const Graph &graph) {
  checkGraph(graph);
  TsmResult res;
  std::vector<int> tempVertices;
  std::vector<int> shortestVertices;
  int source = 0;
  for (int i = 1; i < graph.getSize(); i++) {
    tempVertices.push_back(i);
  }
  int shortestPath = INT_MAX;

  while (next_permutation(tempVertices.begin(), tempVertices.end())) {
    int pathWeight = 0;
    int j = source;
    shortestVertices = {};
    shortestVertices.push_back(1);
    for (size_t i = 0; i < tempVertices.size(); i++) {
      pathWeight += graph.getData()(j, tempVertices[i]);
      j = tempVertices[i];
      shortestVertices.push_back(j + 1);
    }
    pathWeight += graph.getData()(j, source);
    if (shortestPath > pathWeight) {
      shortestPath = pathWeight;
      res.vertices = shortestVertices;
    }
  }
  res.distance = shortestPath;
  return res;
}

std::vector<std::pair<double, double>> GraphAlgorithms::comparasing(const Graph &graph, int N) {
  checkGraph(graph);
  checkGraphsSymmetric(graph);
  std::vector<std::pair<double, double>> runtime;
  TsmResult result;
  ACO algo_one;
  SimulatedAnnealing algo_two(graph);

  // aco algorithm start
  double start = std::clock();
  for (int i = 0; i < N; i++) {
    algo_one.TSPSolve(graph);
    result = algo_one.TSPSolve(graph);
  }
  double end = std::clock();
  double runtime_one = (end - start) / CLOCKS_PER_SEC;
  runtime.push_back({result.distance, runtime_one});

  // sa algorithm start
  start = std::clock();
  for (int i = 0; i < N; i++) {
    result = algo_two.SA_TSPSolve();
  }
  end = std::clock();
  double runtime_two = (end - start) / CLOCKS_PER_SEC;
  runtime.push_back({result.distance, runtime_two});

  // bf algorithm start
  start = std::clock();
  for (int i = 0; i < N; i++) {
    result = solveTravelingSalesmanProblemBruteForce(graph);
  }
  end = std::clock();
  double runtime_three = (end - start) / CLOCKS_PER_SEC;
  runtime.push_back({result.distance, runtime_three});

  return runtime;
}

}  // namespace s21
