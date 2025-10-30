#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, q;
    cin >> n >> q;
    int lg = log2(n) + 1;
    vector<vector<int>> sparse_table(n, vector<int>(lg));
    for (int i = 0; i < n; i++)
    {
        cin >> sparse_table[i][0];
    }
    for (int i = 1; i < lg; i++)
    {
        for (int j = 0; j + (1 << i) <= n; j++)
        {
            sparse_table[j][i] = min(sparse_table[j][i - 1],
                                     sparse_table[j + (1 << (i - 1))][i - 1]);
        }
    }
    while (q--)
    {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        int len = b - a + 1;
        int k = log2(len);
        cout << min(sparse_table[a][k], sparse_table[b - (1 << k) + 1][k]) << '\n';
    }

    return 0;
}
