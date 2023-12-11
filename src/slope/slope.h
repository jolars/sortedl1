/**
 * @file
 * @brief The actual function that fits SLOPE
 */

#pragma once

#include "cd.h"
#include "clusters.h"
#include "helpers.h"
#include "math.h"
#include "objectives.h"
#include "pgd.h"
#include "regularization_sequence.h"
#include "sorted_l1_norm.h"
#include "standardize.h"
#include <Eigen/Core>
#include <Eigen/Sparse>
#include <cassert>
#include <iostream>
#include <memory>
#include <vector>

namespace slope {

/**
 * Abstract class representing an objective function.
 *
 * This class defines the interface for an objective function, which is used in
 * optimization algorithms. The objective function calculates the loss, dual,
 * residual, and updates the weights and working response.
 */
class Slope
{
public:
  /**
   * Default constructor for the Slope class.
   *
   * Initializes the Slope object with default parameter values.
   */
  Slope()
    : intercept(true)
    , standardize(true)
    , update_clusters(false)
    , alpha_min_ratio(-1)
    , learning_rate_decr(0.5)
    , q(0.1)
    , tol(1e-4)
    , max_it(1e6)
    , max_it_outer(30)
    , path_length(100)
    , pgd_freq(10)
    , print_level(0)
    , lambda_type("bh")
    , objective("gaussian")
  {
  }

  /**
   * Sorted L-One Penalized Estimation.
   *
   * This function fits a linear regression model to the given data using the
   * ordinary least squares method.
   *
   * @param x The design matrix, where each column represents a feature.
   * @param y The response matrix. Each row represents an observation.
   * @param alpha Sequence of multipliers for the sorted l1 norm along the
   * regularization path.
   * @param lambda The regularization parameter for the sorted l1 norm, which is
   * a positive nonincreasing array of weights.
   */
  void fit(const Eigen::MatrixXd& x,
           const Eigen::MatrixXd& y,
           const Eigen::ArrayXd& alpha = Eigen::ArrayXd::Zero(0),
           const Eigen::ArrayXd& lambda = Eigen::ArrayXd::Zero(0));

  /**
   * Sorted L-One Penalized Estimation.
   *
   * This function fits a linear regression model to the given data using the
   * ordinary least squares method.
   *
   * @param x The design matrix, where each column represents a feature.
   * @param y The response matrix. Each row represents an observation.
   * @param alpha Sequence of multipliers for the sorted l1 norm along the
   * regularization path.
   * @param lambda The regularization parameter for the sorted l1 norm, which is
   * a positive nonincreasing array of weights.
   */
  void fit(const Eigen::SparseMatrix<double>& x,
           const Eigen::MatrixXd& y,
           const Eigen::ArrayXd& alpha = Eigen::ArrayXd::Zero(0),
           const Eigen::ArrayXd& lambda = Eigen::ArrayXd::Zero(0));

  /**
   * @brief Sets the intercept flag.
   *
   * @param intercept Should an intercept be fitted?
   */
  void setIntercept(bool intercept);

  /**
   * @brief Sets the standardize flag.
   *
   * @param standardize Should the design matrix be standardized?
   */
  void setStandardize(bool standardize);

  /**
   * @brief Sets the update clusters flag.
   *
   * @param update_clusters Selects whether the coordinate descent keeps the
   * clusters updated.
   */
  void setUpdateClusters(bool update_clusters);

  /**
   * @brief Sets the alpha min ratio.
   *
   * @param alpha_min_ratio The value to set for the alpha min ratio. A negative
   * value means that the program automatically chooses 1e-4 if the number of
   * observations is larger than the number of features and 1e-2 otherwise.
   */
  void setAlphaMinRatio(double alpha_min_ratio);

  /**
   * @brief Sets the learning rate decrement.
   *
   * @param learning_rate_decr The value to set for the learning rate decrement
   * for the proximal gradient descent step.
   */
  void setLearningRateDecr(double learning_rate_decr);

