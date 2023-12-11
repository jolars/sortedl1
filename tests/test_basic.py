"""Basics tests for the slope function."""

import unittest

import numpy as np
from numpy.random import default_rng
from scipy.sparse import random

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
        Tests a simple problem using the Slope model for dense input.

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

    def test_simple_sparse_problem(self):
        """
        Tests a simple problem using the Slope model for sparse input.

        Parameters
        ----------
        None

        Returns
        -------
        None
        """
        n = 10
        p = 3

        rng = np.random.default_rng(4)
        x = random(n, p, density=0.5, random_state=rng)
        beta = np.array([1.0, 2, -0.9])
        y = x @ beta

        lam = np.array([0.5, 0.5, 0.2])
        alpha = 1.0

        model = Slope(lam, alpha, standardize=True)

        model.fit(x, y)

        coef = model.coef_
        coef_true = np.array([[0.03459716], [0.69168031], [-0.02195692]])

        np.testing.assert_array_almost_equal(coef, coef_true)

    def test_failing_problem(self):
        """
        Test a problem with automatic lambda selection.

        Parameters
        ----------
        None

        Returns
        -------
        None
        """
        n = 100
        p = 3

        seed = 31
        rng = default_rng(seed)

        x = rng.standard_normal((n, p))
        beta = rng.standard_normal(p)
        y = x @ beta + rng.standard_normal(n)

        model = Slope(alpha=1.0)
        model.fit(x, y)


if __name__ == "__main__":
    unittest.main()
