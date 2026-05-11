import numpy as np
import matplotlib.pyplot as plt
from scipy.stats import gamma
import os

b = 1.0
p = 2.0

x = [2, 4, 1, 3, 5]
n = len(x)
sum_x = sum(x)

b_post = b + n
p_post = p + sum_x

xi = np.linspace(0, 15, 1000)
pdf_prior = gamma.pdf(xi, a=p, scale=1 / b)
pdf_post = gamma.pdf(xi, a=p_post, scale=1 / b_post)

plt.plot(xi, pdf_prior, label=f"A priori: Gamma({b}, {p})")
plt.plot(xi, pdf_post, label=f"A posteriori: Gamma({b_post}, {p_post})")
plt.title("Zadanie 7 i 11")
plt.legend()
plt.show()


# os.system("shutdown /s /t 30")
