cmake_minimum_required(VERSION 3.15...4.0)

project(
    ${SKBUILD_PROJECT_NAME}
    VERSION ${SKBUILD_PROJECT_VERSION}
    LANGUAGES CXX
)

set(PYBIND11_FINDPYTHON ON)
find_package(pybind11 CONFIG REQUIRED)

set(OpenMP_RUNTIME_MSVC "llvm")
find_package(OpenMP)
if(OpenMP_FOUND)
    message(STATUS "OpenMP found: ${OpenMP_CXX_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

include_directories(include)

include(FetchContent)

# Force -fPIC for the slope library (required for shared libraries)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Disable building tests for all dependencies
set(BUILD_TESTING OFF CACHE BOOL "Disable testing" FORCE)
set(EIGEN_BUILD_TESTING OFF CACHE BOOL "Disable Eigen tests" FORCE)

FetchContent_Declare(
    Eigen3
    GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
    GIT_TAG 3.4.1
    GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(Eigen3)

FetchContent_Declare(
    slope
    GIT_REPOSITORY https://github.com/jolars/libslope
    GIT_TAG v6.3.0
    GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(slope)

pybind11_add_module(
  _sortedl1
  src/main.cpp
  src/setup_model.cpp
)
target_link_libraries(_sortedl1 PRIVATE slope)

install(TARGETS _sortedl1 LIBRARY DESTINATION .)
