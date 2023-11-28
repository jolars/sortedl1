#pragma once

#include <Eigen/Sparse>
#include <vector>

namespace slope {

struct Results
{
  const Eigen::VectorXd beta0s;
  const Eigen::SparseMatrix<double> betas;
  const std::vector<double> primals;
};

} // namespace slope
