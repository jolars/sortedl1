#include "setup_model.h"

slope::Slope
setup_model(const pybind11::dict& args)
{
  using Eigen::ArrayXd;
  using Eigen::VectorXd;

  // auto alpha = as<ArrayXd>(control["alpha"]);
  // auto alpha_min_ratio = as<double>(control["alpha_min_ratio"]);
  // auto alpha_type = as<std::string>(control["alpha_type"]);
  auto centering_type = args["centering"].cast<std::string>();
  // auto centers = as<VectorXd>(control["centers"]);
  // auto diagnostics = as<bool>(control["diagnostics"]);
  auto intercept = args["intercept"].cast<bool>();
  // auto lambda = as<ArrayXd>(control["lambda"]);
  // auto lambda_type = as<std::string>(control["lambda_type"]);
  // auto loss_type = as<std::string>(control["family"]);
  // auto max_clusters = as<int>(control["max_variables"]);
  auto max_it = args["max_it"].cast<int>();
  // auto path_length = as<int>(control["path_length"]);
  // auto q = as<double>(control["q"]);
  // auto scales = as<VectorXd>(control["scales"]);
  auto scaling_type = args["scaling"].cast<std::string>();
  // auto solver_type = as<std::string>(control["solver"]);
  // auto theta1 = as<double>(control["theta1"]);
  // auto theta2 = as<double>(control["theta2"]);
  auto tol = args["tol"].cast<double>();
  // auto tol_dev_change = as<double>(control["tol_dev_change"]);
  // auto tol_dev_ratio = as<double>(control["tol_dev_ratio"]);

  slope::Slope model;

  // Map family to loss_type
  // if (loss_type == "gaussian") {
  //   loss_type = "quadratic";
  // } else if (loss_type == "binomial") {
  //   loss_type = "logistic";
  // }

  // overwrite solver type for Poisson regression,
  // since the hybrid solver has convergence issues for this
  // objective
  // if (solver_type == "auto") {
  //   if (loss_type == "poisson") {
  //     solver_type = "fista";
  //   }
  // }

  // model.setAlphaMinRatio(alpha_min_ratio);
  // model.setAlphaType(alpha_type);
  // model.setDevChangeTol(tol_dev_change);
  // model.setDevRatioTol(tol_dev_ratio);
  model.setIntercept(intercept);
  // model.setMaxClusters(max_clusters);
  model.setMaxIterations(max_it);
  // model.setLoss(loss_type);
  // model.setOscarParameters(theta1, theta2);
  // model.setPathLength(path_length);
  // model.setQ(q);
  // model.setSolver(solver_type);
  model.setTol(tol);
  // model.setDiagnostics(diagnostics);
  //
  // if (centering_type == "manual") {
  //   model.setCentering(centers);
  // } else {
  model.setCentering(centering_type);
  // }
  //
  // if (lambda_type != "user") {
  //   model.setLambdaType(lambda_type);
  // }
  //
  // if (scaling_type == "manual") {
  //   model.setScaling(scales);
  // } else {
  model.setScaling(scaling_type);
  // }

  return model;
}
