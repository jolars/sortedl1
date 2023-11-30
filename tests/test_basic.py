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
        alph = np.asarray(1.0)

        model = Slope(lam, alph)

        pred = model.fit(x, y).predict(x)

        pred_true = np.array(
            [
                [0.70852434],
                [1.64431936],
                [0.81548688],
                [-3.1140118],
                [1.04592253],
                [-1.23005169],
                [0.92314128],
                [-2.58331539],
                [-0.93066588],
                [0.63115334],
            ]
        )

        np.testing.assert_array_almost_equal(pred, pred_true)


if __name__ == "__main__":
    unittest.main()
