cmake_minimum_required(VERSION 3.15...4.0)

project(
    ${SKBUILD_PROJECT_NAME}
    VERSION ${SKBUILD_PROJECT_VERSION}
    LANGUAGES CXX
)

set(PYBIND11_FINDPYTHON ON)
find_package(pybind11 CONFIG REQUIRED)

# Force -fPIC for the slope library (required for shared libraries)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Disable building tests for all dependencies
set(BUILD_TESTING OFF CACHE BOOL "Disable testing" FORCE)

include(FetchContent)

find_package(Eigen3 5.0.1 QUIET)
if(NOT Eigen3_FOUND)
    FetchContent_Declare(
        Eigen3
        URL https://gitlab.com/libeigen/eigen/-/archive/5.0.1/eigen-5.0.1.tar.gz
        URL_HASH SHA256=e9c326dc8c05cd1e044c71f30f1b2e34a6161a3b6ecf445d56b53ff1669e3dec
    )
    # libslope needs Eigen's CMake package even when Eigen is a subproject.
    set(EIGEN_BUILD_CMAKE_PACKAGE ON)
    FetchContent_MakeAvailable(Eigen3)
    set(Eigen3_DIR "${eigen3_BINARY_DIR}")
endif()

find_package(slope QUIET)
if(NOT slope_FOUND)
    FetchContent_Declare(
        slope
        GIT_REPOSITORY https://github.com/jolars/libslope.git
        GIT_TAG v6.5.3
        GIT_SHALLOW TRUE
    )
    FetchContent_MakeAvailable(slope)
endif()

pybind11_add_module(
  _sortedl1
  src/main.cpp
  src/setup_model.cpp
)

target_link_libraries(_sortedl1 PRIVATE slope::slope)
target_include_directories(_sortedl1 PRIVATE include)

install(TARGETS _sortedl1 LIBRARY DESTINATION .)
