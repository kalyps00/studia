import numpy as np
import matplotlib

matplotlib.use("Agg")  # Non-interactive backend
import matplotlib.pyplot as plt
from scipy.stats import beta, gamma

# ================================
# Zadanie 9: Model Beta-Dwumianowy
# ================================
print("=" * 70)
print("ZADANIE 9: Porównanie gęstości a priori oraz a posteriori")
print("=" * 70)

# A priori: Beta(1,1) - rozkład płaski
p_prior, q_prior = 1, 1

print(f"\nA PRIORI: Beta({p_prior}, {q_prior}) - rozkład płaski (uniform)")

# Scenariusz 1: n=5, k=1
n1, k1 = 5, 1
p_post1, q_post1 = p_prior + k1, q_prior + n1 - k1

print(f"\nScenariusz 1: n={n1}, k={k1}")
print(f"  A posteriori: Beta({p_post1}, {q_post1})")
print(f"  E(p|x) = {beta.mean(p_post1, q_post1):.4f}")

# Scenariusz 2: n=5, k=4
n2, k2 = 5, 4
p_post2, q_post2 = p_prior + k2, q_prior + n2 - k2

print(f"\nScenariusz 2: n={n2}, k={k2}")
print(f"  A posteriori: Beta({p_post2}, {q_post2})")
print(f"  E(p|x) = {beta.mean(p_post2, q_post2):.4f}")

# Wizualizacja Zadania 9
x = np.linspace(0, 1, 500)
plt.figure(figsize=(12, 5))

plt.subplot(1, 2, 1)
plt.plot(
    x, beta.pdf(x, p_prior, q_prior), "k--", label="A priori Beta(1,1)", linewidth=2.5
)
plt.plot(
    x,
    beta.pdf(x, p_post1, q_post1),
    "b-",
    label=f"A posteriori Beta({p_post1},{q_post1})\n(n={n1}, k={k1})",
    linewidth=2.5,
)
plt.fill_between(x, np.zeros_like(x), beta.pdf(x, p_post1, q_post1), alpha=0.2, color="blue")  # type: ignore
plt.title("Scenariusz 1: n=5, k=1 (mało sukcesów)", fontsize=12, fontweight="bold")
plt.xlabel("Parametr p", fontsize=11)
plt.ylabel("Gęstość", fontsize=11)
plt.legend(fontsize=10)
plt.grid(True, alpha=0.3)

plt.subplot(1, 2, 2)
plt.plot(
    x, beta.pdf(x, p_prior, q_prior), "k--", label="A priori Beta(1,1)", linewidth=2.5
)
plt.plot(
    x,
    beta.pdf(x, p_post2, q_post2),
    "r-",
    label=f"A posteriori Beta({p_post2},{q_post2})\n(n={n2}, k={k2})",
    linewidth=2.5,
)
plt.fill_between(x, np.zeros_like(x), beta.pdf(x, p_post2, q_post2), alpha=0.2, color="red")  # type: ignore
plt.title("Scenariusz 2: n=5, k=4 (dużo sukcesów)", fontsize=12, fontweight="bold")
plt.xlabel("Parametr p", fontsize=11)
plt.ylabel("Gęstość", fontsize=11)
plt.legend(fontsize=10)
plt.grid(True, alpha=0.3)

plt.tight_layout()
plt.savefig("zadanie_9.png", dpi=150, bbox_inches="tight")
plt.show()

# ================================
# Zadanie 11: Model Gamma-Poisson
# ================================
print("\n" + "=" * 70)
print("ZADANIE 11: Ilustracja Zadania 7 - Model Gamma-Poisson")
print("=" * 70)

# Wybór a priori: Gamma(b,p)
# Parametryzacja: f(x) = b^p / Γ(p) * x^(p-1) * e^(-bx)
# W scipy: gamma.pdf(x, a=p, scale=1/b)

b_prior, p_prior_g = 2.0, 2.0
print(f"\nA PRIORI: ξ ~ Gamma(b={b_prior}, p={p_prior_g})")
print(f"Interpretacja: umiarkowanie informatywny rozkład a priori")

# Obserwacje z Poisson(ξ)
obserwacje = [1, 3, 2, 4]
n_obs = len(obserwacje)
sum_x = sum(obserwacje)

print(f"\nMODEL: xᵢ ~ Poisson(ξ), i=1,2,...,{n_obs}")
print(f"Obserwacje: {obserwacje}")
print(f"n = {n_obs}, Σxᵢ = {sum_x}")

