"""Basic tests for the sortedl1 package."""
import numpy as np
from numpy.random import default_rng
from scipy.sparse import csc_array, random

from sortedl1 import Slope


def test_simple_problem():
    """Test case for a simple dense SLOPE problem."""
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


def test_sparse_dense_standardized():
    """Test case for checking standardization works for both sparse and dense."""
    x_dense = np.array(
        [
            [0.0, 0.13339576, 0.49361983],
            [0.17769259, 0.66565742, 0.36972579],
            [0.0, 0.0, 0.0],
            [0.0, 0.0, 0.94280368],
            [0.0, 0.0, 0.3499374],
            [0.0, 0.22377115, 0.0],
            [0.0, 0.96893287, 0.95858229],
            [0.70486475, 0.60885162, 0.0],
            [0.0, 0.92902639, 0.0],
            [0.4978676, 0.0, 0.50022619],
        ]
    )

    x_sparse = csc_array(x_dense)

    beta = np.array([1.0, 2, -0.9])
    y = x_dense @ beta

    lam = np.array([0.5, 0.5, 0.2])
    alpha = 1.0

    model = Slope(lam, alpha, standardize=True, fit_intercept=False)

    coef_true = np.array([[0.04258934], [0.74274634], [-0.02910647]])

    model.fit(x_dense, y)
    coef_sparse = model.coef_

    model2 = Slope(lam, alpha, standardize=True, fit_intercept=False)

    model2.fit(x_sparse, y)
    coef_dense = model2.coef_

    np.testing.assert_array_almost_equal(coef_sparse, coef_dense)
    np.testing.assert_array_almost_equal(coef_dense, coef_true)
