#pragma once

#include <iostream>

#include "../Model/s21_graph.h"
#include "../Model/s21_graph_algorithms.h"

namespace s21 {

class ConsoleInterface {
 public:
  void startProgram();

 private:
  void informationPart();
  void fileReading();
  void saveToDot();
  void algorithmMenu();
  void menuText();
  void menuOrExit();

  void DepthBreadthFirstSearch(int choice);
  void DijkstrasAlgorithm();
  void FloydWarshallPrimAlgorithm(int choice);
  void AntColonyOptimization();
  void printVector(std::vector<int> path);
  void printMatrix(s21::Matrix res);
  void Comparasing();

  Graph mainGraph;
  GraphAlgorithms algorithms;

  std::string end = "\u001b[0m";
  std::string end1 = "\u001b[0m\n";
  std::string style1 = "\u001b[1;38;5;117m";
  std::string style2 = "\u001b[1;48;5;25;38;5;117m";
  std::string style3 = "\u001b[1;48;5;117;38;5;25m";
  std::string style4 = "\u001b[1;38;5;117m";
};

}  // namespace s21
