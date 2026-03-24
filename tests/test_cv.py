"""Cross-validation tests."""

from typing import cast

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

    fig, _ax = res.plot()

    assert fig.__class__.__name__ == "Figure"


def test_cv_summary_and_repr():
    n = 100
    p = 30
    rng = default_rng(11)
    x = rng.standard_normal((n, p))
    beta = rng.standard_normal((p, 1))
    y = x @ beta

    model = Slope()
    res = model.cv(x, y.ravel())

    summary = cast(dict[str, object], res.summary())

    assert summary["metric"] == res.metric
    assert summary["n_param_sets"] == res.n_param_sets
    assert summary["best_ind"] == int(res.best_ind)
    assert summary["best_alpha_ind"] == int(res.best_alpha_ind)
    assert summary["best_alpha"] == res.best_alpha

    rep = repr(res)
    assert "CvResults(" in rep
    assert "metric=" in rep
    assert "best_score=" in rep
    assert "best_alpha=" in rep


def test_cv_refit_returns_best_model():
    n = 100
    p = 30
    rng = default_rng(11)
    x = rng.standard_normal((n, p))
    beta = rng.standard_normal((p, 1))
    y = x @ beta

    model = Slope()
    cv_res, best_model = model.cv(
        x,
        y.ravel(),
        q=[0.1, 0.2],
        gamma=[0.0, 1.0],
        refit=True,
    )

    assert type(cv_res.metric) is str
    assert isinstance(best_model, Slope)
    assert hasattr(best_model, "coef_")
    assert hasattr(best_model, "intercept_")
    assert best_model.n_features_in_ == p
