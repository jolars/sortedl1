#pragma once

#include "slope/slope.h"
#include <pybind11/pybind11.h>

slope::Slope
setup_model(const pybind11::dict& args);
