import numpy as np


class SplineSystem:
    def __init__(self, t_nodes):
        # === FAZA I: PREKOMPUTACJA ===
        self.t = np.array(t_nodes, dtype=float)
        self.N = len(t_nodes) - 1  # Liczba przedziałów

        # 1. Obliczenie kroków siatki: h_k
        self.h = np.diff(self.t)

        # Tablice pomocnicze
        self.lambdas = np.zeros(self.N)  # lambda
        self.alpha = np.zeros(self.N)  # współczynniki alpha
        self.denom = np.zeros(self.N)  # mianowniki

        # 2. Wyznaczenie parametrów geometrycznych
        for k in range(1, self.N):
            self.lambdas[k] = self.h[k - 1] / (self.h[k - 1] + self.h[k])
            mianownik = 2 + self.lambdas[k] * self.alpha[k - 1]
            self.denom[k] = mianownik

            if k < self.N - 1:
                self.alpha[k] = (self.lambdas[k] - 1) / mianownik

    def solve_moments(self, y_values):
        # === FAZA II: WYZNACZANIE MOMENTÓW  ===
        y = np.array(y_values, dtype=float)
        M = np.zeros(self.N + 1)
        beta = np.zeros(self.N)

        for k in range(1, self.N):
            L = (y[k] - y[k - 1]) / self.h[k - 1]
            P = (y[k + 1] - y[k]) / self.h[k]
            d_k = 6 * (P - L) / (self.h[k - 1] + self.h[k])
            beta[k] = (d_k - self.lambdas[k] * beta[k - 1]) / self.denom[k]

        M[self.N] = 0
        M[0] = 0

        for k in range(self.N - 1, 0, -1):
            M[k] = self.alpha[k] * M[k + 1] + beta[k]

        return M

    def get_interpolated_values(self, y_values, M, u_grid):
        # === FAZA III: KONSTRUKCJA FUNKCJI (WYNIK) ===
        results = []
        y = np.array(y_values)
        for u in u_grid:
            k = np.searchsorted(self.t, u, side="right") - 1
            k = max(0, min(k, self.N - 1))

            h = self.h[k]
            dx = u - self.t[k]

            a = y[k]
            b = (y[k + 1] - y[k]) / h - h * (2 * M[k] + M[k + 1]) / 6.0
            c = M[k] / 2.0
            d = (M[k + 1] - M[k]) / (6.0 * h)

            val = a + b * dx + c * (dx**2) + d * (dx**3)
            results.append(val)

        return np.array(results)
