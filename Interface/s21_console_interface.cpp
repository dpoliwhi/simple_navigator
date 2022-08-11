#include "s21_console_interface.h"

#include <iostream>

namespace s21 {

void ConsoleInterface::startProgram() {
  informationPart();
  fileReading();
}

void ConsoleInterface::informationPart() {
  std::cout << style1 << "\n---------------------------------------------" << end << std::endl;
  std::cout << style2 << "         WELCOME TO SIMPLE NAVIGATOR         " << end << std::endl;
  std::cout << style1 << "---------------------------------------------" << end << std::endl;
  std::cout << style4 << "             program created  by" << end << std::endl;
  std::cout << style4 << "             dpoliwhi & esharika" << end << std::endl;
  std::cout << style1 << "---------------------------------------------" << end1 << std::endl;
}

void ConsoleInterface::fileReading() {
  while (true) {
    std::cout << style3 << " please enter file name                      " << end << std::endl;
    std::cout << std::endl;
    std::string filename;
    std::cin >> filename;
    try {
      mainGraph.clearDataFile();
      mainGraph.loadGraphFromFile("datasets/" + filename);
      break;
    } catch (std::exception &exceptionText) {
      std::cerr << style4 << "\nError: " << exceptionText.what() << end << "\n\n";
    }
  }
  algorithmMenu();
}

void ConsoleInterface::saveToDot() {
  std::cout << "\n" << style3 << " please enter file name to save              " << end1 << std::endl;
  std::string filename;
  std::cin >> filename;
  mainGraph.exportGraphToDot(filename);
  std::cout << "\n" << style3 << " file successfully saved in Graphs directory " << end1 << std::endl;
  std::cerr << style4 << "to create a png file\ninstall and use the graphViz utility\n" << end1;
  menuOrExit();
}

void ConsoleInterface::algorithmMenu() {
  menuText();
  int choice;
  std::cin >> choice;
  if (choice == 1 || choice == 2) {
    DepthBreadthFirstSearch(choice);
  } else if (choice == 3) {
    DijkstrasAlgorithm();
  } else if (choice == 4 || choice == 5) {
    FloydWarshallPrimAlgorithm(choice);
  } else if (choice == 6) {
    AntColonyOptimization();
  } else if (choice == 7) {
    Comparasing();
  } else if (choice == 8) {
    saveToDot();
  } else if (choice == 9) {
    fileReading();
  } else if (choice == 0) {
    return;
  } else {
    std::cout << style4 << "\nError: incorrect input, try again " << end << std::endl;
    algorithmMenu();
  }
}

void ConsoleInterface::DepthBreadthFirstSearch(int choice) {
  std::cout << style4 << "\nenter vertex number from 1 to " << mainGraph.getSize() << " to start search "
            << end1 << std::endl;
  int vertex;
  std::cin >> vertex;
  try {
    std::vector<int> path;
    if (choice == 1)
      path = algorithms.depthFirstSearch(mainGraph, vertex);
    else if (choice == 2)
      path = algorithms.breadthFirstSearch(mainGraph, vertex);
    printVector(path);
    menuOrExit();
  } catch (std::exception &exceptionText) {
    std::cerr << style4 << "\nError: " << exceptionText.what() << end << "\n";
    DepthBreadthFirstSearch(choice);
  }
}

void ConsoleInterface::DijkstrasAlgorithm() {
  std::cout << style4 << "\nenter the vertex number of the beginning of the path (from 1 to "
            << mainGraph.getSize() << ") to start search " << end1 << std::endl;
  int start;
  std::cin >> start;
  std::cout << style4 << "\nenter the vertex number of the end of the path (from 1 to " << mainGraph.getSize()
            << ") to start search " << end1 << std::endl;
  int finish;
  std::cin >> finish;
  try {
    int distance = algorithms.getShortestPathBetweenVertices(mainGraph, start, finish);
    std::cout << style4 << "\nDISTANCE: " << distance << end1 << std::endl;
    menuOrExit();
  } catch (std::exception &exceptionText) {
    std::cerr << style4 << "\nError: " << exceptionText.what() << end << "\n";
    DijkstrasAlgorithm();
  }
}

void ConsoleInterface::FloydWarshallPrimAlgorithm(int choice) {
  try {
    s21::Matrix res;
    if (choice == 4)
      res = algorithms.getShortestPathsBetweenAllVertices(mainGraph);
    else if (choice == 5)
      res = algorithms.getLeastSpanningTree(mainGraph);
    printMatrix(res);
    menuOrExit();
  } catch (std::exception &exceptionText) {
    std::cerr << style4 << "\nError: " << exceptionText.what() << end1 << "\n";
    menuOrExit();
  }
}

void ConsoleInterface::AntColonyOptimization() {
  try {
    s21::TsmResult res;
    res = algorithms.solveTravelingSalesmanProblem(mainGraph);
    printVector(res.vertices);
    std::cout << style4 << "DISTANCE: " << res.distance << end1 << std::endl;
    menuOrExit();
  } catch (std::exception &exceptionText) {
    std::cerr << style4 << "\nError: " << exceptionText.what() << end1 << "\n";
    menuOrExit();
  }
}

void ConsoleInterface::Comparasing() {
  try {
    std::cout << style4 << "\nenter how many times to keep track of the time (1 - 1000)" << end1 << std::endl;
    int N;
    std::cin >> N;
    std::vector<std::pair<double, double>> res;
    res = algorithms.comparasing(mainGraph, N);
    std::cout << std::fixed;
    std::cout << style4 << "1) Ant Colony Optimization Algoritm\n";
    std::cout << std::setprecision(5);
    std::cout << style4 << "RUNTIME: " << res[0].second;
    std::cout << std::setprecision(0);
    std::cout << style4 << "sec  DISTANCE: " << res[0].first << end1 << std::endl;
    std::cout << style4 << "2) Simulated Annealing Algoritm\n";
    std::cout << std::setprecision(5);
    std::cout << style4 << "RUNTIME: " << res[1].second;
    std::cout << std::setprecision(0);
    std::cout << style4 << "sec  DISTANCE: " << res[1].first << end1 << std::endl;
    std::cout << style4 << "3) Brute Force Algoritm\n";
    std::cout << std::setprecision(5);
    std::cout << style4 << "RUNTIME: " << res[2].second;
    std::cout << std::setprecision(0);
    std::cout << style4 << "sec  DISTANCE: " << res[2].first << end1 << std::endl;
    menuOrExit();
  } catch (std::exception &exceptionText) {
    std::cerr << style4 << "\nError: " << exceptionText.what() << end1 << "\n";
    menuOrExit();
  }
}

void ConsoleInterface::printVector(std::vector<int> path) {
  std::cout << style4 << "\nPATH: ";
  for (size_t i = 0; i < path.size(); i++) {
    std::cout << path[i] << " ";
  }
  std::cout << "\n" << end1;
}

void ConsoleInterface::printMatrix(s21::Matrix res) {
  std::cout << style4 << "\nMATRIX:\n";
  for (int i = 0; i < res.getRows(); i++) {
    for (int j = 0; j < res.getCols(); j++) {
      std::cout << res(i, j);
      if (res(i, j) < 10)
        std::cout << "   ";
      else if (res(i, j) >= 10 && res(i, j) < 100)
        std::cout << "  ";
      else
        std::cout << " ";
    }
    std::cout << std::endl;
  }
  std::cout << "\n" << end;
}

void ConsoleInterface::menuOrExit() {
  std::cout << style3 << " to return to the menu press 1               " << end << std::endl;
  std::cout << style3 << " to exit the program press 0                 " << end1 << std::endl;
  int choice;
  std::cin >> choice;
  if (choice == 1) {
    algorithmMenu();
  } else if (choice == 0) {
    return;
  } else {
    std::cout << style4 << "\nError: incorrect input, try again " << end << std::endl;
    menuOrExit();
  }
}

void ConsoleInterface::menuText() {
  std::cout << style1 << "---------------------------------------------" << end << std::endl;
  std::cout << style2 << "               ALGORITHMS MENU               " << end << std::endl;
  std::cout << style1 << "---------------------------------------------" << end1 << std::endl;
  std::cout << style3 << " 1. Depth-first search                       " << end << std::endl;
  std::cout << style3 << " 2. Breadth-first search                     " << end << std::endl;
  std::cout << style3 << " 3. Dijkstra's algorithm                     " << end << std::endl;
  std::cout << style3 << " 4. Floyd-Warshall algorithm                 " << end << std::endl;
  std::cout << style3 << " 5. Prim's algorithm                         " << end << std::endl;
  std::cout << style3 << " 6. Ant colony algorithm                     " << end << std::endl;
  std::cout << style3 << " 7. Comparasing algorithms for TSP           " << end1 << std::endl;
  std::cout << style3 << " 8. Save graph to .dot                       " << end << std::endl;
  std::cout << style3 << " 9. Upload new file                          " << end << std::endl;
  std::cout << style3 << " 0. Exit from the program                    " << end1 << std::endl;
}

}  // namespace s21
