#include "slope/slope.h"
#include <Eigen/Core>
#include <Eigen/LU>
#include <pybind11/eigen.h>
#include <pybind11/pybind11.h>

using namespace pybind11::literals;

namespace py = pybind11;

pybind11::tuple
fit_slope_dense(const Eigen::MatrixXd x,
                const Eigen::MatrixXd y,
                Eigen::ArrayXd lambda,
                Eigen::ArrayXd alpha)
{
  auto result = slope::slope(x, y, alpha, lambda);

  return py::make_tuple(result.beta0s, result.betas);
}

pybind11::tuple
fit_slope_sparse(const Eigen::SparseMatrix<double> x,
                 const Eigen::MatrixXd y,
                 Eigen::ArrayXd lambda,
                 Eigen::ArrayXd alpha)
{
  auto result = slope::slope(x, y, alpha, lambda);

  return py::make_tuple(result.beta0s, result.betas);
}

PYBIND11_MODULE(_sortedl1, m)
{
  m.def("fit_slope_dense", &fit_slope_dense);
  m.def("fit_slope_sparse", &fit_slope_sparse);
}
