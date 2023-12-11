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
  slope::Slope model;

  model.setIntercept(args["intercept"].cast<bool>());
  model.setStandardize(args["standardize"].cast<bool>());
  model.setUpdateClusters(args["update_clusters"].cast<bool>());
  model.setAlphaMinRatio(args["alpha_min_ratio"].cast<double>());
  model.setObjective(args["objective"].cast<std::string>());
  model.setPathLength(args["path_length"].cast<int>());
  model.setPgdFreq(args["pgd_freq"].cast<int>());
  model.setTol(args["tol"].cast<double>());
  model.setMaxIt(args["max_it"].cast<int>());
  model.setMaxItOuter(args["max_it_outer"].cast<int>());
  model.setPrintLevel(args["print_level"].cast<int>());

  model.fit(x, y, alpha, lambda);

  return py::make_tuple(model.getIntercepts(),
                        model.getCoefs(),
                        model.getLambda(),
                        model.getAlpha(),
                        model.getTotalIterations());
}

pybind11::tuple
fit_slope_dense(const Eigen::MatrixXd& x,
                const Eigen::MatrixXd& y,
                const Eigen::ArrayXd& lambda,
                const Eigen::ArrayXd& alpha,
                const py::dict& args)
{
  return fit_slope(x, y, lambda, alpha, args);
}

pybind11::tuple
fit_slope_sparse(const Eigen::SparseMatrix<double>& x,
                 const Eigen::MatrixXd& y,
                 const Eigen::ArrayXd& lambda,
                 const Eigen::ArrayXd& alpha,
                 const py::dict& args)
{
  return fit_slope(x, y, lambda, alpha, args);
}

PYBIND11_MODULE(_sortedl1, m)
{
  m.def("fit_slope_dense", &fit_slope_dense);
  m.def("fit_slope_sparse", &fit_slope_sparse);
}
