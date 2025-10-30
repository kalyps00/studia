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
    vector<int> depth(n, 0);
    for (int i = 0; i < n; i++)
    {
        depth[i] = depth[parent[i]] + 1;
    }
    while (q--)
    {
        int u, v;
        cin >> u >> v;
        u--;
        v--; // 0-indexed
        if (depth[u] < depth[v])
            swap(u, v);
        int diff = depth[u] - depth[v];
        for (int j = 0; j < logn; j++)
        {
            if (diff & (1 << j))
            {
                u = up[u][j];
            }
        }
        if (u == v)
        {
            cout << u + 1 << '\n';
            continue;
        }
        for (int j = logn - 1; j >= 0; j--)
        {
            if (up[u][j] != up[v][j])
            {
                u = up[u][j];
                v = up[v][j];
                if (parent[u] == parent[v]) // - 0,01s
                {
                    break;
                }
            }
        }
        cout << parent[u] + 1 << '\n'; // 1-indexed
    }
}