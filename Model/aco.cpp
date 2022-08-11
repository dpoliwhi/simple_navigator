#include "aco.h"

namespace s21 {

double randomChoose(int max) {
  std::random_device rand_r;
  std::default_random_engine engine(rand_r());
  std::uniform_int_distribution<int> posRand(0, max);
  return posRand(engine);
}

Ant::Ant(Matrix data, Matrix phm, int startPos) : graphData(data), pheromones(phm), startPosition(startPos) {
  sizeOfMap = data.getRows();
  position = startPos;
  result.distance = 0;
}

void Ant::initTabu() {
  for (int i = 0; i < sizeOfMap; i++) {
    tabu.push_back(true);
    if (i == startPosition) {
      tabu[i] = false;
    }
  }
}

std::vector<int> Ant::availableWays() {
  std::vector<int> result;
  for (int i = 0; i < sizeOfMap; i++) {
    if (graphData(position, i) != 0 && tabu[i]) {
      result.push_back(i);
    }
  }
  return result;
}

double Ant::getDistance(int from, int to) { return graphData(from, to); }

void Ant::nestProbability(const std::vector<int>& aw) {
  double prevProb = 0;
  probability.clear();
  for (size_t i = 0; i < aw.size(); i++) {
    prevProb += calcProbability(aw, position, aw[i]);
    probability.insert({aw[i], prevProb});
  }
}

double Ant::calcProbability(const std::vector<int>& avalibleWays, int from, int to) {
  double ita = pow(1 / getDistance(from, to), kBeta);
  double teta = pow(pheromones(from, to), kAlpha);
  double probability = 100 * ita * teta;
  double divisor = 0;
  for (size_t i = 0; i < avalibleWays.size(); i++) {
    divisor += pow(1 / getDistance(from, avalibleWays.at(i)), kBeta) *
               pow(pheromones(from, avalibleWays.at(i)), kAlpha);
  }
  return probability / divisor;
}

void Ant::chooseWay() {
  if (probability.size() == 1) {
    position = probability.begin()->first;
    return;
  }
  double random = randomChoose(99);
  for (auto it = probability.begin(); it != probability.end(); ++it) {
    if (random <= it->second) {
      position = it->first;
      break;
    }
  }
}

void Ant::updateTabu() {
  for (size_t i = 0; i < tabu.size(); i++) {
    if (i == (size_t)position) tabu[i] = false;
  }
}

void Ant::updateTabuLastTime() {
  for (size_t i = 0; i < tabu.size(); i++) {
    if (i == (size_t)startPosition) tabu[i] = true;
  }
}

void Ant::runAnt() {
  initTabu();
  for (int i = 0; i < graphData.getCols(); i++) {
    int prevPos, curPos;
    prevPos = position;
    result.vertices.push_back(position);
    if (i == graphData.getCols() - 1) {
      updateTabuLastTime();
    }
    updateTabu();
    std::vector<int> aw = availableWays();
    nestProbability(aw);
    chooseWay();
    curPos = position;
    result.distance += getDistance(prevPos, curPos);
  }
  checkRun();
}

TsmResult Ant::getTrip() { return result; }

void Ant::checkRun() {
  if (position != startPosition) result.distance = INFINITY;
  int count = 0;
  for (size_t i = 0; i < tabu.size(); i++) {
    if (tabu[i]) count++;
  }
  if (count > 1) result.distance = INFINITY;
}

void ACO::createPheromones(const Graph& graph) {
  pheromones = graph.getData();
  for (int i = 0; i < graph.getSize(); i++) {
    for (int j = 0; j < graph.getSize(); j++) {
      if (pheromones(i, j) != 0) {
        pheromones(i, j) = kPheromone0;
      } else {
        pheromones(i, j) = 0;
      }
    }
  }
}

void ACO::createAnts(const Matrix& graphData) {
  for (int i = 0; i < graphData.getCols(); i++) {
    int startPosition = randomChoose(graphData.getCols() - 1);
    ants.push_back(new Ant(graphData, pheromones, startPosition));
  }
}

void ACO::upadateTsmResult(const TsmResult& oneResult) {
  if (resultACO.distance > oneResult.distance) {
    resultACO.distance = oneResult.distance;
    resultACO.vertices.clear();
    resultACO.vertices = oneResult.vertices;
    runsCount = 0;  // обнуляем счетчик проходок для большего кол-ва проходок и нахождения лучшей длины
  }
}

Matrix ACO::updatePheromonesOneRun(const TsmResult& oneResult, Matrix curPheromones) {
  double deltaTeta = kQ / oneResult.distance;
  for (size_t i = 0; i < oneResult.vertices.size() - 1; i++) {
    curPheromones(oneResult.vertices[i], oneResult.vertices[i + 1]) += deltaTeta;
  }
  return curPheromones;
}

void ACO::groupRun() {
  for (size_t i = 0; i < ants.size(); i++) {
    ants[i]->runAnt();
    pheromones = updatePheromonesOneRun(ants[i]->getTrip(), pheromones);
    upadateTsmResult(ants[i]->getTrip());
  }
}

void ACO::deleteAnts() {
  for (size_t i = 0; i < ants.size(); i++) {
    delete ants[i];
  }
  ants.clear();
}

void ACO::decreacePheromones() { pheromones *= (1 - kPheromoneEvaporation); }

TsmResult ACO::TSPSolve(const Graph& graph) {
  createPheromones(graph);
  while (runsCount < kRunCountMAX) {
    createAnts(graph.getData());
    groupRun();
    decreacePheromones();
    deleteAnts();
    runsCount++;
  }
  return resultACO;
}

}  // namespace s21
