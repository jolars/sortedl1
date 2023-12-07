/**
 * @file
 * @brief The declaration of the Results struct.
 */

#pragma once

#include <Eigen/Sparse>
#include <vector>

namespace slope {

/**
 * @brief Struct to store the results of a calculation.
 */
struct Results
{
  const Eigen::VectorXd beta0s; /**< Intercept values for each calculation. */
  const Eigen::SparseMatrix<double>
    betas;                     /**< Coefficient matrix for each calculation. */
  const Eigen::ArrayXd alpha;  /**< Array of alpha values. */
  const Eigen::ArrayXd lambda; /**< Array of lambda values. */
  const std::vector<std::vector<double>>
    primals; /**< Vector of primal values for each calculation. */
  const std::vector<std::vector<double>>
    dual_gaps;        /**< Vector of dual gap values for each calculation. */
  const int it_total; /**< Total number of iterations. */
};

} // namespace slope
