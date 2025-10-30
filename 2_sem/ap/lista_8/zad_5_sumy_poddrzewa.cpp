#include <bits/stdc++.h>
using namespace std;

const int R = (1 << 20);

void dfs(int v, int parent, int &timer, const vector<vector<int>> &adj, vector<int> &tin, vector<int> &tout, vector<long long> &tree, const vector<int> &vals)
{
    tin[v] = ++timer;
    tree[tin[v] - 1 + R] = vals[v];
    for (int u : adj[v])
    {
        if (u != parent)
            dfs(u, v, timer, adj, tin, tout, tree, vals);
    }
    tout[v] = ++timer;
    tree[tout[v] - 1 + R] = 0;
}

void build(vector<long long> &tree)
{
    for (int i = R - 1; i >= 1; i--)
        tree[i] = tree[2 * i] + tree[2 * i + 1];
}

void update(vector<long long> &tree, int v, long long x)
{
    v += R;
    tree[v] = x;
    while (v > 1)
    {
        v /= 2;
        tree[v] = tree[2 * v] + tree[2 * v + 1];
    }
}

long long query(const vector<long long> &tree, int s, int e)
{
    s += R;
    e += R;
    long long res = tree[s];
    if (s != e)
        res += tree[e];
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
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N, Q;
    cin >> N >> Q;
    vector<vector<int>> adj(N + 1);
    vector<int> vals(N + 1);
    for (int i = 1; i <= N; ++i)
        cin >> vals[i];
    for (int i = 0; i < N - 1; ++i)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> tin(N + 1), tout(N + 1);
    vector<long long> tree(2 * R, 0);
    int timer = 0;

    dfs(1, -1, timer, adj, tin, tout, tree, vals);
    build(tree);

    while (Q--)
    {
        int type;
        cin >> type;
        if (type == 1)
        {
            int v, x;
            cin >> v >> x;
            update(tree, tin[v] - 1, x);
        }
        else
        {
            int v;
            cin >> v;
            cout << query(tree, tin[v] - 1, tout[v] - 1) << '\n';
        }
    }
}
