#pragma once

#include <pybind11/pybind11.h>
#include <slope/slope.h>

slope::Slope
setup_model(const pybind11::dict& args);
