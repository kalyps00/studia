import numpy as np
import matplotlib.pyplot as plt
from scipy.stats import gamma

b_prior = 2
p_prior = 4

n_obs = 5
sum_x = 20

b_post = b_prior + n_obs
p_post = p_prior + sum_x

x = np.linspace(0, 8, 1000)

y_prior = gamma.pdf(x, a=p_prior, scale=1 / b_prior)
y_post = gamma.pdf(x, a=p_post, scale=1 / b_post)

plt.plot(x, y_prior, label=f"A priori Gamma({b_prior}, {p_prior})", color="blue")
plt.plot(x, y_post, label=f"A posteriori Gamma({b_post}, {p_post})", color="red")

plt.title("Wnioskowanie bayesowskie - aktualizacja rozkładu Gamma")
plt.xlabel("Parametr ξ")
plt.ylabel("Gęstość prawdopodobieństwa")
plt.legend()
plt.grid(True, alpha=0.3)
plt.show()
