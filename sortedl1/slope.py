import _sortedl1 as sl1
import numpy as np


def slope(x, y, lam, alph):
    """
    Sorted L-One Penalized Estimation

    Parameters
    ----------
    x : array_like
        The design matrix
    y : array_like
        The response vector
    lam : array_like
        The lambda paramter vector for the Sorted L1 Penalty
    alph : array_like
        A multiplied for the Sorted L1 Penalty

    Returns
    -------
    res : ndarray
        An object containing the estimated regression coefficients.

    """
    x = np.array(x)
    y = np.array(y)

    lam = np.array(lam)
    alpha = np.array(alph)

    res = sl1.fit_slope(x, y, lam, alpha)

    return res
