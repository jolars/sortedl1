#include "standardize.h"

namespace slope {

std::tuple<double, Eigen::VectorXd>
rescaleCoefficients(double beta0,
                    Eigen::VectorXd beta,
                    const Eigen::VectorXd& x_centers,
                    const Eigen::VectorXd& x_scales,
                    const SlopeParameters& params)
{
  const int p = beta.rows();

  double x_bar_beta_sum = 0;

  if (params.standardize) {
    for (int j = 0; j < p; ++j) {
      beta(j) /= x_scales(j);
      x_bar_beta_sum += x_centers(j) * beta(j);
    }

    if (params.intercept) {
      beta0 -= x_bar_beta_sum;
    }
  }

  return { beta0, beta };
}

} // namespace slope
