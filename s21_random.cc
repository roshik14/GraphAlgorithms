#include "s21_random.h"

using s21::Random;

double Random::Next(double min, double max) {
  std::uniform_real_distribution<double> dist{min, max};
  return dist(rand_engine_);
}

int Random::Next(int min, int max) {
  std::uniform_int_distribution<int> dist{min, max};
  return dist(rand_engine_);
}
