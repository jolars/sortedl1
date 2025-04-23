"""Scikit-learn compatible estimators for SLOPE."""

from __future__ import annotations

from typing import TypeVar, final

import numpy as np
from _sortedl1 import (
    _predict,
    fit_slope_dense,
    fit_slope_path_dense,
    fit_slope_path_sparse,
    fit_slope_sparse,
)
from numpy.typing import ArrayLike, NDArray
from scipy import sparse
from sklearn.linear_model._base import LinearModel
from sklearn.utils.validation import (
    check_X_y,
)


@final
class Slope(LinearModel):
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

    loss :
        Loss (data-fitting) function to be used. One of "quadratic", "logistic",
        "multinomial", and "poisson".

    lambda_type :
        Type of lambda sequence. One of `"bh"`, `"gaussian"`, `"oscar"`, and `"lasso"`.

    q :
        FDR control parameter for the Sorted L1 Penalty. Must be between 0 and 1.
        Only has effect if `lambda_type` is `"bh"` or `"gaussian"`.

    theta1:
        Slope of the penalty sequence for OSCAR type sequences. Only has effect
        when `lambda_type` is `"oscar"`.

    theta2:
        Slope of the penalty sequence for OSCAR type sequences. Only has effect
        when `lambda_type` is `"oscar"`.

    centering :
        Type of centering, one of "mean", "min", and "none".

    scaling :
        Type of scaling, one of "sd", "l1", "l2", "max_abs", and "none".

    max_iter :
        Maximum number of iterations.

    tol :
        Tolerance for the stopping criterion.

    solver:
        Solver to be used. One of "hybrid", "pgd", and "fista"

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
        loss: str = "quadratic",
        lambda_type: str = "bh",
        q: float = 0.1,
        theta1: float = 1.0,
        theta2: float = 0.5,
        centering: str = "none",
        scaling: str = "none",
        max_iter: int = 100_000,
        tol: float = 1e-4,
        solver: str = "hybrid",
    ):
        self.lam = lam
        self.alpha = alpha
        self.fit_intercept = fit_intercept
        self.loss = loss
        self.lambda_type = lambda_type
        self.q = q
        self.theta1 = theta1
        self.theta2 = theta2
        self.max_iter = max_iter
        self.tol = tol
        self.solver = solver
        self.scaling = scaling
        self.centering = centering

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
        self :
            Fitted estimator.
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

        params = self._get_common_params()

        fit_slope = fit_slope_sparse if sparse.issparse(X) else fit_slope_dense
        result = fit_slope(X, y, lam, self.alpha, params)

        self.intercept_ = result[0][0]
        self.sparse_coef_ = result[1]
        self.coef_ = np.squeeze(result[1].toarray())
        self.lambda_ = result[2]
        self.alpha_ = result[3]
        self.n_iter_ = max(1, result[4])
        self.n_features_in_ = X.shape[1]

        return self

    def path(
        self,
        X: NDArray[np.number] | sparse.csc_array,
        y: NDArray[np.number] | list[float] | tuple[float, ...],
        alphas: None | NDArray[np.number] = None,
        path_length: int = 100,
        alpha_min_ratio: None | np.number = None,
        tol_dev_change: float = 1e-5,
        tol_dev_ratio: float = 0.999,
        max_clusters: int = None,
        **kwargs,
    ):
        """
        Fit the SLOPE path

        Parameters
        ----------
        X :
            Feature matrix, where n_samples is the number of samples and
            n_features is the number of features.

        y :
            Response vector.

        alphas :
            An array of lambda values to use for the path. If None, the lambda
            values are computed automatically based on `path_length` and
            `alpha_min_ratio`.

        path_length :
            The number of alpha values to compute for the path. This parameter
            is ignored if `alphas` is provided.

        alpha_min_ratio :
            The minimum value of alpha to use for the path as a fraction of
            `alpha_max` (the value at which all coefficients are zero). If
            `None`, then the value is computed based on the dimension of the
            data: 1e-2 if there are more features than observations and 1e-4
            otherwise. This parameter is ignored if `alphas` is provided.

        tol_dev_change :
            Early path stopping criterion based on the change in deviance.
            If the fractional change in deviance is less than this value, the path is
            stopped early.

        tol_dev_ratio :
            Early path stopping criterion based on the ratio of deviance.
            If the deviance ratio exceeds this value, the path is stopped
            early.

        max_clusters :
            Early path stopping criterion based on the number of
            clusters (unique nonzero magnitudes among the coefficients).
            The default, `None`, sets this value to the number of
            observations plus one.

        Returns
        -------
        coefs : array, shape (n_features, n_alphas)
            The estimated coefficients for each alpha.

        intercepts : array, shape (n_alphas,)
            The estimated intercepts for each alpha.

        alphas : array, shape (n_alphas,)
            The lambda values for the path.

        lambdas : array, shape (n_alphas,)
            The lambda values for the path.

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
            lam = np.array([], dtype=np.float64)
        else:
            lam = np.atleast_1d(self.lam).astype(np.float64)

        if alphas is None:
            alphas = np.array([], dtype=np.float64)

        if alpha_min_ratio is None:
            alpha_min_ratio = -1

        if max_clusters is None:
            max_clusters = X.shape[0] + 1

        params = self._get_common_params(
            path_length=path_length,
            alpha_min_ratio=alpha_min_ratio,
            tol_dev_change=tol_dev_change,
            tol_dev_ratio=tol_dev_ratio,
            max_clusters=max_clusters,
        )

        fit_slope_path = (
            fit_slope_path_sparse if sparse.issparse(X) else fit_slope_path_dense
        )

        result = fit_slope_path(X, y, lam, alphas, params)

        intercepts = result[0]
        coefs = result[1]
        lambdas = result[2]
        alphas = result[3]

        return coefs, intercepts, alphas, lambdas

    def predict(self, X: ArrayLike | sparse.sparray) -> np.ndarray:
        """
        Generate predictions for new data.

        Parameters
        ----------
        X :
            The feature matrix to predict from.

        Returns
        -------
        y_pred :
            Returns predicted values.
        """
        eta = self._decision_function(X)

        out = _predict(eta, self.loss)

        return np.ravel(out)

    def _get_common_params(self, **additional_params):
        """Get common parameters shared between fit and path methods."""
        params = {
            "alpha": self.alpha,
            "intercept": self.fit_intercept,
            "scaling": self.scaling,
            "loss": self.loss,
            "lambda_type": self.lambda_type,
            "q": self.q,
            "theta1": self.theta1,
            "theta2": self.theta2,
            "centering": self.centering,
            "tol": self.tol,
            "solver": self.solver,
            "max_it": self.max_iter,
        }
        params.update(additional_params)
        return params
