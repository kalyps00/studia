#include <bits/stdc++.h>
using namespace std;

void dfs(int v, int parent, vector<vector<int>> &graph, vector<int> &depth, vector<int> &parent_arr)
{
    parent_arr[v] = parent;
    for (int u : graph[v])
    {
        if (u != parent)
        {
            depth[u] = depth[v] + 1;
            dfs(u, v, graph, depth, parent_arr);
        }
    }
}

int lca(int u, int v, vector<int> &depth, vector<vector<int>> &up)
{
    if (depth[u] < depth[v])
    {
        swap(u, v);
    }

    int log_n = up[0].size();

    // Wyrównanie głębokości
    int diff = depth[u] - depth[v];
    for (int j = 0; j < log_n; j++)
    {
        if (diff & (1 << j))
        {
            u = up[u][j];
        }
    }

    if (u == v)
        return u;

    // Szukanie LCA
    for (int j = log_n - 1; j >= 0; j--)
    {
        if (up[u][j] != up[v][j])
        {
            u = up[u][j];
            v = up[v][j];
        }
    }

    return up[u][0];
}

// Funkcja DFS do propagacji wartości w górę drzewa
void dfs_count(int v, int parent, vector<vector<int>> &graph, vector<int> &sciezki)
{
    for (int u : graph[v])
    {
        if (u != parent)
        {
            dfs_count(u, v, graph, sciezki);
            sciezki[v] += sciezki[u]; // Dodajemy wartości od dzieci
        }
    }
}

void add_path_diff(int u, int v, int lca_val, vector<int> &diff, vector<vector<int>> &up)
{
    diff[u]++;       // +1 od u
    diff[v]++;       // +1 od v
    diff[lca_val]--; // -1 od LCA (żeby nie liczyć dwa razy)

    // -1 od rodzica LCA
    int parent_lca = up[lca_val][0];
    if (parent_lca != -1)
    {
        diff[parent_lca]--;
    }
}

int main()
{
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> graph(n);

    for (int i = 0; i < n - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        u--;
        v--; // 0-indexing
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    vector<int> depth(n, 0);
    vector<int> parent(n, -1);
    dfs(0, -1, graph, depth, parent);

    int log_n = log2(n) + 1;
    vector<vector<int>> up(n, vector<int>(log_n, -1));
    for (int i = 0; i < n; i++)
    {
        up[i][0] = parent[i];
    }
    for (int j = 1; j < log_n; j++)
    {
        for (int i = 0; i < n; i++)
        {
            if (up[i][j - 1] != -1)
            {
                up[i][j] = up[up[i][j - 1]][j - 1];
            }
        }
    }
    vector<int> diff(n, 0);
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        u--;
        v--; // 0-indexing

        int lca_val = lca(u, v, depth, up);
        add_path_diff(u, v, lca_val, diff, up);
    }
    dfs_count(0, -1, graph, diff);
    for (int i = 0; i < n; i++)
    {
        cout << diff[i] << " ";
    }

    return 0;
}