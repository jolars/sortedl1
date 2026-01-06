---
file_format: mystnb
kernelspec:
  name: python3
---

# User Guide

This guide provides detailed examples of using **sortedl1** for different types of regression problems. The package supports multiple loss functions, allowing you to apply SLOPE to various statistical modeling tasks.

## Loss Functions

The `Slope` estimator supports four different loss functions through the `loss` parameter:

- **`"quadratic"`**: Gaussian (linear) regression
- **`"logistic"`**: Logistic regression for binary classification
- **`"poisson"`**: Poisson regression for count data
- **`"multinomial"`**: Multinomial regression for multi-class classification

In the following sections, we demonstrate each loss function with practical examples.

## Gaussian Regression

Gaussian regression (also called linear regression) is the default loss function and is appropriate when the response variable is continuous and approximately normally distributed.

```{code-cell}
import numpy as np
from numpy.random import default_rng
from sortedl1 import Slope

# Set up random number generator
rng = default_rng(42)

# Generate continuous response data
n_samples = 200
n_features = 50

X = rng.standard_normal((n_samples, n_features))

# True coefficients with clustering structure
true_coef = np.zeros(n_features)
true_coef[0:5] = [5, 5, 5, 3, 3]  # Clustered coefficients
true_coef[10:12] = [2, 2]

y = X @ true_coef + rng.standard_normal(n_samples) * 0.5

# Fit Gaussian SLOPE
model = Slope(loss="quadratic", q=0.2)
model.fit(X, y)

print(f"Number of non-zero coefficients: {np.sum(model.coef_ != 0)}")
print(f"Training R²: {model.score(X, y):.3f}")
```

Let's visualize the estimated coefficients compared to the true values:

```{code-cell}
import matplotlib.pyplot as plt

fig, ax = plt.subplots(figsize=(10, 4))
ax.stem(true_coef, linefmt='C0-', markerfmt='C0o', basefmt=' ', label='True')
ax.stem(model.coef_, linefmt='C1-', markerfmt='C1x', basefmt=' ', label='Estimated')
ax.set_xlabel('Coefficient Index')
ax.set_ylabel('Coefficient Value')
ax.set_title('Gaussian Regression: True vs Estimated Coefficients')
ax.legend()
ax.grid(True, alpha=0.3)
plt.tight_layout()
```

We can also examine the regularization path:

```{code-cell}
path_result = model.path(X, y, path_length=50)
path_result.plot()
```

## Logistic Regression

Logistic regression is used for binary classification problems where the response variable takes values 0 or 1.

```{code-cell}
# Generate binary response data
X_binary = rng.standard_normal((n_samples, n_features))

# True coefficients for classification
true_coef_logistic = np.zeros(n_features)
true_coef_logistic[0:3] = [3, 3, 3]
true_coef_logistic[8:10] = [2, 2]
true_coef_logistic[15] = -2.5

# Generate probabilities and binary outcomes
logits = X_binary @ true_coef_logistic
probs = 1 / (1 + np.exp(-logits))
y_binary = rng.binomial(1, probs)

print(f"Class distribution: {np.sum(y_binary == 0)} zeros, {np.sum(y_binary == 1)} ones")

# Fit logistic SLOPE
model_logistic = Slope(loss="logistic", q=0.2)
model_logistic.fit(X_binary, y_binary)

print(f"Number of non-zero coefficients: {np.sum(model_logistic.coef_ != 0)}")
print(f"Training accuracy: {model_logistic.score(X_binary, y_binary):.3f}")
```

Visualize the coefficients:

```{code-cell}
import matplotlib.pyplot as plt

fig, ax = plt.subplots(figsize=(10, 4))
ax.stem(true_coef_logistic, linefmt='C0-', markerfmt='C0o', basefmt=' ', label='True')
ax.stem(model_logistic.coef_, linefmt='C1-', markerfmt='C1x', basefmt=' ', label='Estimated')
ax.set_xlabel('Coefficient Index')
ax.set_ylabel('Coefficient Value')
ax.set_title('Logistic Regression: True vs Estimated Coefficients')
ax.legend()
ax.grid(True, alpha=0.3)
plt.tight_layout()
```

Examine the regularization path for logistic regression:

```{code-cell}
path_result_logistic = model_logistic.path(X_binary, y_binary, path_length=50)
path_result_logistic.plot()
```

## Poisson Regression

Poisson regression is appropriate for count data where the response variable represents the number of events occurring in a fixed interval.

