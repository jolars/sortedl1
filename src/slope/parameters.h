/**
 * @file
 * @brief The declaration of the SlopeParameters struct
 */

#pragma once

#include <string>

namespace slope {

/**
 * @struct SlopeParameters
 * @brief A struct that holds the parameters for the Slope algorithm.
 *
 * This struct holds the parameters that can be used to configure the behavior
 * of the Slope algorithm. The Slope algorithm is used for regression and
 * variable selection.
 *
 * @var SlopeParameters::intercept
 * A boolean indicating whether an intercept term should be included in the
 * model.
 *
 * @var SlopeParameters::standardize
 * A boolean indicating whether the input data should be standardized before
 * fitting the model.
 *
 * @var SlopeParameters::update_clusters
 * A boolean indicating whether the cluster assignments should be updated during
 * the optimization process.
 *
 * @var SlopeParameters::alpha_min_ratio
 * A double representing the minimum value of the regularization parameter
 * alpha. If -1, the value will be set to 1e-4 if n > p and 1e-2 otherwise.
 *
 * @var SlopeParameters::learning_rate_decr
 * Sets the learning rate decrement for the line search in the proximal gradient
 * descent step.
 *
 * @var SlopeParameters::q
 * A double representing the quantile level for the L1 penalty.
 *
 * @var SlopeParameters::tol
 * A double representing the convergence tolerance for the optimization
 * algorithm.
 *
 * @var SlopeParameters::max_it
 * An integer representing the maximum number of iterations for the optimization
 * algorithm.
 *
 * @var SlopeParameters::max_it_outer
 * An integer representing the maximum number of outer iterations for the
 * optimization algorithm.
 *
 * @var SlopeParameters::path_length
 * An integer representing the number of points on the regularization path.
 *
 * @var SlopeParameters::pgd_freq
 * An integer representing the frequency of the proximal gradient descent
 * updates.
 *
 * @var SlopeParameters::print_level
 * An integer representing the level of verbosity for the optimization
 * algorithm.
 *
 * @var SlopeParameters::lambda_type
 * A string representing the type of regularization penalty to be used.
 * Currently only "bh" (Benjamini-Hochberg) is supported.
 *
 * @var SlopeParameters::objective
 * A string representing the choice of objective function for the optimization
 * algorithm. Currently only "gaussian" is supported.
 */
struct SlopeParameters
{
  bool intercept = true;
  bool standardize = true;
  bool update_clusters = false;
  double alpha_min_ratio = -1;
  double learning_rate_decr = 0.5;
  double q = 0.1;
  double tol = 1e-8;
  int max_it = 1e6;
  int max_it_outer = 100;
  int path_length = 100;
  int pgd_freq = 10;
  int print_level = 0;
  std::string lambda_type = "bh";
  std::string objective = "gaussian";
};

} // namespace slope
