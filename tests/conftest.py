"""Pytest configuration for sortedl1 tests."""

import matplotlib as mpl

# Use a non-interactive backend to make plotting tests work in headless CI.
mpl.use("Agg")
