import unittest

import numpy as np
from numpy.random import default_rng

from sortedl1 import slope


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

        res = slope(x, y, lam, alph)

        np.testing.assert_array_almost_equal(res, 0)


if __name__ == "__main__":
    unittest.main()
