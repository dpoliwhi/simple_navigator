#include "sa.h"

namespace s21 {

SimulatedAnnealing::SimulatedAnnealing(const Graph &graph) : graphData(graph.getData()) {
  nCities = graph.getSize();
}

// метод генерации чисел

int SimulatedAnnealing::randomChoose(int max) {
  std::random_device rand_r;
  std::default_random_engine engine(rand_r());
  std::uniform_int_distribution<int> posRand(0, max);
  return posRand(engine);
}

// Случайно генерируем начальное решение, случайным образом выбираем начальную точку, чтобы построить путь
// по порядку

std::vector<int> SimulatedAnnealing::generate() {
  std::vector<int> result;
  int j = 0;
  int i = randomChoose(nCities - 1);
  while (j < nCities) {
    result.push_back(i);
    j++;
    i = (i + 1) % nCities;
  }
  return result;
}

// Метод генерирует индексы соседей, и меняет их местами

TsmResult SimulatedAnnealing::getNewSolution(TsmResult p) {
  int i = randomChoose(nCities - 1);
  int j = randomChoose(nCities - 1);
  std::swap(p.vertices[i], p.vertices[j]);
  return p;
}

// Рассчитаем длину пути

double SimulatedAnnealing::CalCulate_length(TsmResult p) {
  double distance = 0;
  for (int i = 1; i < nCities; i++) {
    distance += graphData(p.vertices[i - 1], p.vertices[i]);
  }
  distance += graphData(p.vertices[nCities - 1], p.vertices[0]);  // Последний город к отправной точке
  return distance;
}

// Принять новые правила решения. Две ситуации

bool SimulatedAnnealing::Accept(const TsmResult &bestone, const TsmResult &temp, double t) {
  if (bestone.distance > temp.distance) {
    return true;
  } else {
    if ((int)(exp((bestone.distance - temp.distance) / t) * 100) > (randomChoose(100))) return true;
  }
  return false;
}

// Алгоритм имитации отжига ТСП

TsmResult SimulatedAnnealing::SA_TSPSolve() {
  double dec = SPEED;
  double t = INITIAL_TEMP;
  int L = nCities * 100;
  const double t_min = 0.01;
  TsmResult temp{{}, 0};
  TsmResult bestone{{}, 0};;
  temp.vertices = generate();
  temp.distance = CalCulate_length(temp);
  bestone = temp;
  while (t > t_min) {
    for (int i = 0; i < L; i++) {
      temp = getNewSolution(temp);
      temp.distance = CalCulate_length(temp);
      if (Accept(bestone, temp, t))
        bestone = temp;
      else
        temp = bestone;
    }
    t *= dec;  // отжиг
  }
  return bestone;
}

}  // namespace s21
