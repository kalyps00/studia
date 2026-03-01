import matplotlib.pyplot as plt
import numpy as np
import math


def calc_b(i, n, t):
    return math.comb(n, i) * pow(t, i) * pow((1 - t), n - i)


def calculate_bezier_curve(W, w, t, n):
    denominator = 0
    for i in range(n):
        denominator += w[i] * calc_b(i, n, t)

    x = 0
    for i in range(n):
        x += w[i] * W[i][0] * calc_b(i, n, t)

    x /= denominator

    y = 0
    for i in range(n):
        y += w[i] * W[i][1] * calc_b(i, n, t)
    y /= denominator

    return x, y


def ev_bezier(t_points, n, W, w):
    res_x = []
    res_y = []
    for t in t_points:
        res_x.append(calculate_bezier_curve(W, w, t, n)[0])
        res_y.append(calculate_bezier_curve(W, w, t, n)[1])
    return (res_x, res_y)


t = np.linspace(0, 1, 100)


W = [
    (39.5, 10.5),
    (30, 20),
    (6, 6),
    (13, -12),
    (63, -12.5),
    (18.5, 17.5),
    (48, 63),
    (7, 25.5),
    (48.5, 49.5),
    (9, 19.5),
    (48.5, 35.5),
    (59, 32.5),
    (56, 20.5),
]
W_x = [p[0] for p in W]
W_y = [p[1] for p in W]
w = [2, 2, 3, 2.5, 6, 1.5, 5, 1, 2, 1, 3, 5, 1]
#w = [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1]
n = len(W)
(res_x, res_y) = ev_bezier(t, n, W, w)

plt.figure(figsize=(8, 8))
plt.plot(res_x, res_y, "b-", linewidth=2, label="Krzywa Beziera")
plt.plot(W_x, W_y, 'ro--', markersize=8, linewidth=1, label='Punkty kontrolne')
plt.axis("equal")
plt.grid(True)
plt.show()
