#include <stdio.h>
int silnia(int n)
{
    int wynik = 1;
    for (int i = 2; i <= n; i++)
    {
        wynik *= i;
    }
    return wynik;
}
void reprezentacja(int n)
{
    int i = 0;
    while (i * silnia(i) <= n)
    {
        i++;
    }
    i--;
    for (; n; i--)
    {

        if (silnia(i) * i <= n)
        {
            n -= silnia(i) * i;
            printf("%d, ", i);
        }
        else
            printf("0, ");
    }
    while (i)
    {
        printf("0, ");
        i--;
    }
}

int gcd_iterative(int n, int m)
{
    // Gdy jedna z liczb to 0, zwróć drugą liczbę jako NWD
    if (n == 0)
        return m;
    if (m == 0)
        return n;

    // Usuwanie wspólnych czynników 2 z obu liczb
    int result = 1;
    while (n % 2 == 0 && m % 2 == 0)
    {
        n /= 2;
        m /= 2;
        result *= 2; // Każde wspólne dzielenie przez 2 zwiększa NWD o czynnik 2
    }

    // Teraz co najmniej jedna z liczb jest nieparzysta
    while (n != m)
    {
        if (n % 2 == 0)
        {
            n /= 2;
        }
        else if (m % 2 == 0)
        {
            m /= 2;
        }
        // NWD(n, m);
        else if (n > m)
        {
            n = (n - m) / 2;
        }
        else
        {
            m = (m - n) / 2;
        }
    }

    // Wynikiem jest n pomnożone przez wszystkie usunięte czynniki 2
    return n * result;
}
int calculate_G(int n)
{
    int G0 = 1, G1 = 1, G2 = 1, Gn;
    for (int i = 3; i <= n; i++)
    {
        Gn = G0 + G1 + G2;
        G0 = G1;
        G1 = G2;
        G2 = Gn;
    }
    return Gn;
}

int fTrec(int n, int m)
{
    if (m == 0)
        return n;
    if (n == 0)
        return m;
    return fTrec(n - 1, m) + 2 * fTrec(n, m - 1);
}

int fTiter(int n, int m)
{
    int T[n + 1][m + 1];

    for (int i = 0; i <= n; i++)
        T[i][0] = i;

    for (int j = 0; j <= m; j++)
        T[0][j] = j;

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            T[i][j] = T[i - 1][j] + 2 * T[i][j - 1];
        }
    }

    return T[n][m];
}
int fibonacci_mod(int k, int r)
{
    if (k == 0)
        return 0;
    if (k == 1)
        return 1;

    int a = 0, b = 1, fib;

    for (int i = 2; i <= k; i++)
    {
        fib = (a + b) % r; // Obliczamy F(i) modulo r
        a = b;
        b = fib;
    }

    return fib;
}
/* def fibonacci(k):
    if k == 0:
        return 0
    elif k == 1:
        return 1

    a = 0  # F_0
    b = 1  # F_1
    for i in range(2, k + 1):
        temp = a + b  # Obliczanie następnego wyrazu ciągu
        a = b         # Aktualizacja F_{n-2} do F_{n-1}
        b = temp      # Aktualizacja F_{n-1} do F_n
    return b%r

 */
int find_min_k(int n, int m)
{
    int k = 0;
    int power = 1;
    while (power < m)
    {
        power *= n;
        k++;
    }
    return k;
}

int main()
{
    int n = 2, m = 17;
    printf("Najmniejsze k dla %d^k >= %d to %d\n", n, m, find_min_k(n, m));
    return 0;
}