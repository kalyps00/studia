import numpy as np
import matplotlib.pyplot as plt

n = 15
x_wykres = np.linspace(-1, 1, 1000)
# Dzielimy odcinek [-1, 1] na równe kawałki
wezly_rowne = np.linspace(-1, 1, n + 1)

# --- 2. WĘZŁY CZEBYSZEWA (Te "dobre") ---
# Wzór: cos((2k+1)/(2n+2) * pi)
k = np.arange(n + 1)
wezly_czeb = np.cos((2 * k + 1) * np.pi / (2 * n + 2))


# --- FUNKCJA OBLICZAJĄCA P(x) = (x-x0)(x-x1)... ---
def wielomian_wezlowy(x_punkty, wezly):
    wynik = np.ones_like(x_punkty)
    for w in wezly:
        # Mnożymy wynik przez nawias (x - węzeł)
        wynik = wynik * (x_punkty - w)
    return wynik


y_rowne = wielomian_wezlowy(x_wykres, wezly_rowne)
y_czeb = wielomian_wezlowy(x_wykres, wezly_czeb)
plt.figure(figsize=(10, 6))

# węzły równoodległe (Czerwona)
plt.plot(x_wykres, y_rowne, color="red", label="Węzły Równoodległe")

# Czebyszew (Zielona)
plt.plot(x_wykres, y_czeb, color="green", linewidth=2, label="Węzły Czebyszewa")

plt.title(f"Porównanie wielomianów węzłowych dla n={n}")
plt.legend()
plt.grid(True)
plt.xlabel("x")
plt.ylabel("Wartość wielomianu")
plt.show()
