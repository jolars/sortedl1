"""Result classes for SLOPE estimators."""

from __future__ import annotations

from typing import NamedTuple

import numpy as np
from numpy.typing import NDArray


class CvResults(NamedTuple):
    best_score: float
    best_ind: int
    best_alpha_ind: int
    metric: str
    scores: list[NDArray[np.floating]]
    means: list[NDArray[np.floating]]
    errors: list[NDArray[np.floating]]
    alphas: list[NDArray[np.floating]]
    params: list[dict[str, str | float | int]]

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

        n_params = len(self.scores)

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

        plot_defaults = {"linestyle": "-"}
        for key, default_value in plot_defaults.items():
            plot_kwargs.setdefault(key, default_value)

        subplot_defaults = {"sharex": True, "sharey": True, "constrained_layout": True}
        for key, default_value in subplot_defaults.items():
            subplot_kwargs.setdefault(key, default_value)

        ribbon_kwargs = {}
        ribbon_keys = {
            "alpha",
            "color",
            "facecolor",
            "edgecolor",
            "linewidth",
            "linestyle",
        }

        final_plot_kwargs = {}
        for key, value in plot_kwargs.items():
            if key in ribbon_keys and key.startswith("ribbon_"):
                ribbon_kwargs[key.replace("ribbon_", "")] = value
            else:
                final_plot_kwargs[key] = value

        ribbon_defaults = {"alpha": 0.2}
        for key, default_value in ribbon_defaults.items():
            ribbon_kwargs.setdefault(key, default_value)

        if n_params == 1:
            fig, ax = plt.subplots(**subplot_kwargs)
            axes = [ax]
        else:
            n_rows = (n_params + 2) // 3
            n_cols = min(3, n_params)
            fig, axes = plt.subplots(n_rows, n_cols, **subplot_kwargs)
            axes = axes.flatten() if n_params > 1 else [axes]

        for i in range(n_params):
            ax = axes[i]

            params = self.params[i]

            ax.fill_between(
                self.alphas[i],
                self.means[i] - self.errors[i],  # Lower bound
                self.means[i] + self.errors[i],  # Upper bound
                alpha=0.2,
            )

            ax.plot(
                self.alphas[i],
                self.means[i],
                label=f"Parameter {i + 1}",
                **plot_kwargs,
            )

            ax.set_xscale("log")
            ax.invert_xaxis()
            ax.set_title(rf"q: {params['q']}, $\gamma$: {params['gamma']}")

            if n_params == 1:
                ax.set_xlabel(r"$\alpha$")
                ax.set_ylabel(f"{self.metric}")

        if n_params > 1:
            fig.supxlabel(r"$\alpha$")
            fig.supylabel(f"{self.metric}")

        return fig, axes if n_params > 1 else axes[0]


class PathResults(NamedTuple):
    coefs: NDArray[np.floating]
    intercepts: NDArray[np.floating]
    alphas: NDArray[np.floating]
    lambdas: NDArray[np.floating]

    def plot(self, **kwargs):
        """Plot the SLOPE path."""
        try:
            import matplotlib.pyplot as plt
        except ImportError:
            msg = (
                "matplotlib is required for plotting. "
                + "Install with: pip install sortedl1[plots]"
            )
            raise ImportError(msg)

        n_plots = self.coefs.shape[1]

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

        if n_plots == 1:
            fig, ax = plt.subplots(**subplot_kwargs)
            axes = [ax]
        else:
            ncols = min(3, n_plots)  # Max 3 columns
            nrows = (n_plots + ncols - 1) // ncols
            fig, axes = plt.subplots(nrows, ncols, **subplot_kwargs)
            axes = axes.flatten() if n_plots > 1 else [axes]

        for i in range(n_plots):
            ax = axes[i]
            coefs = self.coefs[:, i, :].T
            ax.plot(self.alphas.ravel(), coefs, **plot_kwargs)

            ax.set_xscale("log")
            ax.invert_xaxis()
            ax.set_xlabel(r"$\alpha$")
            ax.set_ylabel(r"$\beta$")

            if n_plots > 1:
                ax.set_title(f"Response {i + 1}")

        return fig, axes if n_plots > 1 else axes[0]
