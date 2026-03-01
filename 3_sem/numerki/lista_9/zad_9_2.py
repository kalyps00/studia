import numpy as np
import matplotlib.pyplot as plt
from scipy.special import comb

def bernstein_poly(i, n, t):
    """Oblicza wartość wielomianu Bernsteina B_i^n(t)"""
    return comb(n, i) * (t**i) * (1 - t)**(n - i)

def rational_bezier(points, weights, num_points=1000):
    """Generuje punkty wymiernej krzywej Beziera"""
    n = len(points) - 1
    t = np.linspace(0, 1, num_points)
    curve = np.zeros((num_points, 2))
    denominator = np.zeros(num_points)
    
    for i in range(n + 1):
        b = bernstein_poly(i, n, t)
        # Licznik: suma w_i * P_i * B_i(t)
        curve += np.outer(b * weights[i], points[i])
        # Mianownik: suma w_i * B_i(t)
        denominator += b * weights[i]
        
    # Dzielenie (normalizacja)
    return curve / denominator[:, None]

# 1. Dane z Zadania L9.9 [cite: 30, 31]
control_points = np.array([
    (39.5, 10.5), (30, 20), (6, 6), (13, -12), (63, -12.5), 
    (18.5, 17.5), (48, 63), (7, 25.5), (48.5, 49.5), (9, 19.5), 
    (48.5, 35.5), (59, 32.5), (56, 20.5)
])

weights = np.array([1, 2, 3, 2.5, 6, 1.5, 5, 1, 2, 1, 3, 5, 1])

# 2. Obliczenie krzywej
curve = rational_bezier(control_points, weights)

# 3. Rysowanie
plt.figure(figsize=(6, 6))

# Rysujemy samą krzywą (niebieska linia)
plt.plot(curve[:, 0], curve[:, 1], 'b-', linewidth=2, label='Krzywa (Wynik)')

# Rysujemy punkty kontrolne i wielokąt kontrolny (czerwone kropki i przerywana linia)
# To pokazuje "otoczkę", w której siedzi krzywa (zgodnie z zadaniem 5 i 8)
plt.plot(control_points[:, 0], control_points[:, 1], 'r--', alpha=0.4, label='Wielokąt kontrolny')
plt.scatter(control_points[:, 0], control_points[:, 1], color='red', s=30)

# Oznaczenie pierwszego punktu, żeby wiedzieć gdzie startuje
plt.text(control_points[0,0], control_points[0,1], " Start", fontsize=9)

plt.title("Zadanie L9.9: Wymierna Krzywa Béziera")
plt.xlabel("X")
plt.ylabel("Y")
plt.legend()
plt.grid(True, linestyle=':', alpha=0.6)
plt.axis('equal') # Ważne, żeby zachować proporcje kształtu
plt.show()