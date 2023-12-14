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


def test_simple_sparse_problem():
    """Test case for a simple sparse SLOPE problem."""
    n = 10
    p = 3

    rng = np.random.default_rng(4)
    x = csc_array(random(n, p, density=0.5, random_state=rng))
    beta = np.array([1.0, 2, -0.9])
    y = x @ beta

    lam = np.array([0.5, 0.5, 0.2])
    alpha = 1.0

    model = Slope(lam, alpha, standardize=True)

    model.fit(x, y)

    coef = model.coef_
    coef_true = np.array([[0.03459716], [0.69168031], [-0.02195692]])

    np.testing.assert_array_almost_equal(coef, coef_true)


def test_failing_problem():
    """Test care for problem that failed at some point."""
    n = 100
    p = 3

    seed = 31
    rng = default_rng(seed)

    x = rng.standard_normal((n, p))
    beta = rng.standard_normal(p)
    y = x @ beta + rng.standard_normal(n)

    model = Slope(alpha=1.0)
    model.fit(x, y)