  /**
   * @brief Sets the q value.
   *
   * @param q The value to set for the q value for use in automatically
   * generating the lambda sequence. values between 0 and 1 are allowed..
   */
  void setQ(double q);

  /**
   * @brief Sets the tolerance value.
   *
   * @param tol The value to set for the tolerance value. Must be positive.
   */
  void setTol(double tol);

  /**
   * @brief Sets the maximum number of iterations.
   *
   * @param max_it The value to set for the maximum number of iterations. Must
   * be positive.
   */
  void setMaxIt(int max_it);

  /**
   * @brief Sets the maximum number of outer iterations.
   *
   * @param max_it_outer The value to set for the maximum number of outer
   * iterations for the iterative repeated least-squares step. Must be positive.
   * Has no real effect when the objective is Gaussian.
   */
  void setMaxItOuter(int max_it_outer);

  /**
   * @brief Sets the path length.
   *
   * @param path_length The value to set for the path length.
   */
  void setPathLength(int path_length);

  /**
   * @brief Sets the frequence of proximal gradient descent steps.
   *
   * @param pgd_freq The frequency of the proximal gradient descent steps (or
   * the inverse of that actually). A value of 1 means that the algorithm only
   * runs proximal gradient descent steps.
   */
  void setPgdFreq(int pgd_freq);

  /**
   * @brief Sets the print level.
   *
   * @param print_level The value to set for the print level. A print level of 1
   * prints values from the outer loop, a level of 2 from the inner loop, and a
   * level of 3 some extra debugging information. A level of 0 means no
   * printing.
   */
  void setPrintLevel(int print_level);

  /**
   * @brief Sets the lambda type.
   *
   * @param lambda_type The value to set for the lambda type. Only "bh" is
   * allowed at the moment, which computed the Benjamini-Hochberg sequence.
   * @see setQ
   */
  void setLambdaType(const std::string& lambda_type);

  /**
   * @brief Sets the objective.
   *
   * @param objective The value to set for the objective. Only "gaussian" is
   * allowed at the moment, which results in the standard SLOPE.
   */
  void setObjective(const std::string& objective);

  /**
   * @brief Get the alpha sequence.
   *
   * @return The sequence of weights for the regularization path.
   */
  const Eigen::ArrayXd& getAlpha() const;

  /**
   * @brief Get the lambda sequence.
   *
   * @return The sequence of lambda values for the weights of the sorted L1
   * norm.
   */
  const Eigen::ArrayXd& getLambda() const;

  /**
   * Get the coefficients from the path.
   *
   * @return The coefficients from the path, stored in a sparse matrix.
   */
  const Eigen::SparseMatrix<double>& getCoefs() const;

  /**
   * Get the intercepts from the path.
   *
   * @return The coefficients from the path, stored in an Eigen vector. If no
   * intercepts were fit, this is a vector of zeros.
   */
  const Eigen::VectorXd& getIntercepts() const;

  /**
   * Get the total number of (inner) iterations.
   *
   * @return The toral number of iterations from the inner loop, computed across
   * the path.
   */
  int getTotalIterations() const;

  /**
   * Get the duality gaps.
   *
   * @return Get the duality gaps from the path.
   */
  const std::vector<std::vector<double>>& getDualGaps() const;

