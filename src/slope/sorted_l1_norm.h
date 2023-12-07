/**
 * @file
 * @brief The declaration of the SortedL1Norm class
 */

#pragma once

#include "math.h"
#include "utils.h"
#include <Eigen/Core>

namespace slope {

/**
 * @brief Class representing the Sorted L1 Norm.
 */
class SortedL1Norm
{
private:
  double alpha = 1.0;    /**< The alpha parameter. */
  Eigen::ArrayXd lambda; /**< The lambda parameter. */

public:
  /**
   * @brief Constructor for SortedL1Norm.
   * @param lambda The lambda parameter.
   */
  SortedL1Norm(const Eigen::ArrayXd& lambda);

  /**
   * @brief Evaluates the Sorted L1 Norm.
   * @param beta The beta parameter.
   * @return The evaluation result.
   */
  double eval(const Eigen::VectorXd& beta) const;

  /**
   * @brief Computes the proximal operator of the Sorted L1 Norm.
   * @param beta The beta parameter.
   * @param scale The scale parameter.
   * @return The proximal operator result.
   */
  Eigen::VectorXd prox(const Eigen::VectorXd& beta, const double scale) const;

  /**
   * @brief Computes the dual norm of a vector.
   * @param a The vector.
   * @return The dual norm.
   */
  double dualNorm(const Eigen::VectorXd& a) const;

  /**
   * @brief Sets the lambda parameter.
   * @param new_lambda The new lambda parameter.
   */
  void setLambda(const Eigen::ArrayXd& new_lambda);

  /**
   * @brief Sets the alpha parameter.
   * @param new_alpha The new alpha parameter.
   */
  void setAlpha(const double new_alpha);

  /**
   * @brief Gets the lambda parameter.
   * @return The lambda parameter.
   */
  Eigen::ArrayXd getLambda() const;

  /**
   * @brief Gets a constant reference to the lambda parameter.
   * @return A constant reference to the lambda parameter.
   */
  const Eigen::ArrayXd& getLambdaRef() const;

  /**
   * @brief Gets the alpha parameter.
   * @return The alpha parameter.
   */
  double getAlpha() const;
};

} // namespace slope
