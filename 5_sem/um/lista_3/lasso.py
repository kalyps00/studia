import numpy as np

X = np.array([[1, 1, 0], [1, 0, 1], [1, 1, 1], [1, 2, 0]])
y = np.array([2, 2, 3, 4])
lmbda = 2.0
beta = np.zeros(3)


def soft_threshold(rho, threshold):
    if rho < -threshold:
        return rho + threshold
    elif rho > threshold:
        return rho - threshold
    else:
        return 0.0


for epoch in range(100):
    for j in range(3):
        y_pred_without_j = X @ beta - (X[:, j] * beta[j])
        r_minus_j = y - y_pred_without_j
        rho_j = np.dot(X[:, j], r_minus_j)
        z_j = np.dot(X[:, j], X[:, j])

        if j == 0:
            beta[j] = rho_j / z_j
        else:
            beta[j] = soft_threshold(rho_j, lmbda / 2.0) / z_j

print(
    f"Współczynniki LASSO: beta0={beta[0]:.2f}, beta1={beta[1]:.2f}, beta2={beta[2]:.2f}"
)
