"""Tests for scikit-learn interface."""
import unittest

from sklearn.utils.estimator_checks import check_estimator

from sortedl1 import Slope


class TestSklearnIntegration(unittest.TestCase):
    """
    A class used to test the integration of the Slope estimator with sklearn.

    ...

    Attributes
    ----------
    None

    Methods
    -------
    test_sklearn_integration():
        Tests the integration of the Slope estimator with sklearn.
    """

    def test_sklearn_integration(self):
        """
        Tests the integration of the Slope estimator with sklearn.

        This method creates an instance of the Slope estimator and checks if it adheres to
        sklearn's estimator interface.

        Parameters
        ----------
        None

        Returns
        -------
        None
        """
        mod = Slope()
        check_estimator(mod)


if __name__ == "__main__":
    unittest.main()
