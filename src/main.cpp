#include "slope/slope.h"
#include <Eigen/Core>
#include <Eigen/SparseCore>
#include <pybind11/eigen.h>
#include <pybind11/iostream.h>
#include <pybind11/pybind11.h>

using namespace pybind11::literals;

namespace py = pybind11;

template<typename T>
pybind11::tuple
fit_slope(T& x,
          const Eigen::MatrixXd& y,
          const Eigen::ArrayXd& lambda,
          const double alpha,
          const py::dict& args)
{
  slope::Slope model;

  model.setIntercept(args["intercept"].cast<bool>());
  model.setCentering(args["centering"].cast<std::string>());
  model.setScaling(args["scaling"].cast<std::string>());
  model.setTol(args["tol"].cast<double>());
  model.setMaxIterations(args["max_it"].cast<int>());

  slope::SlopeFit res = model.fit(x, y, alpha, lambda);

  return py::make_tuple(res.getIntercepts(),
                        res.getCoefs(),
                        res.getLambda(),
                        res.getAlpha(),
                        res.getPasses());
}

pybind11::tuple
fit_slope_dense(Eigen::MatrixXd& x,
                const Eigen::MatrixXd& y,
                const Eigen::ArrayXd& lambda,
                const double alpha,
                const py::dict& args)
{
  return fit_slope(x, y, lambda, alpha, args);
}

pybind11::tuple
fit_slope_sparse(Eigen::SparseMatrix<double>& x,
                 const Eigen::MatrixXd& y,
                 const Eigen::ArrayXd& lambda,
                 const double alpha,
                 const py::dict& args)
{
  return fit_slope(x, y, lambda, alpha, args);
}

PYBIND11_MODULE(_sortedl1, m)
{
  m.def("fit_slope_dense", &fit_slope_dense);
  m.def("fit_slope_sparse", &fit_slope_sparse);
}
