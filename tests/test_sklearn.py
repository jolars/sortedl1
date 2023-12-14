from sklearn.utils.estimator_checks import check_estimator

from sortedl1 import Slope


def test_sklearn_integration():
    mod = Slope()
    check_estimator(mod)
