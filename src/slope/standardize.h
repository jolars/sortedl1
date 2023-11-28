#pragma once

#include <Eigen/Sparse>

namespace slope {

std::pair<Eigen::VectorXd, Eigen::VectorXd>
computeMeanAndStdDev(const Eigen::MatrixXd& x);

std::pair<Eigen::VectorXd, Eigen::VectorXd>
computeMeanAndStdDev(const Eigen::SparseMatrix<double>& x);

std::pair<double, Eigen::VectorXd>
unstandardizeCoefficients(double beta0,
                          Eigen::VectorXd beta,
                          const Eigen::VectorXd& x_means,
                          const Eigen::VectorXd& x_stddevs,
                          const bool intercept);

}
