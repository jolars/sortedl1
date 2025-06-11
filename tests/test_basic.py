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

    model = Slope(lam, alpha, centering="mean", scaling="sd", q=0.1)

    model.fit(x, y)

    coef = model.coef_

    coef_true = np.array([-0.16031162, 0.1606755, -0.12518555])

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

    model = Slope(lam, alpha, fit_intercept=False, centering="mean", scaling="sd")

    coef_true = np.array([0.042589, 0.742746, -0.029106])

    model.fit(x_dense, y)
    coef_sparse = model.coef_

    model2 = Slope(lam, alpha, fit_intercept=False, centering="mean", scaling="sd")

    model2.fit(x_sparse, y)
    coef_dense = model2.coef_

    np.testing.assert_array_almost_equal(coef_sparse, coef_dense)
    np.testing.assert_array_almost_equal(coef_dense, coef_true)


def test_logistic():
    """Test case for a simple dense SLOPE problem."""
    n = 10
    p = 5
    rng = default_rng(9)
    x = rng.standard_normal((n, p))

    beta = np.array([1.0, 2, -0.9, 0, 0])

    y = x @ beta
    y = np.where(y > 0, 1, 0)

    lam = np.array([3, 2.5, 2, 1, 0.2])
    alpha = 0.02

    model = Slope(lam, alpha, centering="mean", scaling="sd", loss="logistic", tol=1e-6)

    _ = model.fit(x, y)

    coef = model.coef_

    coef_true = np.array([0.0, 1.148466, -1.171151, 0.342722, -0.409017])

    np.testing.assert_array_almost_equal(coef, coef_true)


def test_oscar():
    """Test case for OSCAR."""
    n = 10
    p = 5

    rng = default_rng(4)
    x = rng.standard_normal((n, p))

    beta = rng.standard_normal(p)

    y = x @ beta

    alpha = 0.1

    model = Slope(
        alpha=alpha,
        centering="mean",
        scaling="sd",
        theta1=0.1,
        theta2=2,
        lambda_type="oscar",
    )

    model.fit(x, y)

    coef = model.coef_

    coef_true = np.array([0.0, 0.13789, -0.279516, 0.0, 0.0])

    np.testing.assert_array_almost_equal(coef, coef_true)
