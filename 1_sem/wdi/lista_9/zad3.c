int poprawne(int a[], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            // Sprawdzenie, czy dwa hetmany są w tej samej kolumnie
            // lub na tej samej przekątnej
            if (a[i] == a[j] || abs(a[i] - a[j]) == abs(i - j))
            {
                return 0;
            }
        }
    }
    return 1;
}
int hetmany(int n, int k, int a[n]) // k=0
{
    if (k == n)
        return poprawne(a, n);
    for (int i = 0; i < n; i++)
    {
        a[k] = i;
        if (hetmany(n, k + 1, a))
            return 1;
    }
    return 0;
}