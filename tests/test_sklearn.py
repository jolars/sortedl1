import numpy as np
from numpy.random import default_rng
from sklearn.model_selection import GridSearchCV
from sklearn.utils.estimator_checks import check_estimator

from sortedl1 import Slope


def test_sklearn_integration():
    mod = Slope()
    check_estimator(mod, on_skip=None)


def test_grid_search_cv_regression():
    rng = default_rng(0)
    X = rng.standard_normal((50, 10))
    y = X[:, 0] + rng.standard_normal(50)

    search = GridSearchCV(Slope(), {"alpha": [0.01, 0.1, 1.0]}, cv=3).fit(X, y)

    assert "alpha" in search.best_params_
    assert np.isfinite(search.best_score_)


def test_grid_search_cv_logistic():
    rng = default_rng(0)
    X = rng.standard_normal((50, 10))
    y = (X[:, 0] > 0).astype(int)

    search = GridSearchCV(
        Slope(loss="logistic"), {"alpha": [0.01, 0.1, 1.0]}, cv=3
    ).fit(X, y)

    assert "alpha" in search.best_params_
    assert 0.0 <= search.best_score_ <= 1.0


def test_score_regression_perfect_fit():
    rng = default_rng(0)
    X = rng.standard_normal((50, 5))
    y = X[:, 0] + rng.standard_normal(50)

    model = Slope(alpha=0.0).fit(X, y)
    score = model.score(X, y)

    assert isinstance(score, float)
    assert score <= 1.0


def test_score_logistic_in_unit_interval():
    rng = default_rng(0)
    X = rng.standard_normal((50, 5))
    y = (X[:, 0] > 0).astype(int)

    model = Slope(loss="logistic", alpha=0.01).fit(X, y)
    score = model.score(X, y)

    assert 0.0 <= score <= 1.0
