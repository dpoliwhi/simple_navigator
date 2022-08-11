#include "s21_graph.h"

namespace s21 {

void Graph::loadGraphFromFile(const std::string& fileName) {
  std::ifstream file(fileName);
  std::string line;
  if (!file.is_open()) {
    throw std::invalid_argument("No such file!");
  } else {
    int k = 0;
    bool isOpen = true;
    int countLines = 0;
    while (getline(file, line) && isOpen) {
      if (countLines == 0) {
        isOpen = parsingSize(line);
        if (!isOpen) {
          throw std::invalid_argument("Wrong matrix size");
        } else {
          data._matrix = Matrix(data._size, data._size);
        }
      } else {
        std::pair<std::vector<int>, bool> oneLine = parsingLine(line);
        isOpen = oneLine.second;
        if (isOpen) {
          for (int i = 0; i < data._size; i++) {
            data._matrix(k, i) = oneLine.first[i];
          }
          k++;
        } else {
          throw std::invalid_argument("Invalid data in file");
        }
      }
      countLines++;
    }
    file.close();
    if (countLines != data._size + 1) {
      throw std::invalid_argument("Invalid data in file");
    }
  }
  checkTypeGraph();
}

std::pair<std::vector<int>, bool> Graph::parsingLine(std::string line) {
  std::vector<int> oneLine;
  std::string buffer;
  bool isValid = true;
  std::string::iterator iter(line.begin());
  while (iter != line.end()) {
    if (isdigit(*iter)) {
      buffer.push_back(*iter);
      if ((iter + 1) == line.end() || ((*(iter + 1) == ' '))) {
        oneLine.push_back(atoi(buffer.c_str()));
        buffer.clear();
      }
      ++iter;
    } else if (*iter == ' ') {
      ++iter;
    } else {
      isValid = false;
      break;
    }
  }
  if ((int)oneLine.size() != data._size) {
    isValid = false;
  }
  return {oneLine, isValid};
}

bool Graph::parsingSize(std::string line) {
  bool isCoorectSize = true;
  std::string buffer;
  std::string::iterator iter(line.begin());
  while (iter != line.end()) {
    if (isdigit(*iter)) {
      buffer.push_back(*iter);
      ++iter;
    } else {
      isCoorectSize = false;
      break;
    }
  }
  int sizeTocheck = atoi(buffer.c_str());
  if (isCoorectSize && sizeTocheck > 0) {
    data._size = sizeTocheck;
  }
  return isCoorectSize;
}

void Graph::checkTypeGraph() {
  for (int i = 0; i < data._size; i++) {
    for (int j = 0; j < data._size; j++) {
      if (data._matrix(i, j) > 1) data._weightType = weighted;
      if (data._matrix(i, j) != data._matrix(j, i)) data._directionType = directed;
    }
  }
}

void Graph::exportGraphToDot(const std::string& fileName) {
  std::string fileWithPass = "Graphs/" + fileName;
  std::ofstream file(fileWithPass);
  Matrix temp(data._size, data._size);
  temp = data._matrix;
  std::string type, typeName;
  if (data._directionType == undirected) {
    type = "--";
    typeName = "graph";
  } else {
    type = "->";
    typeName = "digraph";
  }

  file << typeName << " ourgraph {" << std::endl;
  for (int i = 0; i < data._size; i++) {
    for (int j = 0; j < data._size; j++) {
      if (temp(i, j) > 0) {
        file << "\t" << i + 1 << " "
             << type
             << " " << j + 1;
        file << " [label = "
             << "\"" << temp(i, j) << "\"];" << std::endl;
      }
      if (temp(j, i) != 0) temp(j, i) = 0;
    }
  }
  file << "}";
}

void Graph::clearDataFile() {
  data._directionType = undirected;
  data._weightType = unweighted;
  data._size = 0;
}

// additional
void Graph::printData() {
  data._directionType ? std::cout << "directed\n" : std::cout << "undirected\n";
  data._weightType ? std::cout << "weighted\n" : std::cout << "unweighted\n";
  std::cout << "size = " << data._size << std::endl;
  for (int i = 0; i < data._matrix.getRows(); i++) {
    for (int j = 0; j < data._matrix.getCols(); j++) std::cout << data._matrix(i, j) << " ";
    std::cout << std::endl;
  }
}
}  // namespace s21