# Rozkład a posteriori: Gamma(b+n, p+Σxᵢ)
b_post = b_prior + n_obs
p_post_g = p_prior_g + sum_x

print(f"\nA POSTERIORI: ξ|x ~ Gamma(b={b_post}, p={p_post_g})")
print(f"E(ξ|x) = {p_post_g / b_post:.4f}")

# Wizualizacja Zadania 11
x_g = np.linspace(0, 10, 500)

plt.figure(figsize=(14, 5))

plt.subplot(1, 2, 1)
plt.plot(
    x_g,
    gamma.pdf(x_g, a=p_prior_g, scale=1 / b_prior),
    "k--",
    label=f"A priori: Gamma({b_prior}, {p_prior_g})",
    linewidth=2.5,
)
plt.plot(
    x_g,
    gamma.pdf(x_g, a=p_post_g, scale=1 / b_post),
    "g-",
    label=f"A posteriori: Gamma({b_post}, {p_post_g})",
    linewidth=2.5,
)
plt.fill_between(  # type: ignore
    x_g,
    np.zeros_like(x_g),
    gamma.pdf(x_g, a=p_post_g, scale=1 / b_post),
    alpha=0.2,
    color="green",
)
plt.title("Model Gamma-Poisson\n(Główny wariant)", fontsize=12, fontweight="bold")
plt.xlabel("ξ", fontsize=11)
plt.ylabel("Gęstość", fontsize=11)
plt.legend(fontsize=10)
plt.grid(True, alpha=0.3)

# Wariant alternatywny: inne wybory a priori
plt.subplot(1, 2, 2)

# Wariant 1: mniej informatywny Gamma(1,1)
b_alt1, p_alt1 = 1.0, 1.0
b_post_alt1 = b_alt1 + n_obs
p_post_alt1 = p_alt1 + sum_x

# Wariant 2: bardziej informatywny Gamma(3,3)
b_alt2, p_alt2 = 3.0, 3.0
b_post_alt2 = b_alt2 + n_obs
p_post_alt2 = p_alt2 + sum_x

plt.plot(
    x_g,
    gamma.pdf(x_g, a=p_prior_g, scale=1 / b_prior),
    "k--",
    label=f"A priori główny: Gamma({b_prior}, {p_prior_g})",
    linewidth=2.5,
)
plt.plot(
    x_g,
    gamma.pdf(x_g, a=p_post_g, scale=1 / b_post),
    "g-",
    label=f"A posteriori główny",
    linewidth=2.5,
)

plt.plot(
    x_g,
    gamma.pdf(x_g, a=p_alt1, scale=1 / b_alt1),
    "b:",
    label=f"A priori alt 1: Gamma({b_alt1}, {p_alt1})",
    linewidth=2,
)
plt.plot(
    x_g,
    gamma.pdf(x_g, a=p_post_alt1, scale=1 / b_post_alt1),
    "b-",
    label=f"A posteriori alt 1",
    linewidth=1.5,
    alpha=0.7,
)

plt.plot(
    x_g,
    gamma.pdf(x_g, a=p_alt2, scale=1 / b_alt2),
    "r:",
    label=f"A priori alt 2: Gamma({b_alt2}, {p_alt2})",
    linewidth=2,
)
plt.plot(
    x_g,
    gamma.pdf(x_g, a=p_post_alt2, scale=1 / b_post_alt2),
    "r-",
    label=f"A posteriori alt 2",
    linewidth=1.5,
    alpha=0.7,
)

plt.title(
    "Wpływ wyboru a priori\n(Porównanie wariantów)", fontsize=12, fontweight="bold"
)
plt.xlabel("ξ", fontsize=11)
plt.ylabel("Gęstość", fontsize=11)
plt.legend(fontsize=9)
plt.grid(True, alpha=0.3)

plt.tight_layout()
plt.savefig("zadanie_11.png", dpi=150, bbox_inches="tight")
plt.show()

print(f"\nWarianty alternatywne (dla porównania):")
print(f"  Alt 1 - Gamma({b_alt1}, {p_alt1}): E(ξ|x) = {p_post_alt1/b_post_alt1:.4f}")
print(f"  Alt 2 - Gamma({b_alt2}, {p_alt2}): E(ξ|x) = {p_post_alt2/b_post_alt2:.4f}")

print("\n" + "=" * 70)
print("PODSUMOWANIE")
print("=" * 70)
print("✓ Zadanie 9: Porównanie gęstości a priori i a posteriori - WYŚWIETLONE")
print("✓ Zadanie 11: Ilustracja Gamma-Poisson z wariantami - WYŚWIETLONE")
print("=" * 70)
