#include <bits/stdc++.h>
using namespace std;
int main()
{
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(0);
    int n, q;
    cin >> n >> q;
    vector<int> parent(n + 1);
    parent[0] = -1;
    for (int i = 1; i < n; i++)
    {
        cin >> parent[i];
        parent[i]--; // 0-indexed
    }
    int logn = log2(n) + 1;
    vector<vector<int>> up(n, vector<int>(logn, -1));
    for (int i = 0; i < n; i++)
    {
        up[i][0] = parent[i];
    }
    for (int j = 1; j < logn; j++)
    {
        for (int i = 0; i < n; i++)
        {
            if (up[i][j - 1] != -1)
                up[i][j] = up[up[i][j - 1]][j - 1];
        }
    }
    while (q--)
    {
        int v, k;
        cin >> v >> k;
        v--; // 0-indexed
        for (int j = 0; j < logn; j++)
        {
            if (k & (1 << j))
            {
                v = up[v][j];
                if (v == -1)
                    break;
            }
        }
        cout << (v == -1 ? -1 : v + 1) << '\n'; // 1-indexed
    }
}