  /**
   * Get the primal objective values.
   *
   * @return Get the primal objective values from the path.
   */
  const std::vector<std::vector<double>>& getPrimals() const;

private:
  /**
   * Calculates the slope coefficients for a linear regression model using the
   * SortedL1Norm regularization.
   *
   * @param x The dense input matrix of size n x p, where n is the number of
   *   observations and p is the number of predictors.
   * @param y The response matrix of size n x 1.
   * @param alpha The regularization parameter sequence. If not provided, it
   * will be generated automatically.
   * @param lambda The regularization parameter for the SortedL1Norm
   *   regularization. If not provided, it will be set to zero.
   * @see SlopeParameters
   */
  template<typename T>
  void fitImpl(const T& x,
               const Eigen::VectorXd& y,
               Eigen::ArrayXd alpha,
               Eigen::ArrayXd lambda)
  {
    using Eigen::VectorXd;

    const int n = x.rows();
    const int p = x.cols();

    if (n != y.rows()) {
      throw std::invalid_argument("x and y must have the same number of rows");
    }

    auto [x_centers, x_scales] = computeCentersAndScales(x, this->standardize);

    std::unique_ptr<Objective> objective = setupObjective(this->objective);

    beta0 = 0.0;
    beta.resize(p);
    beta.setZero();
    VectorXd eta = VectorXd::Zero(n); // linear predictor
    VectorXd w = VectorXd::Ones(n);   // weights
    VectorXd z = y;                   // working response

    objective->updateWeightsAndWorkingResponse(w, z, eta, y);

    VectorXd residual = z;

    if (lambda.size() == 0) {
      lambda = lambdaSequence(p, this->q, this->lambda_type);
    } else {
      if (lambda.size() != p) {
        throw std::invalid_argument(
          "lambda must be the same length as the number of predictors");
      }
      if (lambda.minCoeff() < 0) {
        throw std::invalid_argument("lambda must be non-negative");
      }
      if (!lambda.isFinite().all()) {
        throw std::invalid_argument("lambda must be finite");
      }
    }

    // Setup the regularization sequence and path
    SortedL1Norm sl1_norm{ lambda };

    if (alpha.size() == 0) {
      alpha = regularizationPath(x,
                                 w,
                                 z,
                                 x_centers,
                                 x_scales,
                                 sl1_norm,
                                 this->path_length,
                                 this->alpha_min_ratio,
                                 this->intercept,
                                 this->standardize);
    } else {
      if (alpha.minCoeff() < 0) {
        throw std::invalid_argument("alpha must be non-negative");
      }
      if (!alpha.isFinite().all()) {
        throw std::invalid_argument("alpha must be finite");
      }
      path_length = alpha.size();
    }

    int path_length = this->path_length;

    std::vector<Eigen::Triplet<double>> beta_triplets;
    std::vector<double> dual_gaps;
    std::vector<double> primals;

    beta0s.resize(path_length);

    double learning_rate = 1.0;

    VectorXd beta_old_outer = beta;

    Gaussian subprob_objective;

    Clusters clusters(beta);

    this->it_total = 0;

    // Regularization path loop
    for (int path_step = 0; path_step < path_length; ++path_step) {
      if (this->print_level > 0) {
        std::cout << "Path step: " << path_step
                  << ", alpha: " << alpha(path_step) << std::endl;
      }

      sl1_norm.setAlpha(alpha(path_step));

      // IRLS loop
      for (int it_outer = 0; it_outer < this->max_it_outer; ++it_outer) {
        // The residual is kept up to date, but not eta. So we need to compute
        // it here.
        eta = z - residual;

        // Compute primal, dual, and gap
        double primal = objective->loss(eta, y) + sl1_norm.eval(beta);
        primals.emplace_back(primal);

        VectorXd gen_residual = objective->residual(eta, y);

        VectorXd gradient = computeGradient(
          x, gen_residual, x_centers, x_scales, this->standardize);
        VectorXd theta = gen_residual;
        theta.array() /= std::max(1.0, sl1_norm.dualNorm(gradient));
        double dual = objective->dual(theta, y);

        double dual_gap = primal - dual;

        dual_gaps.emplace_back(dual_gap);

        double tol_scaled = std::abs(primal) * this->tol;

        if (this->print_level > 1) {
          std::cout << indent(1) << "IRLS iteration: " << it_outer << std::endl
                    << indent(2) << "primal (main problem): " << primal
                    << std::endl
                    << indent(2) << "duality gap (main problem): " << dual_gap
                    << ", tol: " << tol_scaled << std::endl;
        }

        if (std::max(dual_gap, 0.0) <= tol_scaled) {
          break;
        }

        // Update weights and working response
        beta_old_outer = beta;

        objective->updateWeightsAndWorkingResponse(w, z, eta, y);
        residual = z - eta;

        if (this->print_level > 3) {
          printContents(w, "    weights");
          printContents(z, "    working response");
        }

        for (int it = 0; it < this->max_it; ++it) {
          if (it % this->pgd_freq == 0) {
            double g = (0.5 / n) * residual.cwiseAbs2().dot(w);
            double h = sl1_norm.eval(beta);
            double primal_inner = g + h;

            VectorXd gradient = computeGradient(
              x, residual, x_centers, x_scales, this->standardize);

            // Obtain a feasible dual point by dual scaling
            theta = residual;
            theta.array() /= std::max(1.0, sl1_norm.dualNorm(gradient));
            double dual_inner = subprob_objective.dual(theta, z);

            double dual_gap_inner = primal_inner - dual_inner;

            double tol_inner = std::abs(primal_inner) * this->tol;

            if (this->print_level > 2) {
              std::cout << indent(2) << "iteration: " << it << std::endl
                        << indent(3) << "primal (inner): " << primal_inner
                        << std::endl
                        << indent(3)
                        << "duality gap (inner): " << dual_gap_inner
                        << ", tol: " << tol_inner << std::endl;
            }

            if (std::max(dual_gap_inner, 0.0) <= tol_inner) {
              break;
            }

            VectorXd beta_old = beta;

            if (this->print_level > 2) {
              std::cout << indent(3) << "Running PGD step" << std::endl;
            }

            proximalGradientDescent(beta0,
                                    beta,
                                    residual,
                                    learning_rate,
                                    gradient,
                                    x,
                                    w,
                                    z,
                                    sl1_norm,
                                    x_centers,
                                    x_scales,
                                    g,
                                    intercept,
                                    standardize,
                                    learning_rate_decr,
                                    print_level);

            clusters.update(beta);
          } else {
            if (this->print_level > 2) {
              std::cout << indent(3) << "Running CD step" << std::endl;
            }

            coordinateDescent(beta0,
                              beta,
                              residual,
                              clusters,
                              x,
                              w,
                              z,
                              sl1_norm,
                              x_centers,
                              x_scales,
                              this->intercept,
                              this->standardize,
                              this->update_clusters,
                              this->print_level);
          }
        }
        it_total++;
      }

      // Store everything for this step of the path
      auto [beta0_out, beta_out] = rescaleCoefficients(
        beta0, beta, x_centers, x_scales, intercept, standardize);

      beta0s(path_step) = std::move(beta0_out);

      for (int j = 0; j < p; ++j) {
        if (beta_out(j) != 0) {
          beta_triplets.emplace_back(j, path_step, beta_out(j));
        }
      }

      primals_path.emplace_back(primals);
      dual_gaps_path.emplace_back(dual_gaps);
    }

    betas.resize(p, path_length);
    betas.setFromTriplets(beta_triplets.begin(), beta_triplets.end());
    alpha_out = alpha;
    lambda_out = lambda;
  }

  // parameters
  bool intercept;
  bool standardize;
  bool update_clusters;
  double alpha_min_ratio;
  double learning_rate_decr;
  double q;
  double tol;
  int max_it;
  int max_it_outer;
  int path_length;
  int pgd_freq;
  int print_level;
  std::string lambda_type;
  std::string objective;

  // estimates
  Eigen::ArrayXd alpha_out;
  Eigen::ArrayXd lambda_out;
  Eigen::SparseMatrix<double> betas;
  Eigen::VectorXd beta0s;
  Eigen::VectorXd beta;
  double beta0;
  int it_total;
  std::vector<std::vector<double>> dual_gaps_path;
  std::vector<std::vector<double>> primals_path;
};

} // namespace slope
