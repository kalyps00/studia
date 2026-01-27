import math

# --- Funkcje podcałkowe (bez zmian) ---
def f_a(x):
    return 2026 * (x**8) + 1977 * (x**6) - 1410 * (x**3) - 1791 * x + 1

def f_b(x):
    return 1.0 / (1.0 + 25.0 * x**2)

def f_c(x):
    return math.log(x + 1.0)

# --- Wartości dokładne (bez zmian) ---
def exact_a():
    def F(x):
        return (2026/9)*x**9 + (1977/7)*x**7 - (1410/4)*x**4 - (1791/2)*x**2 + x
    return F(7) - F(-1)

def exact_b():
    return (math.atan(5) - math.atan(-5)) / 5.0

def exact_c():
    def F(x):
        return (x + 1) * math.log(x + 1) - x
    return F(5) - F(0)

# --- Algorytm Romberga ---
def romberg_integration(f, a, b, max_m=10):
    """
    Oblicza tablicę Romberga T[m, k].
    Indeksowanie:
      m (wiersze): od 0 do max_m (liczba przedziałów = 2^m)
      k (kolumny): od 0 do m (rząd dokładności)
    
    Najlepszy wynik znajduje się w elemencie T[max_m, max_m].
    """
    table = {}
    
    # 1. Obliczanie pierwszej kolumny T[m, 0] (Metoda Trapezów)
    h = b - a
    # T[0, 0] -> 1 przedział
    table[(0, 0)] = 0.5 * h * (f(a) + f(b))
    
    last_T = table[(0, 0)]
    
    for m in range(1, max_m + 1):
        # Liczba nowych podprzedziałów (tylko te, które dodajemy)
        n_prev = 2**(m - 1)
        h_prev = (b - a) / n_prev 
        
        # Suma wartości w nowych punktach (środkach dotychczasowych przedziałów)
        sum_f = 0.0
        for i in range(1, n_prev + 1):
            x_new = a + 0.5 * (2 * i - 1) * h_prev
            sum_f += f(x_new)
            
        M_n = h_prev * sum_f
        
        # Rekurencja trapezów: T_new = 1/2 * T_old + 1/2 * M_n
        current_T = 0.5 * (last_T + M_n)
        table[(m, 0)] = current_T
        last_T = current_T

    # 2. Obliczanie pozostałych kolumn (Ekstrapolacja Richardsona)
    # T[m, k] powstaje z T[m, k-1] i T[m-1, k-1]
    for m in range(1, max_m + 1):
        for k in range(1, m + 1):
            # Wzór Richardsona
            val = (4**k * table[(m, k - 1)] - table[(m - 1, k - 1)]) / (4**k - 1)
            table[(m, k)] = val
            
    return table

def print_results(label, table, exact_val, max_m):
    print(f"\nWyniki dla całki {label}:")
    print(f"Wartość dokładna: {exact_val}")
    
    # Najlepszy wynik zgodnie z życzeniem w T[10, 10] (dla max_m=10)
    best_approx = table[(max_m, max_m)]
    print(f"Najlepsze przybliżenie T({max_m}, {max_m}): {best_approx}")
    print(f"Błąd bezwzględny: {abs(best_approx - exact_val)}")
    
    # Wypisanie przekątnej dla podglądu zbieżności
    print("Elementy z przekątnej T(k, k):")
    for k in range(max_m + 1):
        val = table[(k, k)]
        err = abs(val - exact_val)
        print(f"  k={k:<2}: {val:.16f} | Błąd: {err:.2e}")

def main():
    # ZMIANA: Ustawienie max_m na 10, aby wynik końcowy był w T[10, 10]
    m_max = 10
    
    # a)
    tbl_a = romberg_integration(f_a, -1, 7, m_max)
    print_results("a)", tbl_a, exact_a(), m_max)
    
    # b)
    tbl_b = romberg_integration(f_b, -1, 1, m_max)
    print_results("b)", tbl_b, exact_b(), m_max)
    
    # c)
    tbl_c = romberg_integration(f_c, 0, 5, m_max)
    print_results("c)", tbl_c, exact_c(), m_max)

if __name__ == "__main__":
    main()