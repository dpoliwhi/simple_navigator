#pragma once

#include <iostream>
#include <limits>
#include <map>
#include <random>
#include <vector>

#include "s21_graph.h"

namespace s21 {

struct TsmResult {
  std::vector<int> vertices;  // массив с искомым маршрутом (с порядком обхода вершин).
  double distance;  // длина этого маршрута
};

const double kAlpha = 1.0;  // выбор пути относительно остатка феромонов
const double kBeta = 1.0;   // выбор пути относительно дальности пути
const double kPheromone0 = 0.5;            // начальное значение феромонов
const double kPheromoneEvaporation = 0.5;  // коэффициент испарения феромонов
const double kQ = 1.0;                     // коэффициент увеличения феромонов
const int kRunCountMAX = 20;  // количество проходок групп муравьев по карте

double randomChoose(int max);

class Ant {
 private:
  int sizeOfMap;
  int position{0};
  Matrix graphData;
  Matrix pheromones;
  int startPosition{0};

  std::vector<bool> tabu;
  std::vector<int> availableWays();
  std::map<int, double> probability;
  TsmResult result;

  void initTabu();
  void updateTabu();
  void updateTabuLastTime();
  void chooseWay();
  void nestProbability(const std::vector<int>& avalibleWays);
  double calcProbability(const std::vector<int>& avalibleWays, int from, int to);
  double getDistance(int from, int to);
  void checkRun();

 public:
  Ant(Matrix data, Matrix phm, int startPos);
  void runAnt();
  TsmResult getTrip();
};

class ACO {
 private:
  int runsCount = 0;  // счетчик для кол-ва проходок. Обнуляется при каждом нахождении меньшего пути
  TsmResult resultACO;
  Matrix pheromones;
  std::vector<Ant*> ants;

  void createAnts(const Matrix& graphData);
  void deleteAnts();
  void groupRun();
  void createPheromones(const Graph& graph);
  Matrix updatePheromonesOneRun(const TsmResult& oneResult, Matrix curPheromones);
  void decreacePheromones();
  void upadateTsmResult(const TsmResult& oneResult);

 public:
  ACO() {
    resultACO.distance = INFINITY;
    resultACO.vertices = {};
  }
  ~ACO() {}
  TsmResult TSPSolve(const Graph& graph);
};
}  // namespace s21
