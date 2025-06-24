"""Basic tests for the sortedl1 package."""

from numpy.random import default_rng

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


def test_path_plot():
    """Test case for a simple dense SLOPE problem."""
    n = 90
    p = 200
    rng = default_rng(37)
    x = rng.standard_normal((n, p))
    beta = rng.standard_normal((p, 1))
    y = x @ beta

    model = Slope()

    res = model.path(x, y.ravel())

    fig, ax = res.plot()

    assert fig.__class__.__name__ == "Figure"

    lines = ax.get_lines()
    assert len(lines) > 0
