#include "slope/slope.h"
#include <Eigen/Core>
#include <Eigen/LU>
#include <pybind11/eigen.h>
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
  auto objective_choice = args["objective_choice"].cast<std::string>();
  auto intercept = args["intercept"].cast<bool>();
  auto standardize = args["standardize"].cast<bool>();
  auto path_length = args["path_length"].cast<int>();
  auto alpha_min_ratio = args["alpha_min_ratio"].cast<double>();
  auto pgd_freq = args["pgd_freq"].cast<int>();
  auto tol = args["tol"].cast<double>();
  auto max_it = args["max_it"].cast<int>();
  auto max_it_outer = args["max_it_outer"].cast<int>();
  auto update_clusters = args["update_clusters"].cast<bool>();
  auto print_level = args["print_level"].cast<int>();

  auto result = slope::slope(x,
                             y,
                             alpha,
                             lambda,
                             objective_choice,
                             intercept,
                             standardize,
                             path_length,
                             alpha_min_ratio,
                             pgd_freq,
                             tol,
                             max_it,
                             max_it_outer,
                             update_clusters,
                             print_level);

  return py::make_tuple(result.beta0s, result.betas);
}

pybind11::tuple
fit_slope_dense(const Eigen::MatrixXd& x,
                const Eigen::MatrixXd& y,
                const Eigen::ArrayXd& lambda,
                const Eigen::ArrayXd& alpha,
                const py::dict& args)
{
  return fit_slope(x, y, alpha, lambda, args);
}

pybind11::tuple
fit_slope_sparse(const Eigen::SparseMatrix<double>& x,
                 const Eigen::MatrixXd& y,
                 const Eigen::ArrayXd& lambda,
                 const Eigen::ArrayXd& alpha,
                 const py::dict& args)
{
  return fit_slope(x, y, alpha, lambda, args);
}

PYBIND11_MODULE(_sortedl1, m)
{
  m.def("fit_slope_dense", &fit_slope_dense);
  m.def("fit_slope_sparse", &fit_slope_sparse);
}
