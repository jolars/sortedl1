import unittest

import numpy as np
from numpy.random import default_rng

from sortedl1 import Slope


class TestBasicUse(unittest.TestCase):
    def test_simple_problem(self):
        n = 10
        p = 3
        rng = default_rng(9)
        x = rng.standard_normal((n, p))

        beta = np.array([1.0, 2, -0.9])

        y = x @ beta

        lam = np.array([2, 1, 0.2])
        alph = np.array([1.0])

        model = Slope(alph, lam)

        res = model.fit(x, y).predict(x)

        np.testing.assert_array_almost_equal(res, np.array([0.0, 1.0]))


if __name__ == "__main__":
    unittest.main()
