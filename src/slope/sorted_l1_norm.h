#pragma once

#include "math.h"
#include "utils.h"
#include <Eigen/Core>

namespace slope {

class SortedL1Norm
{
private:
  double alpha = 1.0;

public:
  const Eigen::ArrayXd lambda;

  SortedL1Norm(const Eigen::ArrayXd& lambda);

  double eval(const Eigen::VectorXd& beta) const;

  template<typename T>
  double dual(const T& x, const Eigen::VectorXd& theta) const
  {
    Eigen::ArrayXd xt_theta_abs = (x.transpose() * theta).cwiseAbs();
    sort(xt_theta_abs, true);
    return (cumSum(xt_theta_abs) / cumSum((lambda * alpha).eval())).maxCoeff();
  }

  Eigen::VectorXd prox(const Eigen::VectorXd& beta, const double scale) const;

  Eigen::ArrayXd dualNorm(const Eigen::VectorXd& a) const;

  void setAlpha(const double new_alpha);

  double getAlpha() const;
};

}
