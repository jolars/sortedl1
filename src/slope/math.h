/**
 * @internal
 * @file
 * @brief Mathematical support functions for the slope package.
 */

#pragma once

#include <Eigen/Core>
#include <numeric>
#include <vector>

namespace slope {

/**
 * @brief Returns the sign of a given value.
 *
 * This function determines the sign of the input value by comparing it to zero.
 * It returns -1 if the value is negative, 0 if the value is zero, and 1 if the
 * value is positive.
 *
 * @tparam T The type of the input value.
 * @param val The value for which the sign needs to be determined.
 * @return -1 if the value is negative, 0 if the value is zero, and 1 if the
 * value is positive.
 */
template<typename T>
int
sign(T val)
{
  return (T(0) < val) - (val < T(0));
}

/**
 * Calculates the cumulative sum of the elements in the input array.
 *
 * @tparam T The type of the input array.
 * @param x The input array.
 * @return An Eigen::ArrayXd containing the cumulative sum of the elements in
 * the input array.
 */
template<typename T>
Eigen::ArrayXd
cumSum(const T& x)
{
  std::vector<double> cum_sum(x.size());
  std::partial_sum(
    x.data(), x.data() + x.size(), cum_sum.begin(), std::plus<double>());

  Eigen::Map<Eigen::ArrayXd> out(cum_sum.data(), cum_sum.size());

  return out;
}

/**
 * Calculates the sigmoid function for the given input.
 *
 * The sigmoid function is defined as 1 / (1 + exp(-x)).
 *
 * @tparam T The type of the input.
 * @param x The input value.
 * @return The result of the sigmoid function.
 */
template<typename T>
T
sigmoid(const T& x)
{
  return 1.0 / (1.0 + std::exp(-x));
}

/**
 * Returns the value of x clamped between the specified lower and upper bounds.
 *
 * @tparam T the type of the values being clamped
 * @param x the value to be clamped
 * @param lo the lower bound
 * @param hi the upper bound
 * @return the clamped value of x
 */
template<typename T>
T
clamp(const T& x, const T& lo, const T& hi)
{
  return x < lo ? lo : x > hi ? hi : x;
}

/**
 * Computes the gradient of a function.
 *
 * @tparam T The type of the input matrix.
 * @param x The input matrix.
 * @param residual The residual vector.
 * @param x_centers The vector of center values for each column of x.
 * @param x_scales The vector of scale values for each column of x.
 * @param standardize Flag indicating whether to standardize the gradient.
 * @return The computed gradient vector.
 */
template<typename T>
Eigen::VectorXd
computeGradient(const T& x,
                const Eigen::VectorXd& residual,
                const Eigen::VectorXd& x_centers,
                const Eigen::VectorXd& x_scales,
                const bool standardize)
{
  const int n = x.rows();
  const int p = x.cols();

  Eigen::VectorXd gradient(p);

  if (standardize) {
    double wr_sum = residual.sum();
    for (int j = 0; j < p; ++j) {
      gradient(j) =
        -(x.col(j).dot(residual) - x_centers(j) * wr_sum) / (x_scales(j) * n);
    }
  } else {
    gradient = -(x.transpose() * residual) / n;
  }

  return gradient;
}

} // namespace slope
