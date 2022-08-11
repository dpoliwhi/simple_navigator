#pragma once

#include <fstream>
#include <string>
#include <vector>

#include "../Matrix/matrix.h"

namespace s21 {

enum direction { undirected = 0, directed };
enum weight { unweighted = 0, weighted };

class Graph {
 private:
  struct graphData {
    Matrix _matrix;
    int _size;
    direction _directionType = undirected;
    weight _weightType = unweighted;
  } data;

  bool parsingSize(std::string line);
  std::pair<std::vector<int>, bool> parsingLine(std::string line);
  bool checkSizeData();
  void checkTypeGraph();

 public:
  Graph() {data._size = 0;}
  ~Graph() {}
  void loadGraphFromFile(const std::string& fileName);
  void exportGraphToDot(const std::string& fileName);
  void clearDataFile();

  // getters
  Matrix getData() const { return data._matrix; }
  int getSize() const { return data._size; }
  direction getDirectionType() const { return data._directionType; }
  weight getWeightType() const { return data._weightType; }

  // additionals
  void printData();
};

}  // namespace s21
