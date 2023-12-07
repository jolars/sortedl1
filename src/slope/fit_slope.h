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
#include "parameters.h"
#include "pgd.h"
#include "regularization_sequence.h"
#include "results.h"
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
 */
template<typename T>
Results
fitSlope(const T& x,
         const Eigen::MatrixXd& y,
         Eigen::ArrayXd alpha = Eigen::ArrayXd::Zero(0),
         Eigen::ArrayXd lambda = Eigen::ArrayXd::Zero(0),
         const SlopeParameters& params = SlopeParameters())
{
  using Eigen::VectorXd;

  const int n = x.rows();
  const int p = x.cols();

  auto [x_centers, x_scales] = standardize(x, params.standardize);

  std::unique_ptr<Objective> objective = setupObjective(params.objective);

  // initialize coeficients
  double beta0 = 0.0;
  VectorXd beta = VectorXd::Zero(p);

  VectorXd eta = x * beta;
  eta.array() += beta0;

  VectorXd w(n); // weights
  VectorXd z(n); // working response

  objective->updateWeightsAndWorkingResponse(w, z, eta, y);

  VectorXd residual = z - eta;

  // Setup the regularization sequence and path
  SortedL1Norm sl1_norm{ lambda };

  if (lambda.size() == 0) {
    lambda = lambdaSequence(p, params.q, params.lambda_type);
  } else {
    if (lambda.size() != p) {
      throw std::invalid_argument(
        "lambda must be the same length as the number of predictors");
    }
    if (lambda.minCoeff() < 0) {
      throw std::invalid_argument("lambda must be non-negative");
    }
  }

  int path_length = params.path_length;

  if (alpha.size() == 0) {
    alpha = regularizationPath(x,
                               w,
                               z,
                               x_centers,
                               x_scales,
                               sl1_norm,
                               params.path_length,
                               params.alpha_min_ratio,
                               params.intercept,
                               params.standardize);
  } else {
    path_length = alpha.size();
  }

  VectorXd beta0s(path_length);
  std::vector<Eigen::Triplet<double>> beta_triplets;

  std::vector<double> primals;
  std::vector<double> dual_gaps;
  std::vector<std::vector<double>> primals_path;
  std::vector<std::vector<double>> dual_gaps_path;

  double learning_rate = 1.0;

  VectorXd beta_old_outer = beta;

  Gaussian subprob_objective;

  Clusters clusters(beta);

  int it_total = 0;

  // Regularization path loop
  for (int path_step = 0; path_step < path_length; ++path_step) {
    if (params.print_level > 0) {
      std::cout << "Path step: " << path_step << ", alpha: " << alpha(path_step)
                << std::endl;
    }

    sl1_norm.setAlpha(alpha(path_step));

    // IRLS loop
    for (int it_outer = 0; it_outer < params.max_it_outer; ++it_outer) {
      // The residual is kept up to date, but not eta. So we need to compute it
      // here.
      eta = z - residual;

      // Compute primal, dual, and gap
      double primal = objective->loss(eta, y) + sl1_norm.eval(beta);
      primals.emplace_back(primal);

      VectorXd gen_residual = objective->residual(eta, y);

      VectorXd gradient = computeGradient(
        x, gen_residual, x_centers, x_scales, params.standardize);
      VectorXd theta = gen_residual;
      theta.array() /= std::max(1.0, sl1_norm.dualNorm(gradient));
      double dual = objective->dual(theta, y);

      double dual_gap = primal - dual;

      dual_gaps.emplace_back(dual_gap);

      double tol = std::abs(primal) * params.tol;

      if (params.print_level > 1) {
        std::cout << indent(1) << "IRLS iteration: " << it_outer << std::endl
                  << indent(2) << "primal (main problem): " << primal
                  << std::endl
                  << indent(2) << "duality gap (main problem): " << dual_gap
                  << ", tol: " << tol << std::endl;
      }

      if (std::max(dual_gap, 0.0) <= tol) {
        break;
      }

      // Update weights and working response
      beta_old_outer = beta;

      objective->updateWeightsAndWorkingResponse(w, z, eta, y);
      residual = z - eta;

      if (params.print_level > 3) {
        printContents(w, "    weights");
        printContents(z, "    working response");
      }

      for (int it = 0; it < params.max_it; ++it) {
        if (it % params.pgd_freq == 0) {
          double g = (0.5 / n) * residual.cwiseAbs2().dot(w);
          double h = sl1_norm.eval(beta);
          double primal_inner = g + h;

          VectorXd gradient = computeGradient(
            x, residual, x_centers, x_scales, params.standardize);

          // Obtain a feasible dual point by dual scaling
          theta = residual;
          theta.array() /= std::max(1.0, sl1_norm.dualNorm(gradient));
          double dual_inner = subprob_objective.dual(theta, z);

          double dual_gap_inner = primal_inner - dual_inner;

          double tol_inner = std::abs(primal_inner) * params.tol;

          if (params.print_level > 2) {
            std::cout << indent(2) << "iteration: " << it << std::endl
                      << indent(3) << "primal (inner): " << primal_inner
                      << std::endl
                      << indent(3) << "duality gap (inner): " << dual_gap_inner
                      << ", tol: " << tol_inner << std::endl;
          }

          if (std::max(dual_gap_inner, 0.0) <= tol_inner) {
            break;
          }

          VectorXd beta_old = beta;

          if (params.print_level > 2) {
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
                                  params);

          clusters.update(beta);
        } else {
          if (params.print_level > 2) {
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
                            params);
        }
      }
      it_total++;
    }

    // Store everything for this step of the path
    auto [beta0_out, beta_out] =
      rescaleCoefficients(beta0, beta, x_centers, x_scales, params);

    beta0s(path_step) = std::move(beta0_out);

    for (int j = 0; j < p; ++j) {
      if (beta_out(j) != 0) {
        beta_triplets.emplace_back(j, path_step, beta_out(j));
      }
    }

    primals_path.emplace_back(primals);
    dual_gaps_path.emplace_back(dual_gaps);
  }

  Eigen::SparseMatrix<double> betas(p, path_length);
  betas.setFromTriplets(beta_triplets.begin(), beta_triplets.end());

  return {
    beta0s, betas, alpha, lambda, primals_path, dual_gaps_path, it_total
  };
}

} // namespace slope
