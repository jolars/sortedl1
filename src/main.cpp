#include "slope/slope.h"
#include <Eigen/Core>
#include <Eigen/LU>
#include <pybind11/eigen.h>
#include <pybind11/pybind11.h>

#define STRINGIFY(x) #x
#define MACRO_STRINGIFY(x) STRINGIFY(x)

int
fit_slope(const Eigen::MatrixXd x,
          const Eigen::MatrixXd y,
          Eigen::ArrayXd lambda,
          Eigen::ArrayXd alpha)
{
  auto result = slope::slope(x, y, alpha, lambda);

  return 0;
}

namespace py = pybind11;

PYBIND11_MODULE(_sortedl1, m)
{
  m.doc() = R"pbdoc(
        Pybind11 example plugin
        -----------------------

        .. currentmodule:: _sortedl1

        .. autosummary::
           :toctree: _generate

           fit_slope
    )pbdoc";

  m.def("fit_slope", &fit_slope, R"pbdoc(
        Fit SLOPE
        ---------------

        Let's fit SLOPE!
    )pbdoc");

#ifdef VERSION_INFO
  m.attr("__version__") = MACRO_STRINGIFY(VERSION_INFO);
#else
  m.attr("__version__") = "dev";
#endif
}
