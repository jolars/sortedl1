# Require CMake 3.15+ (matching scikit-build-core) Use new versions of all
# policies up to CMake 3.27
cmake_minimum_required(VERSION 3.15...3.27)

# Scikit-build-core sets these values for you, or you can just hard-code the
# name and version.
project(
  ${SKBUILD_PROJECT_NAME}
  VERSION ${SKBUILD_PROJECT_VERSION}
  LANGUAGES CXX)

# set(CMAKE_CXX_STANDARD 17) set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find the module development requirements (requires FindPython from 3.17 or
# scikit-build-core's built-in backport)
find_package(Python REQUIRED COMPONENTS Interpreter Development.Module)
find_package(pybind11 CONFIG REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/external)

# Add a library using FindPython's tooling (pybind11 also provides a helper like
# this) python_add_library(_sortedl1 MODULE src/main.cpp WITH_SOABI)
# target_link_libraries(_sortedl1 PRIVATE pybind11::headers)
#

pybind11_add_module(
  _sortedl1
  src/main.cpp
  src/slope/qnorm.cpp
  src/slope/helpers.cpp
  src/slope/objectives.cpp
  src/slope/clusters.cpp
  src/slope/slope.cpp
  src/slope/regularization_sequence.cpp
  src/slope/slope_threshold.cpp
  src/slope/sorted_l1_norm.cpp
  src/slope/standardize.cpp)

# The install directory is the output (wheel) directory
install(TARGETS _sortedl1 LIBRARY DESTINATION .)
