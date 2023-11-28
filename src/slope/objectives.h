#pragma once

#include <Eigen/Core>
#include <memory>

namespace slope {

class Objective
{
public:
  virtual ~Objective() = default;

  virtual double loss(const Eigen::VectorXd& eta, const Eigen::MatrixXd& y) = 0;

  virtual void updateWeightsAndWorkingResponse(
    Eigen::VectorXd& weights,
    Eigen::VectorXd& working_response,
    const Eigen::VectorXd& eta,
    const Eigen::MatrixXd& y) = 0;
};

class Gaussian : public Objective
{
public:
  double loss(const Eigen::VectorXd& eta, const Eigen::MatrixXd& y);

  void updateWeightsAndWorkingResponse(Eigen::VectorXd& w,
                                       Eigen::VectorXd& z,
                                       const Eigen::VectorXd& eta,
                                       const Eigen::MatrixXd& y);
};

class Binomial : public Objective
{
private:
  double p_min = 1e-5;

public:
  double loss(const Eigen::VectorXd& eta, const Eigen::MatrixXd& y);

  void updateWeightsAndWorkingResponse(Eigen::VectorXd& w,
                                       Eigen::VectorXd& z,
                                       const Eigen::VectorXd& eta,
                                       const Eigen::MatrixXd& y);
};

std::unique_ptr<Objective>
setupObjective(const std::string family);

} // namespace slope
