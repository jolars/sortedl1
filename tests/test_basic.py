"""Basics tests for the slope function."""

import unittest

import numpy as np
from numpy.random import default_rng

from sortedl1 import Slope


class TestBasicUse(unittest.TestCase):
    """
    A class used to test the basic use of the Slope model.

    ...

    Attributes
    ----------
    None

    Methods
    -------
    test_simple_problem():
        Tests a simple problem using the Slope model.
    """

    def test_simple_problem(self):
        """
        Tests a simple problem using the Slope model.

        This method generates a random dataset using the numpy random module,
        creates a Slope model with specific parameters, fits the model to the
        generated data, and then checks if the model's coefficients are almost
        equal to the expected coefficients.

        Parameters
        ----------
        None

        Returns
        -------
        None
        """
        n = 10
        p = 3
        rng = default_rng(4)
        x = rng.standard_normal((n, p))

        beta = np.array([1.0, 2, -0.9])

        y = x @ beta

        lam = np.array([2, 1, 0.2])
        alpha = 1.0

        model = Slope(lam, alpha, standardize=True)

        model.fit(x, y)

        coef = model.coef_

        coef_true = np.array([[-0.16031162], [0.1606755], [-0.12518555]])

        np.testing.assert_array_almost_equal(coef, coef_true)


if __name__ == "__main__":
    unittest.main()
