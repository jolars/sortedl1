"""Cross-validation tests."""

from numpy.random import default_rng

from sortedl1 import Slope


def test_cv():
    """Test case for simple CV."""
    n = 100
    p = 30
    rng = default_rng(11)
    x = rng.standard_normal((n, p))

    beta = rng.standard_normal((p, 1))

    y = x @ beta

    model = Slope()

    res = model.cv(x, y.ravel())

    assert type(res.metric) is str


def test_cv_plot():
    n = 100
    p = 30
    rng = default_rng(11)
    x = rng.standard_normal((n, p))

    beta = rng.standard_normal((p, 1))

    y = x @ beta

    model = Slope()

    res = model.cv(x, y.ravel())

    fig, ax = res.plot()

    assert fig.__class__.__name__ == "Figure"
