"""Basic tests for the sortedl1 package."""

import numpy as np
from numpy.random import default_rng
from scipy.sparse import csc_array, random

from sortedl1 import Slope


def test_path():
    """Test case for a simple dense SLOPE problem."""
    n = 100
    p = 30
    rng = default_rng(9)
    x = rng.standard_normal((n, p))

    beta = rng.standard_normal((p, 1))

    y = x @ beta

    model = Slope()

    coefs, intercepts, _, _ = model.path(x, y.ravel())

    assert coefs.shape[0] == p
    assert coefs.shape[1] == 1
    assert intercepts.shape[0] == 1
