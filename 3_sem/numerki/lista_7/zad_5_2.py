import numpy as np
import matplotlib.pyplot as plt


# Funkcja generująca węzły Czebyszewa
def cheb_nodes(n):
    k = np.arange(0, n + 1)
    return np.cos((2 * k + 1) * np.pi / (2 * (n + 1)))


xs = np.linspace(-1, 1, 1000)
# Pętla po różnych stopniach wielomianu n
for n in range(4, 20):

    # Obliczanie wielomianu węzłowego dla węzłów równoodległych
    x_eq = np.linspace(-1, 1, n + 1)
    p_eq = np.ones_like(xs)
    for xi in x_eq:
        p_eq *= xs - xi

    # Obliczanie wielomianu węzłowego dla węzłów Czebyszewa
    x_ch = cheb_nodes(n)
    p_ch = np.ones_like(xs)
    for xi in x_ch:
        p_ch *= xs - xi

    # Rysowanie wykresów
    plt.figure(figsize=(8, 3))
    plt.plot(xs, p_eq, label="równoodległe")
    plt.plot(xs, p_ch, label="Czebyszewa", linestyle="--")
    plt.axhline(0, color="k", linewidth=0.5)
    plt.title(f"p_{{{n+1}}}(x) dla n={n}")
    plt.legend()
    plt.show()
