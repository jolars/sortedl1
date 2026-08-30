"""Tests for interrupting native SLOPE solves."""

import selectors
import signal
import subprocess
import sys
import textwrap
import time

import pytest

_SOLVE_SCRIPT = textwrap.dedent(
    """
    import sys

    import numpy as np
    from scipy.stats import norm

    from sortedl1 import Slope


    method = sys.argv[1]
    rng = np.random.default_rng(0)
    n, p = 536, 500
    X = rng.standard_normal((n, p))
    y = rng.standard_normal(n)

    q = 0.2
    bh = norm.ppf(1 - np.arange(1, p + 1) * q / (2 * p))
    xty = np.sort(np.abs(X.T @ (y / n)))[::-1]
    alpha_max = np.max(np.cumsum(xty) / np.cumsum(bh))
    lambdas = 0.02 * alpha_max * bh

    model = Slope(
        lam=lambdas,
        alpha=1.0,
        fit_intercept=False,
        max_iter=1_000_000,
        tol=1e-20,
        hybrid_cd_type="cyclical",
    )

    print("solve started", flush=True)
    try:
        if method == "fit":
            model.fit(X, y)
        else:
            model.path(X, y, alphas=np.array([1.0]))
    except KeyboardInterrupt:
        print("interrupted", flush=True)
    else:
        raise RuntimeError("solve completed before SIGINT was handled")
    """
)


@pytest.mark.skipif(sys.platform == "win32", reason="requires POSIX signals")
@pytest.mark.parametrize("method", ["fit", "path"])
def test_native_solve_handles_sigint(method):
    process = subprocess.Popen(
        [sys.executable, "-c", _SOLVE_SCRIPT, method],
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        text=True,
    )

    assert process.stdout is not None
    selector = selectors.DefaultSelector()
    selector.register(process.stdout, selectors.EVENT_READ)

    try:
        assert selector.select(timeout=10), "solve did not start in time"
        assert process.stdout.readline() == "solve started\n"

        time.sleep(0.5)
        process.send_signal(signal.SIGINT)
        stdout, stderr = process.communicate(timeout=3)
    except subprocess.TimeoutExpired:
        process.kill()
        stdout, stderr = process.communicate()
        pytest.fail(f"{method} did not respond to SIGINT:\n{stdout}\n{stderr}")
    finally:
        selector.close()
        if process.poll() is None:
            process.kill()
            process.wait()

    assert process.returncode == 0, stderr
    assert stdout == "interrupted\n"