```{code-cell}
# Generate count data
X_count = rng.standard_normal((n_samples, n_features))

# True coefficients for count data
true_coef_poisson = np.zeros(n_features)
true_coef_poisson[0:4] = [0.8, 0.8, 0.6, 0.6]
true_coef_poisson[12:14] = [0.5, 0.5]

# Generate Poisson counts
log_rates = X_count @ true_coef_poisson + 1.0  # Add intercept
rates = np.exp(log_rates)
y_count = rng.poisson(rates)

print(f"Response statistics: mean={np.mean(y_count):.2f}, max={np.max(y_count)}, min={np.min(y_count)}")

# Fit Poisson SLOPE
model_poisson = Slope(loss="poisson", q=0.2, fit_intercept=True)
model_poisson.fit(X_count, y_count)

print(f"Number of non-zero coefficients: {np.sum(model_poisson.coef_ != 0)}")
print(f"Intercept: {model_poisson.intercept_:.3f}")
```

Visualize the Poisson regression coefficients:

```{code-cell}
import matplotlib.pyplot as plt

fig, ax = plt.subplots(figsize=(10, 4))
ax.stem(true_coef_poisson, linefmt='C0-', markerfmt='C0o', basefmt=' ', label='True')
ax.stem(model_poisson.coef_, linefmt='C1-', markerfmt='C1x', basefmt=' ', label='Estimated')
ax.set_xlabel('Coefficient Index')
ax.set_ylabel('Coefficient Value')
ax.set_title('Poisson Regression: True vs Estimated Coefficients')
ax.legend()
ax.grid(True, alpha=0.3)
plt.tight_layout()
```

View the regularization path:

```{code-cell}
path_result_poisson = model_poisson.path(X_count, y_count, path_length=50)
path_result_poisson.plot()
```

## Multinomial Regression

Multinomial regression extends logistic regression to handle multiple classes (more than two categories).

```{code-cell}
# Generate multi-class data
n_classes = 3
X_multi = rng.standard_normal((n_samples, n_features))

# True coefficients for each class (relative to baseline)
true_coef_multi = np.zeros((n_classes - 1, n_features))
true_coef_multi[0, 0:3] = [2, 2, 1.5]  # Class 1 vs baseline
true_coef_multi[1, 5:8] = [1.8, 1.8, 1.2]  # Class 2 vs baseline

# Generate class probabilities
logits_multi = X_multi @ true_coef_multi.T
# Add baseline class with log-odds = 0
logits_all = np.column_stack([np.zeros(n_samples), logits_multi])
exp_logits = np.exp(logits_all)
probs_multi = exp_logits / exp_logits.sum(axis=1, keepdims=True)

# Sample class labels
y_multi = np.array([rng.choice(n_classes, p=probs_multi[i]) for i in range(n_samples)])

print(f"Class distribution: {np.bincount(y_multi)}")

# Fit multinomial SLOPE
model_multi = Slope(loss="multinomial", q=0.2)
model_multi.fit(X_multi, y_multi)

print(f"Coefficient matrix shape: {model_multi.coef_.shape}")
print(f"Training accuracy: {model_multi.score(X_multi, y_multi):.3f}")
```

For multinomial regression, the coefficients form a matrix where each row corresponds to a class:

```{code-cell}
import matplotlib.pyplot as plt

fig, axes = plt.subplots(2, 1, figsize=(10, 7))

# Class 1 coefficients
axes[0].stem(true_coef_multi[0], linefmt='C0-', markerfmt='C0o', basefmt=' ', label='True')
axes[0].stem(model_multi.coef_[0], linefmt='C1-', markerfmt='C1x', basefmt=' ', label='Estimated')
axes[0].set_ylabel('Coefficient Value')
axes[0].set_title('Multinomial Regression: Class 1 Coefficients')
axes[0].legend()
axes[0].grid(True, alpha=0.3)

# Class 2 coefficients
axes[1].stem(true_coef_multi[1], linefmt='C0-', markerfmt='C0o', basefmt=' ', label='True')
axes[1].stem(model_multi.coef_[1], linefmt='C1-', markerfmt='C1x', basefmt=' ', label='Estimated')
axes[1].set_xlabel('Coefficient Index')
axes[1].set_ylabel('Coefficient Value')
axes[1].set_title('Multinomial Regression: Class 2 Coefficients')
axes[1].legend()
axes[1].grid(True, alpha=0.3)

plt.tight_layout()
```

View the regularization path for multinomial regression:

```{code-cell}
path_result_multi = model_multi.path(X_multi, y_multi, path_length=50)
path_result_multi.plot()
```

## Choosing the Right Loss Function

Here's a quick reference for selecting the appropriate loss function:

| Loss Function | Use Case | Response Type | Example |
|--------------|----------|---------------|---------|
| `quadratic` | Linear regression | Continuous, unbounded | Heights, temperatures, stock prices |
| `logistic` | Binary classification | Binary (0/1) | Disease presence, spam detection |
| `poisson` | Count regression | Non-negative integers | Number of events, accident counts |
| `multinomial` | Multi-class classification | Categorical (K classes) | Species classification, image categories |

All loss functions support the same regularization features of SLOPE, including:
- Clustering of coefficient magnitudes
- False discovery rate (FDR) control via the `q` parameter
- Different lambda sequence types via `lambda_type`
- Cross-validation via the `cv()` method
