#include <bits/stdc++.h>
using namespace std;
#define MOD1 1000000007
#define MOD2 1000000009
#define A 37
#define B 53
typedef long long ll;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    string T, P;
    cin >> T >> P;
    int n = T.size(), m = P.size();

    if (m > n)
    {
        cout << "0\n";
        return 0;
    }

    ll highest_power_A = 1, highest_power_B = 1;
    for (int i = 0; i < m - 1; i++)
    {
        highest_power_A = (highest_power_A * A) % MOD1;
        highest_power_B = (highest_power_B * B) % MOD2;
    }

    ll hash_P1 = 0, hash_P2 = 0;
    for (int i = 0; i < m; i++)
    {
        hash_P1 = ((hash_P1 * A) % MOD1 + (P[i] - 'a' + 1)) % MOD1;
        hash_P2 = ((hash_P2 * B) % MOD2 + (P[i] - 'a' + 1)) % MOD2;
    }
    ll hash_T1 = 0, hash_T2 = 0;
    for (int i = 0; i < m; i++)
    {
        hash_T1 = ((hash_T1 * A) % MOD1 + (T[i] - 'a' + 1)) % MOD1;
        hash_T2 = ((hash_T2 * B) % MOD2 + (T[i] - 'a' + 1)) % MOD2;
    }

    int answer = 0;
    if (hash_P1 == hash_T1 && hash_P2 == hash_T2)
        answer++;

    // Przesuwanie
    for (int i = 0; i < n - m; i++)
    {
        // Aktualizacja pierwszego hasha
        hash_T1 = (hash_T1 - ((T[i] - 'a' + 1) * highest_power_A) % MOD1 + MOD1) % MOD1;
        hash_T1 = (hash_T1 * A) % MOD1;
        hash_T1 = (hash_T1 + (T[i + m] - 'a' + 1)) % MOD1;

        // Aktualizacja drugiego hasha
        hash_T2 = (hash_T2 - ((T[i] - 'a' + 1) * highest_power_B) % MOD2 + MOD2) % MOD2;
        hash_T2 = (hash_T2 * B) % MOD2;
        hash_T2 = (hash_T2 + (T[i + m] - 'a' + 1)) % MOD2;

        if (hash_P1 == hash_T1 && hash_P2 == hash_T2)
            answer++;
    }

    cout << answer << "\n";
    return 0;
}