#include "slope/parameters.h"
#include "slope/slope.h"
#include <Eigen/Core>
#include <Eigen/LU>
#include <pybind11/eigen.h>
#include <pybind11/iostream.h>
#include <pybind11/pybind11.h>

using namespace pybind11::literals;

namespace py = pybind11;

template<typename T>
pybind11::tuple
fit_slope(const T& x,
          const Eigen::MatrixXd& y,
          const Eigen::ArrayXd& lambda,
          const Eigen::ArrayXd& alpha,
          const py::dict& args)
{
  slope::SlopeParameters params;

  params.intercept = args["intercept"].cast<bool>();
  params.standardize = args["standardize"].cast<bool>();
  params.update_clusters = args["update_clusters"].cast<bool>();
  params.alpha_min_ratio = args["alpha_min_ratio"].cast<double>();
  params.objective = args["objective"].cast<std::string>();
  params.path_length = args["path_length"].cast<int>();
  params.pgd_freq = args["pgd_freq"].cast<int>();
  params.tol = args["tol"].cast<double>();
  params.max_it = args["max_it"].cast<int>();
  params.max_it_outer = args["max_it_outer"].cast<int>();
  params.print_level = args["print_level"].cast<int>();

  auto result = slope::slope(x, y, alpha, lambda, params);

  return py::make_tuple(
    result.beta0s, result.betas, result.lambda, result.alpha);
}

pybind11::tuple
fit_slope_dense(const Eigen::MatrixXd& x,
                const Eigen::MatrixXd& y,
                Eigen::ArrayXd lambda,
                Eigen::ArrayXd alpha,
                const py::dict& args)
{
  return fit_slope(x, y, lambda, alpha, args);
}

pybind11::tuple
fit_slope_sparse(const Eigen::SparseMatrix<double>& x,
                 const Eigen::MatrixXd& y,
                 Eigen::ArrayXd lambda,
                 Eigen::ArrayXd alpha,
                 const py::dict& args)
{
  return fit_slope(x, y, lambda, alpha, args);
}

PYBIND11_MODULE(_sortedl1, m)
{
  // m.def("fit_slope_dense", &fit_slope_dense);
  m.def("fit_slope_dense", &fit_slope_dense);
  m.def("fit_slope_sparse", &fit_slope_sparse);
}
