#include <gtest/gtest.h>

#include "Containers/s21_stack.h"
#include "Model/s21_graph.h"
#include "Model/s21_graph_algorithms.h"

// open graph
TEST(test_s21_Graph, openGraph) {
  s21::Graph one;
  one.loadGraphFromFile("datasets/1.txt");
  ASSERT_EQ(one.getSize(), 11);
  ASSERT_EQ(one.getDirectionType(), 0);
}

TEST(test_s21_Graph, openGraph1) {
  s21::Graph one;
  one.loadGraphFromFile("datasets/2.txt");
  ASSERT_EQ(one.getSize(), 5);
  ASSERT_EQ(one.getDirectionType(), 1);
}

TEST(test_s21_Graph, openGraph2) {
  s21::Graph one;
  ASSERT_ANY_THROW(one.loadGraphFromFile("datasets/error_1.txt"););
}

TEST(test_s21_Graph, openGraph3) {
  s21::Graph one;
  ASSERT_ANY_THROW(one.loadGraphFromFile("datasets/somefile.txt"););
}

TEST(test_s21_Graph, saveGraph) {
  s21::Graph one;
  one.loadGraphFromFile("datasets/2.txt");
  one.exportGraphToDot("2.dot");
  SUCCEED();
}

TEST(test_s21_GraphAlgorithms, depthFirstSearch) {
  s21::Graph one;
  s21::GraphAlgorithms algo;
  std::vector<int> res = {1, 2, 3, 4, 5};
  one.loadGraphFromFile("datasets/2.txt");
  std::vector<int> path = algo.depthFirstSearch(one, 1);
  ASSERT_EQ(res, path);
}

TEST(test_s21_GraphAlgorithms, depthFirstSearch1) {
  s21::Graph one;
  s21::GraphAlgorithms algo;
  std::vector<int> res = {5, 1, 2, 3, 4, 6, 7, 8, 9, 10, 11};
  one.loadGraphFromFile("datasets/1.txt");
  std::vector<int> path = algo.depthFirstSearch(one, 5);
  ASSERT_EQ(res, path);
}

TEST(test_s21_GraphAlgorithms, depthFirstSearch2) {
  s21::Graph one;
  s21::GraphAlgorithms algo;
  one.loadGraphFromFile("datasets/1.txt");
  ASSERT_ANY_THROW(std::vector<int> path = algo.depthFirstSearch(one, 0););
}

TEST(test_s21_GraphAlgorithms, breadthFirstSearch) {
  s21::Graph one;
  s21::GraphAlgorithms algo;
  std::vector<int> res = {1, 2, 3, 5, 4};
  one.loadGraphFromFile("datasets/2.txt");
  std::vector<int> path = algo.breadthFirstSearch(one, 1);
  ASSERT_EQ(res, path);
}

TEST(test_s21_GraphAlgorithms, breadthFirstSearch1) {
  s21::Graph one;
  s21::GraphAlgorithms algo;
  std::vector<int> res = {3, 1, 6, 2, 4, 5, 7};
  one.loadGraphFromFile("datasets/5.txt");
  std::vector<int> path = algo.breadthFirstSearch(one, 3);
  ASSERT_EQ(res, path);
}

TEST(test_s21_GraphAlgorithms, breadthFirstSearch2) {
  s21::Graph one;
  s21::GraphAlgorithms algo;
  one.loadGraphFromFile("datasets/5.txt");
  ASSERT_ANY_THROW(std::vector<int> path = algo.depthFirstSearch(one, 8););
}

TEST(test_s21_GraphAlgorithms, getShortestPathBetweenVertices) {
  s21::Graph one;
  s21::GraphAlgorithms algo;
  one.loadGraphFromFile("datasets/1.txt");
  int distance = algo.getShortestPathBetweenVertices(one, 7, 1);
  ASSERT_EQ(distance, 100);
}

TEST(test_s21_GraphAlgorithms, getShortestPathBetweenVertices1) {
  s21::Graph one;
  s21::GraphAlgorithms algo;
  one.loadGraphFromFile("datasets/5.txt");
  int distance = algo.getShortestPathBetweenVertices(one, 1, 7);
  ASSERT_EQ(distance, 5);
}

TEST(test_s21_GraphAlgorithms, getShortestPathBetweenVertices2) {
  s21::Graph one;
  s21::GraphAlgorithms algo;
  one.loadGraphFromFile("datasets/5.txt");
  ASSERT_ANY_THROW(algo.getShortestPathBetweenVertices(one, 13, 7););
}

