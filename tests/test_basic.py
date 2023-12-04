import unittest

import numpy as np
from numpy.random import default_rng

from sortedl1 import Slope


class TestBasicUse(unittest.TestCase):
    def test_simple_problem(self):
        n = 10
        p = 3
        rng = default_rng(4)
        x = rng.standard_normal((n, p))

        beta = np.array([1.0, 2, -0.9])

        y = x @ beta

        lam = np.array([2, 1, 0.2])
        alpha = np.asarray(1.0)

        model = Slope(lam, alpha, standardize=True)

        model.fit(x, y)

        coef = model.coef_

        coef_true = np.array([[-0.16031162], [0.1606755], [-0.12518555]])

        np.testing.assert_array_almost_equal(coef, coef_true)


if __name__ == "__main__":
    unittest.main()
