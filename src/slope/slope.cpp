#include "fit_slope.h"

namespace slope {

Results
slope(const Eigen::MatrixXd& x,
      const Eigen::MatrixXd& y,
      Eigen::ArrayXd alpha = Eigen::ArrayXd::Zero(0),
      Eigen::ArrayXd lambda = Eigen::ArrayXd::Zero(0),
      const SlopeParameters& params = SlopeParameters())
{
  return fitSlope(x, y, alpha, lambda, params);
}

Results
slope(const Eigen::SparseMatrix<double>& x,
      const Eigen::MatrixXd& y,
      Eigen::ArrayXd alpha = Eigen::ArrayXd::Zero(0),
      Eigen::ArrayXd lambda = Eigen::ArrayXd::Zero(0),
      const SlopeParameters& params = SlopeParameters())
{
  return fitSlope(x, y, alpha, lambda, params);
}

}