TEST(test_s21_GraphAlgorithms, getShortestPathsBetweenAllVertices) {
  s21::Graph one;
  s21::GraphAlgorithms algo;
  one.loadGraphFromFile("datasets/1.txt");
  int res[11][11] = { 0, 29, 20, 20, 16, 31, 100, 12, 4, 31, 18, 
                      29, 0, 15, 29, 28, 40, 72, 21, 29, 41, 12, 
                      20, 15, 0, 15, 14, 25, 81, 9, 23, 27, 13, 
                      20, 29, 15, 0, 4, 12, 92, 12, 24, 13, 25, 
                      16, 28, 14, 4, 0, 16, 94, 9, 20, 16, 22, 
                      31, 40, 25, 12, 16, 0, 95, 24, 35, 3, 37, 
                      100, 72, 81, 92, 94, 95, 0, 90, 101, 98, 84, 
                      12, 21, 9, 12, 9, 24, 90, 0, 15, 25, 13, 
                      4, 29, 23, 24, 20, 35, 101, 15, 0, 35, 18, 
                      31, 41, 27, 13, 16, 3, 98, 25, 35, 0, 38, 
                      18, 12, 13, 25, 22, 37, 84, 13, 18, 38, 0};
  s21::Matrix matrix = algo.getShortestPathsBetweenAllVertices(one);
  for (int i = 0; i < 11; i++)
    for (int j = 0; j < 11; j++)
      ASSERT_EQ(matrix(i, j), res[i][j]);
}

TEST(test_s21_GraphAlgorithms, getShortestPathsBetweenAllVertices1) {
  s21::Graph one;
  s21::GraphAlgorithms algo;
  one.loadGraphFromFile("datasets/2.txt");
  int res[5][5] = { 0, 1, 1, 2, 1, 
                    0, 0, 0, 0, 0, 
                    0, 0, 0, 1, 2, 
                    0, 0, 0, 0, 1, 
                    0, 0, 0, 0, 0};
  s21::Matrix matrix = algo.getShortestPathsBetweenAllVertices(one);
  for (int i = 0; i < 5; i++)
    for (int j = 0; j < 5; j++)
      ASSERT_EQ(matrix(i, j), res[i][j]);
}

TEST(test_s21_GraphAlgorithms, getLeastSpanningTree) {
  s21::Graph one;
  s21::GraphAlgorithms algo;
  one.loadGraphFromFile("datasets/1.txt");
  int res[11][11] = { 0, 0, 0, 0, 0, 0, 0, 12, 4, 0, 0, 
                      0, 0, 0, 0, 0, 0, 72, 0, 0, 0, 12, 
                      0, 0, 0, 0, 0, 0, 0, 9, 0, 0, 13, 
                      0, 0, 0, 0, 4, 12, 0, 0, 0, 0, 0, 
                      0, 0, 0, 4, 0, 0, 0, 9, 0, 0, 0, 
                      0, 0, 0, 12, 0, 0, 0, 0, 0, 3, 0, 
                      0, 72, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
                      12, 0, 9, 0, 9, 0, 0, 0, 0, 0, 0,
                      4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
                      0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 
                      0, 12, 13, 0, 0, 0, 0, 0, 0, 0, 0};
  s21::Matrix matrix = algo.getLeastSpanningTree(one);
  for (int i = 0; i < 11; i++)
    for (int j = 0; j < 11; j++)
      ASSERT_EQ(matrix(i, j), res[i][j]);
}

TEST(test_s21_GraphAlgorithms, getLeastSpanningTree1) {
  s21::Graph one;
  s21::GraphAlgorithms algo;
  one.loadGraphFromFile("datasets/2.txt");
  ASSERT_ANY_THROW(s21::Matrix matrix = algo.getLeastSpanningTree(one));
}

TEST(test_s21_GraphAlgorithms, solveTravelingSalesmanProblem) {
  s21::Graph one;
  s21::GraphAlgorithms algo;
  one.loadGraphFromFile("datasets/6.txt");
  s21::TsmResult res = algo.solveTravelingSalesmanProblem(one);
  ASSERT_EQ(res.distance, 80);
}

TEST(test_s21_GraphAlgorithms, solveTravelingSalesmanProblem2) {
  s21::Graph one;
  s21::GraphAlgorithms algo;
  one.loadGraphFromFile("datasets/2.txt");
  ASSERT_ANY_THROW(s21::TsmResult res = algo.solveTravelingSalesmanProblem(one););
}

TEST(test_s21_GraphAlgorithms, solveTravelingSalesmanProblemBruteForce1) {
  s21::Graph one;
  s21::GraphAlgorithms algo;
  one.loadGraphFromFile("datasets/6.txt");
  s21::TsmResult res = algo.solveTravelingSalesmanProblemBruteForce(one);
  ASSERT_EQ(res.distance, 80);
}

TEST(test_s21_GraphAlgorithms, solveTravelingSalesmanProblemBruteForce2) {
  s21::Graph one;
  s21::GraphAlgorithms algo;
  one.loadGraphFromFile("datasets/2.txt");
  ASSERT_ANY_THROW(s21::TsmResult res = algo.solveTravelingSalesmanProblemBruteForce(one););
}

TEST(test_s21_GraphAlgorithms, solveTravelingSalesmanProblemSA) {
  s21::Graph one;
  s21::GraphAlgorithms algo;
  one.loadGraphFromFile("datasets/6.txt");
  s21::TsmResult res = algo.solveTravelingSalesmanProblem_SA(one);
  ASSERT_EQ(res.distance, 80);
}

TEST(test_s21_GraphAlgorithms, solveTravelingSalesmanProblemSA2) {
  s21::Graph one;
  s21::GraphAlgorithms algo;
  one.loadGraphFromFile("datasets/2.txt");
  ASSERT_ANY_THROW(s21::TsmResult res = algo.solveTravelingSalesmanProblem_SA(one););
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
