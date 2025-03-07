/**
 * @internal
 * @file
 * @brief Definitions of constants used in libslope
 */

#pragma once

#include <limits>
namespace slope {
namespace constants {

constexpr double EPSILON = 1e-10;
constexpr double P_MIN = 1e-9;
constexpr double P_MAX = 1.0 - P_MIN;
constexpr double POS_INF = std::numeric_limits<double>::max();
constexpr double NEG_INF = std::numeric_limits<double>::lowest();

} // namespace constants
} // namespace slope
