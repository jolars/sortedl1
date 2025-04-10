#include "setup_model.h"
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
fit_slope_path(T& x,
               const Eigen::MatrixXd& y,
               const Eigen::ArrayXd& lambda,
               const Eigen::ArrayXd& alpha,
               const py::dict& args)
{
  slope::Slope model = setup_model(args);
  slope::SlopePath path = model.path(x, y, alpha, lambda);

  std::vector<Eigen::SparseMatrix<double>> coefs = path.getCoefs();
  auto intercepts = path.getIntercepts();

  int p = coefs.front().rows();
  int m = coefs.front().cols();
  int path_length = path.size();

  py::array_t<double> coefs_out({ p, m, path_length });
  py::array_t<double> intercepts_out({ m, path_length });

  // Get mutable buffers for direct access
  auto coefs_buf = coefs_out.mutable_unchecked<3>();
  auto intercepts_buf = intercepts_out.mutable_unchecked<2>();

  // Fill the arrays with data
  for (int step = 0; step < path_length; step++) {
    Eigen::MatrixXd dense_coefs = coefs[step];

    for (int j = 0; j < m; j++) {
      intercepts_buf(j, step) = intercepts[step](j);

      for (int i = 0; i < p; i++) {
        coefs_buf(i, j, step) = dense_coefs(i, j);
      }
    }
  }

  return py::make_tuple(
    intercepts_out, coefs_out, path.getLambda(), path.getAlpha());
}

template<typename T>
pybind11::tuple
fit_slope(T& x,
          const Eigen::MatrixXd& y,
          const Eigen::ArrayXd& lambda,
          const double alpha,
          const py::dict& args)
{
  slope::Slope model = setup_model(args);
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

pybind11::tuple
fit_slope_path_dense(Eigen::MatrixXd& x,
                     const Eigen::MatrixXd& y,
                     const Eigen::ArrayXd& lambda,
                     const Eigen::ArrayXd& alpha,
                     const py::dict& args)
{
  return fit_slope_path(x, y, lambda, alpha, args);
}

pybind11::tuple
fit_slope_path_sparse(Eigen::SparseMatrix<double>& x,
                      const Eigen::MatrixXd& y,
                      const Eigen::ArrayXd& lambda,
                      const Eigen::ArrayXd& alpha,
                      const py::dict& args)
{
  return fit_slope_path(x, y, lambda, alpha, args);
}

PYBIND11_MODULE(_sortedl1, m)
{
  m.def("fit_slope_dense", &fit_slope_dense);
  m.def("fit_slope_sparse", &fit_slope_sparse);
  m.def("fit_slope_path_dense", &fit_slope_path_dense);
  m.def("fit_slope_path_sparse", &fit_slope_path_sparse);
}
