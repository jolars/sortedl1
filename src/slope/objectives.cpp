#include "objectives.h"
#include "math.h"

namespace slope {

double
Gaussian::loss(const Eigen::VectorXd& eta, const Eigen::MatrixXd& y)
{
  const int n = y.rows();
  return (eta - y.col(0)).squaredNorm() / (2.0 * n);
}

double
Gaussian::dual(const Eigen::VectorXd& theta, const Eigen::VectorXd& y)
{
  const int n = y.rows();
  return (y.squaredNorm() - (y - theta).squaredNorm()) / (2.0 * n);
}

Eigen::VectorXd
Gaussian::residual(const Eigen::VectorXd& eta, const Eigen::VectorXd& y)
{
  return y - eta;
}

void
Gaussian::updateWeightsAndWorkingResponse(Eigen::VectorXd& w,
                                          Eigen::VectorXd& z,
                                          const Eigen::VectorXd& eta,
                                          const Eigen::MatrixXd& y)
{
  w.setOnes();
  z = y;
}

double
Binomial::loss(const Eigen::VectorXd& eta, const Eigen::MatrixXd& y)
{
  double loss = eta.array().exp().log1p().sum() - y.col(0).dot(eta);
  return loss / y.rows();
}

double
Binomial::dual(const Eigen::VectorXd& theta, const Eigen::VectorXd& y)
{
  using Eigen::log;

  const int n = y.rows();

  Eigen::ArrayXd r = theta.array() / y.array();

  return (((r - 1.0) * log(1.0 - r)).sum() - (r * log(r)).sum()) / n;
}

Eigen::VectorXd
Binomial::residual(const Eigen::VectorXd& eta, const Eigen::VectorXd& y)
{
  return y.array() / (1.0 + y.cwiseProduct(eta).array().exp());
}

void
Binomial::updateWeightsAndWorkingResponse(Eigen::VectorXd& w,
                                          Eigen::VectorXd& z,
                                          const Eigen::VectorXd& eta,
                                          const Eigen::MatrixXd& y)
{
  for (int i = 0; i < eta.size(); ++i) {
    double p_i = sigmoid(eta(i));
    p_i = clamp(p_i, p_min, 1.0 - p_min);
    w(i) = p_i * (1.0 - p_i);
    z(i) = eta(i) + (y(i) - p_i) / w(i);
  }
}

std::unique_ptr<Objective>
setupObjective(const std::string family)
{
  if (family == "binomial")
    return std::make_unique<Binomial>();

  // else Gaussian
  return std::make_unique<Gaussian>();
}

}
