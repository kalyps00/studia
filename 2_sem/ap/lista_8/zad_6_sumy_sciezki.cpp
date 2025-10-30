#include <bits/stdc++.h>
using namespace std;

const int R = (1 << 20);

void dfs(int v, int parent,
         int &timer,
         const vector<vector<int>> &adj,
         const vector<int> &vals,
         vector<int> &tin,
         vector<int> &tout,
         vector<long long> &tree)
{
    tin[v] = ++timer;
    tree[tin[v] - 1 + R] = vals[v];
    for (int u : adj[v])
    {
        if (u == parent)
            continue;
        dfs(u, v, timer, adj, vals, tin, tout, tree);
    }
    tout[v] = ++timer;
    tree[tout[v] - 1 + R] = -vals[v];
}

void build(vector<long long> &tree)
{
    for (int i = R - 1; i >= 1; --i)
    {
        tree[i] = tree[2 * i] + tree[2 * i + 1];
    }
}

void pointUpdate(vector<long long> &tree, int pos, long long x)
{
    int idx = pos + R;
    tree[idx] = x;
    while (idx > 1)
    {
        idx /= 2;
        tree[idx] = tree[2 * idx] + tree[2 * idx + 1];
    }
}

long long rangeQuery(const vector<long long> &tree, int l, int r)
{
    int s = l + R;
    int e = r + R;
    long long res = tree[s] + (s == e ? 0 : tree[e]);
    while (s / 2 != e / 2)
    {
        if (s % 2 == 0)
            res += tree[s + 1];
        if (e % 2 == 1)
            res += tree[e - 1];
        s /= 2;
        e /= 2;
    }
    return res;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, Q;
    cin >> N >> Q;

    vector<int> vals(N + 1);
    for (int i = 1; i <= N; ++i)
    {
        cin >> vals[i];
    }

    vector<vector<int>> adj(N + 1);
    for (int i = 0; i < N - 1; ++i)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> tin(N + 1), tout(N + 1);
    vector<long long> tree(2 * R, 0LL);
    int timer = 0;

    // Build Euler tour: +val at entry, -val at exit
    dfs(1, -1, timer, adj, vals, tin, tout, tree);
    build(tree);

    while (Q--)
    {
        int type;
        cin >> type;
        if (type == 1)
        {
            int v;
            long long x;
            cin >> v >> x;
            // update both entry and exit positions
            pointUpdate(tree, tin[v] - 1, x);
            pointUpdate(tree, tout[v] - 1, -x);
        }
        else
        {
            int v;
            cin >> v;
            // query sum on path from root (tin[1]-1) to tin[v]-1
            long long ans = rangeQuery(tree, tin[1] - 1, tin[v] - 1);
            cout << ans << '\n';
        }
    }

    return 0;
}
