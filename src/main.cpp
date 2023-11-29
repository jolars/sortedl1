#include "slope/slope.h"
#include <Eigen/Core>
#include <Eigen/LU>
#include <pybind11/eigen.h>
#include <pybind11/pybind11.h>

int
fit_slope(const Eigen::MatrixXd x,
          const Eigen::MatrixXd y,
          Eigen::ArrayXd lambda,
          Eigen::ArrayXd alpha)
{
  auto result = slope::slope(x, y, alpha, lambda);

  return 0;
}

PYBIND11_MODULE(_sortedl1, m)
{
  m.def("fit_slope", &fit_slope);
}
