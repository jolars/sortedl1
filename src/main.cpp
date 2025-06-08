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

  auto tol_dev_change = args["tol_dev_change"].cast<double>();
  auto tol_dev_ratio = args["tol_dev_ratio"].cast<double>();
  auto path_length = args["path_length"].cast<int>();
  auto alpha_min_ratio = args["alpha_min_ratio"].cast<double>();
  auto max_clusters = args["max_clusters"].cast<int>();

  model.setDevChangeTol(tol_dev_change);
  model.setDevRatioTol(tol_dev_ratio);
  model.setPathLength(path_length);
  model.setMaxClusters(max_clusters);

  if (alpha_min_ratio != -1) {
    model.setAlphaMinRatio(alpha_min_ratio);
  }

  slope::SlopePath path = model.path(x, y, alpha, lambda);

  std::vector<Eigen::SparseMatrix<double>> coefs = path.getCoefs();
  auto intercepts = path.getIntercepts();

  int p = coefs.front().rows();
  int m = coefs.front().cols();
  path_length = path.size();

  py::array_t<double> coefs_out({ p, m, path_length });
  py::array_t<double> intercepts_out({ m, path_length });

  // Get mutable buffers for direct access
  auto coefs_buf = coefs_out.mutable_unchecked<3>();
  auto intercepts_buf = intercepts_out.mutable_unchecked<2>();

  // Fill the arrays with data
  for (int step = 0; step < path_length; step++) {
    Eigen::MatrixXd dense_coefs = coefs[step];

    for (int k = 0; k < m; k++) {
      intercepts_buf(k, step) = intercepts[step](k);

      for (int j = 0; j < p; j++) {
        coefs_buf(j, k, step) = dense_coefs(j, k);
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

Eigen::MatrixXd
_predict(const Eigen::MatrixXd& eta, const std::string& loss_type)
{
  std::unique_ptr<slope::Loss> loss = slope::setupLoss(loss_type);
  return loss->predict(eta);
}

PYBIND11_MODULE(_sortedl1, m)
{
  m.def("fit_slope_dense", &fit_slope_dense);
  m.def("fit_slope_sparse", &fit_slope_sparse);
  m.def("fit_slope_path_dense", &fit_slope_path_dense);
  m.def("fit_slope_path_sparse", &fit_slope_path_sparse);
  m.def("_predict", &_predict);
}
