/**
 * @file
 * @brief The declaration of the main functions in the slope package
 */

#include "parameters.h"
#include "results.h"
#include <Eigen/Sparse>

namespace slope {

/**
 * Calculates the slope coefficients for a linear regression model using the
 * SortedL1Norm regularization.
 *
 * @param x The dense input matrix of size n x p, where n is the number of
 *   observations and p is the number of predictors.
 * @param y The response matrix of size n x 1.
 * @param alpha The regularization parameter sequence. If not provided, it will
 *   be generated automatically.
 * @param lambda The regularization parameter for the SortedL1Norm
 *   regularization. If not provided, it will be set to zero.
 * @param params A struct containing the parameters for the calculation. See
 * SlopeParameters.
 * @return The slope coefficients, intercept values, and primal values for each
 *   step in the regularization path.
 * @see SlopeParameters
 * @ingroup estimators
 */
Results
slope(const Eigen::MatrixXd& x,
      const Eigen::MatrixXd& y,
      Eigen::ArrayXd alpha = Eigen::ArrayXd::Zero(0),
      Eigen::ArrayXd lambda = Eigen::ArrayXd::Zero(0),
      const SlopeParameters& params = SlopeParameters());

/**
 * Calculates the slope coefficients for a linear regression model using the
 * SortedL1Norm regularization.
 *
 * @param x Sparse input matrix of size n x p, where n is the number of
 *   observations and p is the number of predictors.
 * @param y The response matrix of size n x 1.
 * @param alpha The regularization parameter sequence. If not provided, it will
 *   be generated automatically.
 * @param lambda The regularization parameter for the SortedL1Norm
 *   regularization. If not provided, it will be set to zero.
 * @param params A struct containing the parameters for the calculation. See
 * SlopeParamters.
 * @return The slope coefficients, intercept values, and primal values for each
 *   step in the regularization path.
 * @see SlopeParameters
 * @ingroup estimators
 */
Results
slope(const Eigen::SparseMatrix<double>& x,
      const Eigen::MatrixXd& y,
      Eigen::ArrayXd alpha = Eigen::ArrayXd::Zero(0),
      Eigen::ArrayXd lambda = Eigen::ArrayXd::Zero(0),
      const SlopeParameters& params = SlopeParameters());

} // namespace slope
