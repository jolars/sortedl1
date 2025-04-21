# Getting Started

Estimators in **sortedl1** are compatible with the scikit-learn interface. Here is a simple example of fitting a model to some random data.

We start by generating the data.

```{testcode}
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
```

Next, we create the estimator by calling `Slope()` with all the desired parameters.

```{testcode}
model = Slope(alpha=0.1)
```

Finally, we fit the model to the data and inspect the coefficients.

```{testcode}
model.fit(x, y)
print(model.coef_)
```

```{testoutput}
[-1.12654445  0.9238887  -1.7007892 ]
```
