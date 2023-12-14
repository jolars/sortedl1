# sortedl1 <a href="https://jolars.github.io/sortedl1/"><img src="https://github.com/jolars/sortedl1/raw/main/docs/source/_static/slope-horizontal.svg" align="right" width="140" /></a>

[![CI](https://github.com/jolars/sortedl1/actions/workflows/ci.yaml/badge.svg?branch=main)](https://github.com/jolars/sortedl1/actions/workflows/ci.yaml)
[![PyPI version](https://badge.fury.io/py/sortedl1.svg)](https://badge.fury.io/py/sortedl1)
[![codecov](https://codecov.io/gh/jolars/sortedl1/graph/badge.svg?token=tMVGB2LHcM)](https://codecov.io/gh/jolars/sortedl1)

**sortedl1** is a python package for Sorted L-One Penalized Estimation (SLOPE).

## Installing

The current release can be installed from PyPI by running

```python
pip install sortedl1
```

You can also install the latest development version via pip by calling

```python
pip install git+https://github.com/jolars/sortedl1
```

Alternatively, you can clone the repository and install the package locally by running

```python
pip install .
```

Installing from source requires a C++17 compatible compiler.

## Usage

Estimators in **sortedl1** are compatible with the scikit-learn interface.

```python
import numpy as np
from numpy.random import default_rng

from sortedl1 import Slope

# Generate some random data
n = 100
p = 3

seed = 31
rng = default_rng(seed)

x = rng.standard_normal((n, p))
beta = rng.standard_normal(p)
y = x @ beta + rng.standard_normal(n)

# Fit the model
model = Slope(alpha=0.1)
model.fit(x, y)

# Print the coefficients
print(model.coef_)
```

## Contributing

The backbone of the package is written in C++ and developed in a separate repository at <https://github.com/jolars/libslope>. So if you have any issues with the package other than such that are specific to the python interface, please report them there. But feel free to request features here.

When writing commit messages, please use the [conventional commits format](https://www.conventionalcommits.org/en/v1.0.0/).

## Versioning

sortedl1 uses [semantic versioning](https://semver.org).
