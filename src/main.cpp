#include "setup_model.h"
#include "slope/cv.h"
#include "slope/slope.h"
#include <Eigen/Core>
#include <Eigen/SparseCore>
#include <pybind11/eigen.h>
#include <pybind11/iostream.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

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

  if (max_clusters != -1) {
    model.setMaxClusters(max_clusters);
  }

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

template<typename T>
pybind11::tuple
cv_slope(T& x,
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

  if (max_clusters != -1) {
    model.setMaxClusters(max_clusters);
  }

  if (alpha_min_ratio != -1) {
    model.setAlphaMinRatio(alpha_min_ratio);
  }

  auto cv_config = slope::CvConfig();

  std::map<std::string, std::vector<double>> hyperparams;
  hyperparams["q"] = args["cv_q"].cast<std::vector<double>>();
  hyperparams["gamma"] = args["cv_gamma"].cast<std::vector<double>>();

  cv_config.hyperparams = hyperparams;
  cv_config.metric = args["metric"].cast<std::string>();
  cv_config.predefined_folds =
    args["predefined_folds"].cast<std::vector<std::vector<std::vector<int>>>>();

  auto res = crossValidate(model, x, y, cv_config);

  int n_slices = res.results.size();

  std::vector<Eigen::MatrixXd> scores;
  std::vector<Eigen::ArrayXd> means;
  std::vector<Eigen::ArrayXd> errors;
  std::vector<Eigen::ArrayXd> alphas;
  std::vector<std::map<std::string, double>> params;

  for (int k = 0; k < n_slices; k++) {
    const auto& grid_result = res.results[k];

    scores.emplace_back(grid_result.score);
    means.emplace_back(grid_result.mean_scores);
    errors.emplace_back(grid_result.std_errors);
    alphas.emplace_back(grid_result.alphas);
    params.emplace_back(grid_result.params);
  }

  return py::make_tuple(res.best_score,
                        res.best_ind,
                        res.best_alpha_ind,
                        scores,
                        means,
                        errors,
                        alphas,
                        params);
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

pybind11::tuple
cv_slope_dense(Eigen::SparseMatrix<double>& x,
               const Eigen::MatrixXd& y,
               const Eigen::ArrayXd& lambda,
               const Eigen::ArrayXd& alpha,
               const py::dict& args)
{
  return cv_slope(x, y, lambda, alpha, args);
}

pybind11::tuple
cv_slope_sparse(Eigen::MatrixXd& x,
                const Eigen::MatrixXd& y,
                const Eigen::ArrayXd& lambda,
                const Eigen::ArrayXd& alpha,
                const py::dict& args)
{
  return cv_slope(x, y, lambda, alpha, args);
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
  m.def("cv_slope_dense", &cv_slope_dense);
  m.def("cv_slope_sparse", &cv_slope_sparse);
  m.def("_predict", &_predict);
}
