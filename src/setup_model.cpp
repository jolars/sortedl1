#include "setup_model.h"

slope::Slope
setup_model(const pybind11::dict& args)
{
  using Eigen::ArrayXd;
  using Eigen::VectorXd;

  // auto alpha = as<ArrayXd>(control["alpha"]);
  // auto alpha_type = as<std::string>(control["alpha_type"]);
  auto centering_type = args["centering"].cast<std::string>();
  // auto centers = as<VectorXd>(control["centers"]);
  // auto diagnostics = as<bool>(control["diagnostics"]);
  auto intercept = args["intercept"].cast<bool>();
  // auto lambda = as<ArrayXd>(control["lambda"]);
  auto lambda_type = args["lambda_type"].cast<std::string>();
  auto loss_type = args["loss"].cast<std::string>();
  auto max_it = args["max_it"].cast<int>();
  auto q = args["q"].cast<double>();
  // auto scales = as<VectorXd>(control["scales"]);
  auto scaling_type = args["scaling"].cast<std::string>();
  auto solver_type = args["solver"].cast<std::string>();
  auto theta1 = args["theta1"].cast<double>();
  auto theta2 = args["theta2"].cast<double>();
  auto tol = args["tol"].cast<double>();

  slope::Slope model;

  // model.setAlphaType(alpha_type);
  model.setIntercept(intercept);
  // model.setMaxClusters(max_clusters);
  model.setMaxIterations(max_it);
  model.setLoss(loss_type);
  model.setOscarParameters(theta1, theta2);
  model.setQ(q);
  model.setSolver(solver_type);
  model.setTol(tol);
  // model.setDiagnostics(diagnostics);
  //
  // if (centering_type == "manual") {
  //   model.setCentering(centers);
  // } else {
  model.setCentering(centering_type);
  // }

  if (lambda_type != "user") {
    model.setLambdaType(lambda_type);
  }

  // if (scaling_type == "manual") {
  //   model.setScaling(scales);
  // } else {
  model.setScaling(scaling_type);
  // }

  return model;
}
