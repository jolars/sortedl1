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

find_package(Eigen3 3.4 QUIET)
if(NOT Eigen3_FOUND)
    FetchContent_Declare(
        Eigen3
        GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
        GIT_TAG 3.4.0
        GIT_SHALLOW TRUE
    )
    FetchContent_MakeAvailable(Eigen3)
endif()

find_package(slope QUIET)
if(NOT slope_FOUND)
    FetchContent_Declare(
        slope
        GIT_REPOSITORY https://github.com/jolars/libslope
        GIT_TAG e1cad5314fa72a63c423fd45e950a2f7db1478a6
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
