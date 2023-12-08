"""Estimators for SLOPE."""

import numpy as np
from _sortedl1 import fit_slope_dense, fit_slope_sparse
from scipy import sparse
from sklearn.base import BaseEstimator, RegressorMixin
from sklearn.utils.validation import check_array, check_is_fitted, check_X_y


class Slope(BaseEstimator, RegressorMixin):
    """
    Sorted L-One Penalized Estimation.

    Parameters
    ----------
    lam : array_like, optional
        The lambda parameter vector for the Sorted L1 Penalty. Default is None.
    alpha : array_like, optional
        A multiplier for the Sorted L1 Penalty. Default is 1.0.
    fit_intercept : bool, optional
        Whether to fit an intercept term. Default is True.
    standardize : bool, optional
        Whether to standardize the features. Default is False.
    max_iter : int, optional
        Maximum number of iterations for the inner loop.
    tol : float, optional
        Tolerance for the stopping criterion.

    Attributes
    ----------
    coef_ : ndarray
        The estimated regression coefficients.
    """

    def __init__(
        self,
        lam=None,
        alpha=1.0,
        fit_intercept=True,
        standardize=False,
        max_iter=100_000,
        tol=1e-4,
    ):
        self.lam = lam
        self.alpha = alpha
        self.fit_intercept = fit_intercept
        self.standardize = standardize
        self.max_iter = max_iter
        self.tol = tol

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
            Returns self.
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
            fit_slope = fit_slope_sparse
        else:
            fit_slope = fit_slope_dense

        params = {
            "objective": "gaussian",
            "intercept": self.fit_intercept,
            "standardize": self.standardize,
            "path_length": 1,
            "alpha_min_ratio": -1,
            "pgd_freq": 10,
            "tol": self.tol,
            "max_it": self.max_iter,
            "max_it_outer": 2,
            "update_clusters": False,
            "print_level": 0,
        }

        result = fit_slope(X, y, lam, alpha, params)

        self.intercept_ = result[0]
        self.sparse_coef_ = result[1]
        self.coef_ = result[1].toarray()
        self.lambda_ = result[2]
        self.alpha_ = result[3]

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
