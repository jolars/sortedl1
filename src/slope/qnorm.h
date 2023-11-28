#include <array>
#include <cmath>
#include <sstream>

namespace slope {

/**
 * Computes the quantile of a standard normal distribution using the
 * Beasley-Springer-Moro algorithm.
 *
 * @param p Probability value
 * @return Quantile
 */
double
normalQuantile(const double p);

} // namespace slope
