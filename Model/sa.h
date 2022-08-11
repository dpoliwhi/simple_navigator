#pragma once

#include <math.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>
#include <random>
#include <vector>

#include "bits/stdc++.h"
#include "s21_graph.h"
#include "aco.h"

namespace s21 {

const double SPEED = 0.9;         // Скорость отжига
const double INITIAL_TEMP = 1000;  // Начальная температура

class SimulatedAnnealing {
 private:
  Matrix graphData;
  int nCities;
  std::vector<int> generate();
  TsmResult getNewSolution(TsmResult p);
  double CalCulate_length(TsmResult p);
  bool Accept(const TsmResult &bestone, const TsmResult &temp, double t);
  int randomChoose(int max);

 public:
  explicit SimulatedAnnealing(const Graph &graph);
  TsmResult SA_TSPSolve();
};

}  // namespace s21
