import numpy as np
import matplotlib.pyplot as plt


class SplineSystem:

    def __init__(self, t_nodes):
        # === FAZA I: PREKOMPUTACJA ===
        # Wykonywana tylko raz.

        self.t = np.array(t_nodes, dtype=float)
        self.N = len(t_nodes) - 1  # Liczba przedziałów

        # 1. Obliczenie kroków siatki: h_k
        self.h = np.diff(self.t)

        # Tablice pomocnicze
        self.lambdas = np.zeros(self.N)  # lambda
        self.alpha = np.zeros(self.N)  # współczynniki alpha
        self.denom = np.zeros(self.N)  # mianowniki

        # 2. Wyznaczenie parametrów geometrycznych
        # Pętla od k=1 do N-1
        for k in range(1, self.N):
            # Obliczenie lambda_k = h_k / (h_k + h_{k+1})
            # h[k-1] to h_k, h[k] to h_{k+1}
            self.lambdas[k] = self.h[k - 1] / (self.h[k - 1] + self.h[k])

            # Obliczenie mianownika i alpha_k
            # mian_k = 2 + lambda_k * alpha_{k-1}
            mianownik = 2 + self.lambdas[k] * self.alpha[k - 1]
            self.denom[k] = mianownik

            # alpha_k = (lambda_k - 1) / mian_k
            if k < self.N - 1:
                self.alpha[k] = (self.lambdas[k] - 1) / mianownik

    def solve_moments(self, y_values):
        # === FAZA II: WYZNACZANIE MOMENTÓW  ===
        y = np.array(y_values, dtype=float)
        M = np.zeros(self.N + 1)  # Wektor momentów
        beta = np.zeros(self.N)  # Wektor pomocniczy beta

        # 1. Obliczenie prawych stron równań (d_k) i (beta)
        for k in range(1, self.N):
            # Obliczamy nachylenia (ilorazy różnicowe 1. rzędu)
            # L (lewe) = (y_k - y_{k-1}) / h_k
            L = (y[k] - y[k - 1]) / self.h[k - 1]

            # P (prawe) = (y_{k+1} - y_k) / h_{k+1}
            P = (y[k + 1] - y[k]) / self.h[k]

            # Prawa strona d_k = 6 * (P - L) / (h_k + h_{k+1})
            d_k = 6 * (P - L) / (self.h[k - 1] + self.h[k])

            # Wyznaczenie beta_k
            # beta_k = (d_k - lambda_k * beta_{k-1}) / mian_k
            beta[k] = (d_k - self.lambdas[k] * beta[k - 1]) / self.denom[k]

        # 2. Podstawienie wstecz (Wyznaczenie M)
        # Wiemy, że M_N = 0, więc zaczynamy od N-1 w dół
        M[self.N] = 0
        M[0] = 0

        for k in range(self.N - 1, 0, -1):
            # M_k = alpha_k * M_{k+1} + beta_k
            M[k] = self.alpha[k] * M[k + 1] + beta[k]

        return M

    def get_interpolated_values(self, y_values, M, u_grid):
        # === FAZA III: KONSTRUKCJA FUNKCJI (WYNIK) ===
        # Obliczenie wartości na gęstej siatce punktów do rysowania.

        results = []
        y = np.array(y_values)

        for u in u_grid:
            # Znajdź odpowiedni przedział [t_k, t_{k+1}] dla punktu u
            k = np.searchsorted(self.t, u, side="right") - 1
            k = max(0, min(k, self.N - 1))

            # Parametry wewnątrz przedziału
            h = self.h[k]  # długość przedziału
            dx = u - self.t[k]  # odległość od początku przedziału (x - x_k)

            # Wzór Taylora dla NIFS3: S(x) = a + b*dx + c*dx^2 + d*dx^3
            # Współczynniki wyliczamy z wartości y i momentów M
            a = y[k]
            b = (y[k + 1] - y[k]) / h - h * (2 * M[k] + M[k + 1]) / 6.0
            c = M[k] / 2.0
            d = (M[k + 1] - M[k]) / (6.0 * h)

            # Obliczenie wartości wielomianu
            val = a + b * dx + c * (dx**2) + d * (dx**3)
            results.append(val)

        return np.array(results)


