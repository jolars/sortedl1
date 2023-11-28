#pragma once

#include "clusters.h"
#include <Eigen/Core>

namespace slope {

struct ThresholdingResults
{
  const double value;
  const int new_index;
};

ThresholdingResults
slopeThreshold(const double x,
               const int j,
               const Eigen::ArrayXd lambdas,
               const Clusters& clusters);

}
