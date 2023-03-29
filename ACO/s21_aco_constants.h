#ifndef S21_ACO_CONSTANTS_H_
#define S21_ACO_CONSTANTS_H_

#include <cstddef>

namespace s21 {
class ACO_Constants {
 public:
  static constexpr size_t kIterationsCount = 10;
  static constexpr double kQ = 10.0;
  static constexpr double kTau0 = 0.5;
  static constexpr double kRho = 0.01;
  static constexpr double kAlpha = 1.0;
  static constexpr double kBeta = 5.0;
};
}  // namespace s21

#endif  // S21_ACO_CONSTANTS_H_
