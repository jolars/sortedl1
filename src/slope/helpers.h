/**
 * @internal
 * @file
 * @brief Internal helper functions for printing and more
 */

#pragma once

#include <Eigen/Core>
#include <iostream>
#include <string>

/**
 * @internal
 * Prints the contents of a container to the standard output.
 *
 * @tparam T The type of the container.
 * @param x The container to print.
 * @param what An optional string to prefix the output with.
 */
template<typename T>
void
printContents(const T& x, const std::string what = "")
{
  if (what != "") {
    std::cout << what << ": ";
  }

  int n = x.size();
  for (int i = 0; i < n; ++i) {
    std::cout << x[i] << " ";
  }

  std::cout << std::endl;
}

/**
 * @internal
 * @brief This function takes an integer level and returns a string of spaces
 *        that represents the indentation level.
 *
 * @param level The indentation level to be represented.
 * @return std::string A string of spaces representing the indentation level.
 */
std::string
indent(const int level);
