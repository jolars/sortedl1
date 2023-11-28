#include "regularization_sequence.h"
#include "math.h"
#include "qnorm.h"
#include <Eigen/Core>

namespace slope {

Eigen::ArrayXd
lambdaSequence(const int p, const double q)
{
  Eigen::ArrayXd lambda_sequence(p);

  for (int j = 0; j < p; ++j) {
    lambda_sequence[j] = normalQuantile(1.0 - (j + 1.0) * q / (2.0 * p));
  }

  return lambda_sequence;
}

} // namespace slope
