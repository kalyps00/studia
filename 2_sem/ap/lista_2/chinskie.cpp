#include <bits/stdc++.h>
using namespace std;
long long ex_gcd(long long a, long long b, long long &x, long long &y)
{
    if (b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }
    long long x1, y1, gcd;
    gcd = ex_gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return gcd;
}
long long invmod(long long a, long long m)
{
    long long x, y;
    ex_gcd(a, m, x, y);
    return (x % m + m) % m; // ujemne
}
int main()
{
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(0);
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int k;
        cin >> k;
        vector<pair<int, int>> pary(k);
        long long M = 1;
        for (int j = 0; j < k; j++)
        {
            cin >> pary[j].first >> pary[j].second;
            M *= pary[j].first;
        }
        long long wynik = 0;
        for (auto p : pary)
        {
            int invers_mod = invmod(M / p.first, p.first);
            wynik += (p.second * M / p.first * invers_mod) % M;
        }
        wynik = (wynik % M + M) % M; // ujemne
        cout << wynik << '\n';
    }
    return 0;
}