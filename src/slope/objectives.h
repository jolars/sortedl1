/**
 * @file
 * @brief The declartion of the Objctive class and its subclasses, which
 * represent the data-fitting part of the composite objective function.
 */

#pragma once

#include <Eigen/Core>
#include <memory>

namespace slope {

/**
 * Abstract class representing an objective function.
 *
 * This class defines the interface for an objective function, which is used in
 * optimization algorithms. The objective function calculates the loss, dual,
 * residual, and updates the weights and working response.
 */
class Objective
{
public:
  /**
   * @brief Destructor for the Objective class.
   */
  virtual ~Objective() = default;

  /**
   * @brief Calculates the loss function
   *
   * This function calculates the loss function given the predicted values (eta)
   * and the true values (y).
   *
   * @param eta The predicted values.
   * @param y The true values.
   * @return The loss value.
   */
  virtual double loss(const Eigen::VectorXd& eta, const Eigen::MatrixXd& y) = 0;

  /**
   * @brief Calculates the dual objective
   *
   * This function calculates the dual function given the estimated parameters
   * (theta) and the true values (y).
   *
   * @param theta The estimated parameters.
   * @param y The true values.
   * @return The dual value.
   */
  virtual double dual(const Eigen::VectorXd& theta,
                      const Eigen::VectorXd& y) = 0;

  /**
   * @brief Calculates the residual
   *
   * This function calculates the residual given the predicted values (eta) and
   * the true values (y).
   *
   * @param eta The predicted values.
   * @param y The true values.
   * @return The residual vector.
   */
  virtual Eigen::VectorXd residual(const Eigen::VectorXd& eta,
                                   const Eigen::VectorXd& y) = 0;

  /**
   * @brief Updates the weights and working response
   *
   * This function updates the weights and working response given the predicted
   * values (eta) and the true values (y).
   *
   * @param weights The weights to be updated.
   * @param working_response The working response to be updated.
   * @param eta The predicted values.
   * @param y The true values.
   */
  virtual void updateWeightsAndWorkingResponse(
    Eigen::VectorXd& weights,
    Eigen::VectorXd& working_response,
    const Eigen::VectorXd& eta,
    const Eigen::MatrixXd& y) = 0;
};

/**
 * @class Gaussian
 * @brief The Gaussian class represents a Gaussian objective function.
 */
class Gaussian : public Objective
{
public:
  /**
   * @brief Calculates the loss function for the Gaussian objective.
   * @param eta The predicted values.
   * @param y The actual values.
   * @return The loss value.
   */
  double loss(const Eigen::VectorXd& eta, const Eigen::MatrixXd& y);

  /**
   * @brief Calculates the dual function for the Gaussian objective.
   * @param theta The dual variables.
   * @param y The actual values.
   * @return The dual value.
   */
  double dual(const Eigen::VectorXd& theta, const Eigen::VectorXd& y);

  /**
   * @brief Calculates the residuals for the Gaussian objective.
   * @param eta The predicted values.
   * @param y The actual values.
   * @return The residuals.
   */
  Eigen::VectorXd residual(const Eigen::VectorXd& eta,
                           const Eigen::VectorXd& y);

  /**
   * @brief Updates the weights and working response for the Gaussian objective.
   * @param w The weights.
   * @param z The working response.
   * @param eta The predicted values.
   * @param y The actual values.
   */
  void updateWeightsAndWorkingResponse(Eigen::VectorXd& w,
                                       Eigen::VectorXd& z,
                                       const Eigen::VectorXd& eta,
                                       const Eigen::MatrixXd& y);
};

/**
 * @class Binomial
 * @brief The Binomial class represents a binomial objective function.
 * @details The binomial objective function is used for binary classification
 * problems. It calculates the loss, dual, residual, and updates weights and
 * working response.
 */
class Binomial : public Objective
{
private:
  double p_min = 1e-5; /**< The minimum probability value. */

public:
  /**
   * @brief Calculates the loss for the binomial objective function.
   * @param eta The predicted values.
   * @param y The true labels.
   * @return The loss value.
   */
  double loss(const Eigen::VectorXd& eta, const Eigen::MatrixXd& y);

  /**
   * @brief Calculates the dual for the binomial objective function.
   * @param theta The dual variables.
   * @param y The true labels.
   * @return The dual value.
   */
  double dual(const Eigen::VectorXd& theta, const Eigen::VectorXd& y);

  /**
   * @brief Calculates the residual for the binomial objective function.
   * @param eta The predicted values.
   * @param y The true labels.
   * @return The residual vector.
   */
  Eigen::VectorXd residual(const Eigen::VectorXd& eta,
                           const Eigen::VectorXd& y);

  /**
   * @brief Updates the weights and working response for the binomial objective
   * function.
   * @param w The weights.
   * @param z The working response.
   * @param eta The predicted values.
   * @param y The true labels.
   */
  void updateWeightsAndWorkingResponse(Eigen::VectorXd& w,
                                       Eigen::VectorXd& z,
                                       const Eigen::VectorXd& eta,
                                       const Eigen::MatrixXd& y);
};

/**
 * @brief Sets up the objective function based on the given family.
 * @param family The family of the objective function.
 * @return A unique pointer to the objective function.
 */
std::unique_ptr<Objective>
setupObjective(const std::string family);

} // namespace slope
