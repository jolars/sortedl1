"""Scikit-learn compatible estimators for SLOPE."""

from __future__ import annotations

import warnings
from typing import TypeVar, final

import numpy as np
from _sortedl1 import fit_slope_dense, fit_slope_sparse
from numpy.typing import ArrayLike, NDArray
from scipy import sparse
from sklearn.base import BaseEstimator, RegressorMixin
from sklearn.utils.validation import (
    check_is_fitted,
    check_X_y,
    validate_data,
)


@final
class Slope(RegressorMixin, BaseEstimator):
    """
    Sorted L-One Penalized Estimation.

    Parameters
    ----------
    lam :
        The lambda parameter vector for the Sorted L1 Penalty.
    alpha :
        A multiplier for the Sorted L1 Penalty.
    fit_intercept :
        Whether to fit an intercept term.
    centering :
        Type of centering, one of "mean", "min", and "none".
    scaling :
        Type of scaling, one of "sd", "l1", "l2", "max_abs", and "none".
    max_iter :
        Maximum number of iterations.
    tol :
        Tolerance for the stopping criterion.
    standardize :
        DEPRECATED: This parameter is deprecated and will be removed in
        a future version. It no longer has any effect. Use `centering` and
        `scaling` instead.

    Attributes
    ----------
    intercept_ : float
        The estimated intercept.
    coef_ : ndarray
        The estimated regression coefficients in a sparse format.
    sparse_coef_ : scipy.sparse.csc_matrix
        The estimated regression coefficients in a dense format.
    lambda_ : ndarray
        The lambda parameter vector for the Sorted L1 Penalty.
    n_iter_ : int
        The total number of iterations from the inner loop.
    n_features_in_ : int
        The number of features seen by the estimator.
    """

    def __init__(
        self,
        lam: None | ArrayLike = None,
        alpha: float = 1.0,
        fit_intercept: bool = True,
        centering: str = "mean",
        scaling: str = "sd",
        max_iter: int = 100_000,
        tol: float = 1e-4,
        standardize: str | None = None,
    ):
        self.lam = lam
        self.alpha = alpha
        self.fit_intercept = fit_intercept
        self.max_iter = max_iter
        self.tol = tol
        self.scaling = scaling
        self.centering = centering
        self.standardize = None

        if standardize is not None:
            warnings.warn(
                "The 'standardize' parameter is deprecated and will be removed in a future version. It no longer has any effect",
                DeprecationWarning,
                stacklevel=2,
            )

    def __sklearn_tags__(self):
        tags = super().__sklearn_tags__()
        tags.input_tags.sparse = True
        return tags

    DType = TypeVar("DType", bound=np.number)

    def fit(
        self,
        X: NDArray[np.number] | sparse.csc_array,
        y: NDArray[np.number] | list[float] | tuple[float, ...],
    ):
        """
        Fit the model according to the given training data.

        Parameters
        ----------
        X :
            Training vector, where n_samples is the number of samples and
            n_features is the number of features.
        y :
            Target vector relative to X.

        Returns
        -------
        self : object
            Returns self.
        """
        X, y = check_X_y(X, y, accept_sparse=True, order="F", y_numeric=True)
        y = np.atleast_1d(y).astype(np.float64)
        if y.ndim == 1:
            y = y.reshape(-1, 1)

        if X.shape[0] == 1:
            raise ValueError("Data contains only one sample")

        if np.unique(y).size == 1:
            raise ValueError("y contains only one unique value")

        if self.lam is None:
            # If None, the lambda value is computed automatically in Slope
            lam = np.array([], dtype=np.float64)
        else:
            lam = np.atleast_1d(self.lam).astype(np.float64)

        params = {
            "alpha": self.alpha,
            "intercept": self.fit_intercept,
            "scaling": self.scaling,
            "centering": self.centering,
            "tol": self.tol,
            "max_it": self.max_iter,
        }

        fit_slope = fit_slope_sparse if sparse.issparse(X) else fit_slope_dense
        result = fit_slope(X, y, lam, self.alpha, params)

        self.intercept_ = result[0][0]
        self.sparse_coef_ = result[1]
        self.coef_ = result[1].toarray()
        self.lambda_ = result[2]
        self.alpha_ = result[3]
        self.n_iter_ = max(1, result[4])
        self.n_features_in_ = X.shape[1]

        return self

    def predict(self, X: ArrayLike | sparse.sparray) -> np.ndarray:
        """
        Generate predictions for new data.

        Parameters
        ----------
        X :
            Samples.

        Returns
        -------
        C : array, shape (n_samples,)
            Returns predicted values.
        """
        check_is_fitted(self)
        X = validate_data(self, X, accept_sparse=True, reset=False)

        pred = X @ self.coef_ + self.intercept_
        return np.ravel(pred)
