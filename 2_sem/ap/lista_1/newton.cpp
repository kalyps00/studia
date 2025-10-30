#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MOD = 1e9 + 7;
const int maks = 1e6;
vector<ll> fact(maks + 1);
vector<ll> inv_fact(maks + 1);

ll pow_mod(ll a, ll b)
{
    ll res = 1;
    while (b)
    {
        if (b & 1)
            res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

void preproces()
{
    fact[0] = 1;
    for (int i = 1; i <= maks; i++)
        fact[i] = fact[i - 1] * i % MOD;

    inv_fact[maks] = pow_mod(fact[maks], MOD - 2);
    for (int i = maks - 1; i >= 0; i--)
        inv_fact[i] = inv_fact[i + 1] * (i + 1) % MOD;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    preproces();

    int n;
    cin >> n;
    while (n--)
    {
        int a, b;
        cin >> a >> b;
        if (b > a)
        {
            cout << "0\n";
            continue;
        }
        if (b == 0 || b == a)
        {
            cout << "1\n";
            continue;
        }
        cout << (fact[a] * inv_fact[b] % MOD * inv_fact[a - b] % MOD) << '\n';
    }

    return 0;
}
