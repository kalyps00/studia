#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, q;
    cin >> n;
    vector<int> numbers(n);
    for (int i = 0; i < n; i++)
    {
        cin >> numbers[i];
    }
    cin >> q;

    const int T = 500; // +/- sqrt(1e6)
    vector<long long> tab[T];
    // tablica przeskokow o b
    for (int b = 1; b < T; b++) // tab[skok ile][element -> koniec]
    {
        tab[b].resize(n);                // ustawiamy vektor na n bo tyle tam mamy elementow
        for (int i = n - 1; i >= 0; i--) // sumy prefiksowe od konca
        {
            long long sum = numbers[i];
            if (i + b < n) // jest nastepna suma
            {
                sum += tab[b][i + b]; // nastepna suma
            }
            tab[b][i] = sum;
        }
    }

    for (int i = 0; i < q; i++)
    {
        int a, b;
        cin >> a >> b;
        a--;
        long long ans = 0;
        if (b < T)
        {
            ans = tab[b][a];
        }
        else
        {
            for (int j = a; j < n; j += b)
            {
                ans += numbers[j];
            }
        }
        cout << ans << "\n";
    }

    return 0;
}
