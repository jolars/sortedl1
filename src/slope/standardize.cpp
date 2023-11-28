#include "standardize.h"

namespace slope {

std::pair<Eigen::VectorXd, Eigen::VectorXd>
computeMeanAndStdDev(const Eigen::MatrixXd& x)
{
  const int n = x.rows();
  const int p = x.cols();

  Eigen::VectorXd x_means = x.colwise().mean();
  Eigen::VectorXd x_stddevs(p);

  for (int j = 0; j < p; ++j) {
    x_stddevs(j) =
      std::sqrt((x.col(j).array() - x_means(j)).square().sum() / n);
  }

  return { x_means, x_stddevs };
}

std::pair<Eigen::VectorXd, Eigen::VectorXd>
computeMeanAndStdDev(const Eigen::SparseMatrix<double>& x)
{
  const int n = x.rows();
  const int p = x.cols();

  Eigen::VectorXd x_means(p);
  Eigen::VectorXd x_stddevs(p);

  for (int j = 0; j < p; ++j) {
    x_means(j) = x.col(j).sum() / n;
    // TODO: Reconsider this implementation since it might overflow.
    x_stddevs(j) =
      std::sqrt(x.col(j).squaredNorm() / n - std::pow(x_means(j), 2));
  }

  return { x_means, x_stddevs };
}

std::pair<double, Eigen::VectorXd>
unstandardizeCoefficients(double beta0,
                          Eigen::VectorXd beta,
                          const Eigen::VectorXd& x_means,
                          const Eigen::VectorXd& x_stddevs,
                          const bool intercept)
{
  const int p = beta.rows();

  double x_bar_beta_sum = 0;

  for (int j = 0; j < p; ++j) {
    beta(j) /= x_stddevs(j);
    x_bar_beta_sum += x_means(j) * beta(j);
  }
  if (intercept) {
    beta0 -= x_bar_beta_sum;
  }

  return { beta0, beta };
}

}