# --- CZĘŚĆ GŁÓWNA PROGRAMU ---


t_nodes = np.linspace(0, 1, 96)  # t_k = k/95
# fmt: off
X_data = [
    5.5, 8.5, 10.5, 13, 17, 20.5, 24.5, 28, 32.5, 37.5, 40.5, 42.5, 45, 47,
    49.5, 50.5, 51, 51.5, 52.5, 53, 52.8, 52, 51.5, 53, 54, 55, 56, 55.5, 54.5, 54, 55, 57, 58.5,
    59, 61.5, 62.5, 63.5, 63, 61.5, 59, 55, 53.5, 52.5, 50.5, 49.5, 50, 51, 50.5, 49, 47.5, 46,
    45.5, 45.5, 45.5, 46, 47.5, 47.5, 46, 43, 41, 41.5, 41.5, 41, 39.5, 37.5, 34.5, 31.5, 28, 24,
    21, 18.5, 17.5, 16.5, 15, 13, 10, 8, 6, 6, 6, 5.5, 3.5, 1, 0, 0, 0.5, 1.5, 3.5, 5, 5, 4.5, 4.5, 5.5,
    6.5, 6.5, 5.5, 
]

Y_data = [
    41, 40.5, 40, 40.5, 41.5, 41.5, 42, 42.5, 43.5, 45, 47, 49.5, 53, 57, 59,
    59.5, 61.5, 63, 64, 64.5, 63, 61.5, 60.5, 61, 62, 63, 62.5, 61.5, 60.5, 60, 59.5, 59, 58.5,
    57.5, 55.5, 54, 53, 51.5, 50, 50, 50.5, 51, 50.5, 47.5, 44, 40.5, 36, 30.5, 28, 25.5, 21.5,
    18, 14.5, 10.5, 7.50, 4, 2.50, 1.50, 2, 3.50, 7, 12.5, 17.5, 22.5, 25, 25, 25, 25.5, 26.5,
    27.5, 27.5, 26.5, 23.5, 21, 19, 17, 14.5, 11.5, 8, 4, 1, 0, 0.5, 3, 6.50, 10, 13, 16.5, 20.5,
    25.5, 29, 33, 35, 36.5, 39, 41, 
]
# fmt: on
# 2. Uruchomienie FAZY I (Geometria)
spline_solver = SplineSystem(t_nodes)

# 3. Uruchomienie FAZY II (Momenty)
# Rozwiązujemy układ równań dla współrzędnych X
M_x = spline_solver.solve_moments(X_data)
# Rozwiązujemy układ równań dla współrzędnych Y (używając prekomputacji z Fazy I)
M_y = spline_solver.solve_moments(Y_data)

# 4. Uruchomienie FAZY III (Ewaluacja/Rysowanie)
u_grid = np.linspace(0, 1, 1000)  # Gęsta siatka parametrów

# Obliczamy wartości funkcji X(t) i Y(t)
curve_x = spline_solver.get_interpolated_values(X_data, M_x, u_grid)
curve_y = spline_solver.get_interpolated_values(Y_data, M_y, u_grid)

# 5. Rysowanie wyniku
plt.figure(figsize=(10, 6))
plt.plot(curve_x, curve_y, "b-", linewidth=2, label="NIFS3 Parametryczna")
plt.plot(X_data, Y_data, "ro", markersize=3, label="Węzły interpolacji")
plt.title("Pies?")
plt.xlabel("X(t)")
plt.ylabel("Y(t)")
plt.legend()
plt.axis("equal")
plt.grid(True, linestyle="--", alpha=0.6)
plt.show()
