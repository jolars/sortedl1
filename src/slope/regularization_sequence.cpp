#include "regularization_sequence.h"
#include "qnorm.h"
#include <cassert>

namespace slope {

Eigen::ArrayXd
lambdaSequence(const int p, const double q, const std::string& type)
{
  Eigen::ArrayXd lambda(p);

  if (type == "bh") {
    if (q < 0 || q > 1) {
      throw std::invalid_argument("q must be between 0 and 1");
    }

    for (int j = 0; j < p; ++j) {
      lambda[j] = normalQuantile(1.0 - (j + 1.0) * q / (2.0 * p));
    }
  }

  assert(lambda.minCoeff() > 0);

  return lambda;
}

} // namespace slope
