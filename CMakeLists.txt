# Require CMake 3.15+ (matching scikit-build-core) Use new versions of all
# policies up to CMake 3.27
cmake_minimum_required(VERSION 3.15...3.29)

# Scikit-build-core sets these values for you, or you can just hard-code the
# name and version.
project(
    ${SKBUILD_PROJECT_NAME}
    VERSION ${SKBUILD_PROJECT_VERSION}
    LANGUAGES CXX
)

# Find the module development requirements (requires FindPython from 3.17 or
# scikit-build-core's built-in backport)
set(PYBIND11_FINDPYTHON ON)
find_package(pybind11 CONFIG REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/external)

# Add a library using FindPython's tooling (pybind11 also provides a helper like
# this) python_add_library(_sortedl1 MODULE src/main.cpp WITH_SOABI)
# target_link_libraries(_sortedl1 PRIVATE pybind11::headers)

pybind11_add_module(
  _sortedl1
  src/main.cpp
  src/setup_model.cpp
  src/slope/clusters.cpp
  src/slope/cv.cpp
  src/slope/folds.cpp
  src/slope/kkt_check.cpp
  src/slope/logger.cpp
  src/slope/losses/loss.cpp
  src/slope/losses/logistic.cpp
  src/slope/losses/multinomial.cpp
  src/slope/losses/poisson.cpp
  src/slope/losses/quadratic.cpp
  src/slope/losses/setup_loss.cpp
  src/slope/math.cpp
  src/slope/normalize.cpp
  src/slope/qnorm.cpp
  src/slope/regularization_sequence.cpp
  src/slope/score.cpp
  src/slope/screening.cpp
  src/slope/slope.cpp
  src/slope/solvers/hybrid.cpp
  src/slope/solvers/hybrid_cd.cpp
  src/slope/solvers/pgd.cpp
  src/slope/solvers/setup_solver.cpp
  src/slope/solvers/slope_threshold.cpp
  src/slope/sorted_l1_norm.cpp
  src/slope/timer.cpp
  src/slope/utils.cpp
)

# The install directory is the output (wheel) directory
install(TARGETS _sortedl1 LIBRARY DESTINATION .)
