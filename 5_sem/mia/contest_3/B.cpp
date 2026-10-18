
#include <bits/stdc++.h>
using namespace std;

void solve()
{
    int n, m;
    cin >> n;

    vector<long long> a(n);

    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    cin >> m;

    long long sum_def = accumulate(a.begin(), a.end(), 0LL);

    sort(a.begin(), a.end());

    for (int i = 0; i < m; i++)
    {
        long long attack, defense;
        cin >> attack >> defense;

        int attack_hero = lower_bound(a.begin(), a.end(), attack) - a.begin();

        if (attack_hero < n && a[attack_hero] == attack)
        {
            cout << max(0LL, defense - (sum_def - a[attack_hero])) << "\n";
        }
        else if (attack_hero == n)
        {
            cout << attack - a[n - 1] + max(0LL, defense - (sum_def - a[n - 1])) << "\n";
        }
        else if (attack_hero == 0)
        {
            cout << max(0LL, attack - a[0]) + max(0LL, defense - (sum_def - a[0])) << "\n";
        }
        else
        {
            long long cost1 = max(0LL, attack - a[attack_hero - 1]) + max(0LL, defense - (sum_def - a[attack_hero - 1]));

            long long cost2 = max(0LL, defense - (sum_def - a[attack_hero])) + max(0LL, attack - a[attack_hero]);

            cout << min(cost1, cost2) << "\n";
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
