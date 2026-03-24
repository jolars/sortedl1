"""Result classes for SLOPE estimators."""

from __future__ import annotations

from typing import NamedTuple, cast

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

    @property
    def n_param_sets(self) -> int:
        """Number of parameter combinations evaluated in cross-validation."""
        return len(self.scores)

    @property
    def best_alpha(self) -> float:
        """Best alpha value selected by cross-validation."""
        if not self.alphas:
            return float("nan")

        best_ind = int(self.best_ind)
        best_alpha_ind = int(self.best_alpha_ind)

        if best_ind < 0 or best_ind >= len(self.alphas):
            return float("nan")

        alpha_values = np.asarray(self.alphas[best_ind]).ravel()
        if best_alpha_ind < 0 or best_alpha_ind >= alpha_values.size:
            return float("nan")

        return float(alpha_values[best_alpha_ind])

    def summary(self, as_str: bool = False) -> dict[str, object] | str:
        """Return a compact summary of cross-validation results."""
        out: dict[str, object] = {
            "metric": self.metric,
            "n_param_sets": self.n_param_sets,
            "best_ind": int(self.best_ind),
            "best_alpha_ind": int(self.best_alpha_ind),
            "best_score": float(self.best_score),
            "best_alpha": self.best_alpha,
            "n_alphas_per_param": [int(np.asarray(a).size) for a in self.alphas],
            "param_keys": sorted(self.params[0].keys()) if self.params else [],
        }

        if as_str:
            return "CvResults(" + ", ".join(f"{k}={v}" for k, v in out.items()) + ")"

        return out

    def __repr__(self) -> str:
        s = cast(dict[str, object], self.summary())
        return (
            "CvResults("
            f"metric={s['metric']!r}, "
            f"n_param_sets={s['n_param_sets']}, "
            f"best_score={s['best_score']:.6g}, "
            f"best_alpha={s['best_alpha']:.6g}, "
            f"best_ind={s['best_ind']}, "
            f"best_alpha_ind={s['best_alpha_ind']}"
            ")"
        )

    def __str__(self) -> str:
        return repr(self)

    def plot(self, **kwargs):
        """Plot cross-validation results."""
        try:
            import matplotlib.pyplot as plt
        except ImportError:
            msg = (
                "matplotlib is required for plotting. "
                + "Install with: pip install sortedl1[plots]"
            )
            raise ImportError(msg) from None

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

    @property
    def n_alphas(self) -> int:
        """Number of alpha values in the fitted path."""
        return int(np.asarray(self.alphas).size)

    @property
    def n_features(self) -> int:
        """Number of features in the path coefficients."""
        return int(self.coefs.shape[0])

    @property
    def n_targets(self) -> int:
        """Number of target responses in the path coefficients."""
        coefs = np.asarray(self.coefs)
        if coefs.ndim <= 2:
            return 1
        return int(coefs.shape[1])

    @property
    def alpha_range(self) -> tuple[float, float]:
        """Smallest and largest alpha value in the path."""
        alphas = np.asarray(self.alphas).ravel()
        if alphas.size == 0:
            return (float("nan"), float("nan"))
        return float(np.min(alphas)), float(np.max(alphas))

    def summary(self, as_str: bool = False) -> dict[str, object] | str:
        """Return a compact summary of path results."""
        coefs = np.asarray(self.coefs)

        if coefs.ndim == 3:
            first_alpha_coefs = coefs[:, :, 0]
            last_alpha_coefs = coefs[:, :, -1]
        elif coefs.ndim == 2:
            first_alpha_coefs = coefs[:, 0]
            last_alpha_coefs = coefs[:, -1]
        else:
            first_alpha_coefs = coefs
            last_alpha_coefs = coefs

        alpha_min, alpha_max = self.alpha_range
        out: dict[str, object] = {
            "n_alphas": self.n_alphas,
            "n_features": self.n_features,
            "n_targets": self.n_targets,
            "alpha_min": alpha_min,
            "alpha_max": alpha_max,
            "coef_shape": tuple(coefs.shape),
            "intercepts_shape": tuple(np.asarray(self.intercepts).shape),
            "lambda_shape": tuple(np.asarray(self.lambdas).shape),
            "nnz_first_alpha": int(np.count_nonzero(first_alpha_coefs)),
            "nnz_last_alpha": int(np.count_nonzero(last_alpha_coefs)),
        }

        if as_str:
            return "PathResults(" + ", ".join(f"{k}={v}" for k, v in out.items()) + ")"

        return out

    def __repr__(self) -> str:
        s = cast(dict[str, object], self.summary())
        return (
            "PathResults("
            f"n_alphas={s['n_alphas']}, "
            f"n_features={s['n_features']}, "
            f"n_targets={s['n_targets']}, "
            f"alpha_range=({s['alpha_min']:.6g}, {s['alpha_max']:.6g})"
            ")"
        )

    def __str__(self) -> str:
        return repr(self)

    def plot(self, **kwargs):
        """Plot the SLOPE path."""
        try:
            import matplotlib.pyplot as plt
        except ImportError:
            msg = (
                "matplotlib is required for plotting. "
                + "Install with: pip install sortedl1[plots]"
            )
            raise ImportError(msg) from None

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
