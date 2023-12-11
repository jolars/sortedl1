# sortedl1

**sortedl1** is a python package for Sorted L-One Penalized Estimation.

## Installing

sortedl1 is currently only available on github. To install it, run

```python
pip install -U git+https://github.com/jolars/sortedl1
```

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
