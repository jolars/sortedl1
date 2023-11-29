import _sortedl1 as sl1
import numpy as np
from sklearn.base import BaseEstimator, RegressorMixin
from sklearn.utils.validation import check_array, check_is_fitted, check_X_y


class Slope(BaseEstimator, RegressorMixin):
    """
    Sorted L-One Penalized Estimation

    Parameters
    ----------
    lam : array_like
        The lambda parameter vector for the Sorted L1 Penalty
    alph : array_like
        A multiplier for the Sorted L1 Penalty

    Attributes
    ----------
    coef_ : ndarray
        The estimated regression coefficients.
    """

    def __init__(self, lam=None, alph=1.0):
        self.lam = lam
        self.alph = alph

    def fit(self, X, y):
        """
        Fit the model according to the given training data.

        Parameters
        ----------
        X : array_like, shape (n_samples, n_features)
            Training vector, where n_samples is the number of samples and
            n_features is the number of features.
        y : array_like, shape (n_samples,)
            Target vector relative to X.

        Returns
        -------
        self : object
        """
        X, y = check_X_y(X, y, accept_sparse=True, order="F", y_numeric=True)

        self.X_ = X
        self.y_ = y

        self.coef_ = sl1.fit_slope(
            self.X_, self.y_, np.array(self.lam), np.array(self.alph)
        )

        return self

    def predict(self, X):
        """
        Predict using the linear model.

        Parameters
        ----------
        X : array_like, shape (n_samples, n_features)
            Samples.

        Returns
        -------
        C : array, shape (n_samples,)
            Returns predicted values.
        """
        check_is_fitted(self)

        X = check_array(X, accept_sparse=True, order="F")

        return np.dot(X, self.coef_)
