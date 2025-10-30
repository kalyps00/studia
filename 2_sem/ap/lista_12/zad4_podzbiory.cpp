#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
#define MOD 1000000007

int main()
{
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(0);

    int n, q;
    cin >> n >> q;
    vector<int> hash_values(1000001);
    srand(42);

    for (int i = 0; i <= 1000000; i++)
    {
        hash_values[i] = ((rand() << 15) ^ rand()) % 1000000000 + 1;
    }
    vector<int> a(n + 1), b(n + 1);
    vector<ll> prefix_a(n + 1, 0), prefix_b(n + 1, 0);

    for (int i = 1; i <= n; i++)
    {
        int val;
        cin >> val;
        a[i] = hash_values[val];
        prefix_a[i] = prefix_a[i - 1] + a[i];
    }

    for (int i = 1; i <= n; i++)
    {
        int val;
        cin >> val;
        b[i] = hash_values[val];
        prefix_b[i] = prefix_b[i - 1] + b[i];
    }
    for (int i = 0; i < q; i++)
    {
        int l1, r1, l2, r2;
        cin >> l1 >> r1 >> l2 >> r2;
        if ((r1 - l1) != (r2 - l2))
        {
            cout << "NIE\n";
            continue;
        }
        ll sum_a = prefix_a[r1] - prefix_a[l1 - 1];
        ll sum_b = prefix_b[r2] - prefix_b[l2 - 1];

        if (sum_a == sum_b)
        {
            cout << "TAK\n";
        }
        else
        {
            cout << "NIE\n";
        }
    }

    return 0;
}