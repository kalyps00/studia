import numpy as np
import matplotlib.pyplot as plt
from scipy.stats import beta

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

print("\n" + "=" * 70)
print("✓ Zadanie 9: Porównanie gęstości a priori i a posteriori - WYŚWIETLONE")
print("=" * 70)
