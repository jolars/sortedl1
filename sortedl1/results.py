"""Result classes for SLOPE estimators."""

from __future__ import annotations

from typing import NamedTuple

import numpy as np


class CvResults(NamedTuple):
    best_ind: int
    best_score: float
    best_alpha_ind: int
    scores: np.ndarray
    means: np.ndarray
    errors: np.ndarray

    def plot(self, **kwargs):
        """Plot cross-validation results."""
        try:
            import matplotlib.pyplot as plt
        except ImportError:
            msg = (
                "matplotlib is required for plotting. "
                + "Install with: pip install sortedl1[plots]"
            )
            raise ImportError(msg)

        fig, ax = plt.subplots(**kwargs)

        return fig, ax


class PathResults(NamedTuple):
    coefs: np.ndarray
    intercepts: np.ndarray
    alphas: np.ndarray
    lambdas: np.ndarray

    def plot(self, response=None, **kwargs):
        """Plot the SLOPE path."""
        try:
            import matplotlib.pyplot as plt
        except ImportError:
            msg = (
                "matplotlib is required for plotting. "
                + "Install with: pip install sortedl1[plots]"
            )
            raise ImportError(msg)

        n_responses = self.coefs.shape[1]

        if response is None:
            responses_to_plot = list(range(n_responses))
        else:
            if response < 0 or response >= n_responses:
                msg = f"Response index {response} is out of bounds for coefs with shape {self.coefs.shape}"
                raise IndexError(msg)
            responses_to_plot = [response]

        subplot_kwargs = {}
        plot_kwargs = {}

        subplot_keys = {
            "figsize",
            "dpi",
            "facecolor",
            "edgecolor",
            "frameon",
            "subplotpars",
            "tight_layout",
            "constrained_layout",
            "sharex",
            "sharey",
        }

        for key, value in kwargs.items():
            if key in subplot_keys:
                subplot_kwargs[key] = value
            else:
                plot_kwargs[key] = value

        plot_defaults = {"marker": "None", "linestyle": "-"}
        for key, default_value in plot_defaults.items():
            plot_kwargs.setdefault(key, default_value)

        subplot_defaults = {"sharex": True, "sharey": True}
        for key, default_value in subplot_defaults.items():
            subplot_kwargs.setdefault(key, default_value)

        n_plots = len(responses_to_plot)
        if n_plots == 1:
            fig, ax = plt.subplots(**subplot_kwargs)
            axes = [ax]
        else:
            ncols = min(3, n_plots)  # Max 3 columns
            nrows = (n_plots + ncols - 1) // ncols
            fig, axes = plt.subplots(nrows, ncols, **subplot_kwargs)
            axes = axes.flatten() if n_plots > 1 else [axes]

        for i, resp_idx in enumerate(responses_to_plot):
            ax = axes[i]
            coefs = self.coefs[:, resp_idx, :].T
            ax.plot(self.alphas.ravel(), coefs, **plot_kwargs)

            ax.set_xscale("log")
            ax.invert_xaxis()
            ax.set_xlabel(r"$\alpha$")
            ax.set_ylabel(r"$\beta$")

            if n_plots > 1:
                ax.set_title(f"Response {resp_idx}")

        return fig, axes if n_plots > 1 else axes[0]
