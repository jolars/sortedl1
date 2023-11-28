#include "sorted_l1_norm.h"

namespace slope {

SortedL1Norm::SortedL1Norm(const Eigen::ArrayXd& lambda)
  : lambda{ lambda }
{
}

double
SortedL1Norm::eval(const Eigen::VectorXd& beta) const
{
  Eigen::ArrayXd beta_abs = beta.array().abs();
  sort(beta_abs, true);
  return alpha * (beta_abs * lambda).sum();
}

Eigen::VectorXd
SortedL1Norm::prox(const Eigen::VectorXd& beta, const double scale) const
{
  using namespace Eigen;

  ArrayXd beta_sign = beta.array().sign();
  VectorXd beta_copy = beta.cwiseAbs().eval();

  auto ord = sortIndex(beta_copy, true);
  permute(beta_copy, ord);

  int p = beta_copy.size();

  VectorXd s(p);
  VectorXd w(p);
  VectorXi idx_i(p);
  VectorXi idx_j(p);

  int k = 0;

  for (int i = 0; i < p; i++) {
    idx_i[k] = i;
    idx_j[k] = i;
    s[k] = beta_copy(i) - lambda[i] * alpha * scale;
    w[k] = s[k];

    while ((k > 0) && (w[k - 1] <= w[k])) {
      k--;
      idx_j[k] = i;
      s[k] += s[k + 1];
      w[k] = s[k] / (i - idx_i[k] + 1.0);
    }
    k++;
  }

  for (int j = 0; j < k; j++) {
    double d = std::max(w[j], 0.0);
    for (int i = idx_i[j]; i <= idx_j[j]; i++) {
      beta_copy(i) = d;
    }
  }

  // return order and sigsn
  inversePermute(beta_copy, ord);
  beta_copy.array() *= beta_sign;

  return beta_copy;
}

void
SortedL1Norm::setAlpha(const double new_alpha)
{
  alpha = new_alpha;
}

double
SortedL1Norm::getAlpha() const
{
  return alpha;
}

Eigen::ArrayXd
SortedL1Norm::dualNorm(const Eigen::VectorXd& a) const
{
  Eigen::ArrayXd a_abs = a.array().abs();
  sort(a_abs, true);
  return cumSum(a_abs);
}

} // namspace slope
