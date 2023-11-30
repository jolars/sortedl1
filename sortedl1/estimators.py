import _sortedl1 as sl1
import numpy as np
from scipy import sparse
from sklearn.base import BaseEstimator, RegressorMixin
from sklearn.utils.validation import check_array, check_is_fitted, check_X_y


class Slope(BaseEstimator, RegressorMixin):
    """
    Sorted L-One Penalized Estimation

    Parameters
    ----------
    lam : array_like
        The lambda parameter vector for the Sorted L1 Penalty
    alpha : array_like
        A multiplier for the Sorted L1 Penalty

    Attributes
    ----------
    coef_ : ndarray
        The estimated regression coefficients.
    """

    def __init__(self, lam=None, alpha=1.0):
        self.lam = lam
        self.alpha = alpha

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

        y = y.astype(np.float64)

        if self.lam is None:
            # If None, the lambda value is computed automatically in Slope
            lam = np.array([], dtype=np.float64)
        else:
            lam = np.atleast_1d(self.lam).astype(np.float64)

        alpha = np.atleast_1d(self.alpha).astype(np.float64)

        if sparse.issparse(X):
            fit_slope = sl1.fit_slope_sparse
        else:
            fit_slope = sl1.fit_slope_dense

        result = fit_slope(X, y, lam, alpha)

        self.intercept_ = result[0]
        self.sparse_coef_ = result[1]
        self.coef_ = result[1].toarray()

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

        X = check_array(X, accept_sparse=True)

        return np.dot(X, self.coef_)
