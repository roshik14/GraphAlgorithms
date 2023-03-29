#ifndef S21_RANDOM_H_
#define S21_RANDOM_H_

#include <random>

namespace s21 {

class Random {
 public:
  double Next(double min, double max);
  int Next(int min, int max);

 private:
  std::random_device rd_;
  std::default_random_engine rand_engine_{rd_()};
};

}  // namespace s21

#endif  // S21_RANDOM_H_
