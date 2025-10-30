#include <bits/stdc++.h>
using namespace std;

const long long INF = 1e18;

int main()
{
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    // Wczytanie krawędzi
    vector<tuple<int, int, long long>> edges;

    // Budowanie grafu
    vector<vector<int>> graph(n + 1);
    vector<vector<int>> rev_graph(n + 1);

    for (int i = 0; i < m; i++)
    {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        edges.push_back({u, v, w});
        graph[u].push_back(v);
        rev_graph[v].push_back(u);
    }

    // Sprawdzenie osiągalności z wierzchołka 1
    vector<bool> reachable_from_1(n + 1, false);
    queue<int> q;
    q.push(1);
    reachable_from_1[1] = true;

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        for (int v : graph[u])
        {
            if (!reachable_from_1[v])
            {
                reachable_from_1[v] = true;
                q.push(v);
            }
        }
    }

    // Sprawdzenie osiągalności do wierzchołka n
    vector<bool> can_reach_n(n + 1, false);
    q.push(n);
    can_reach_n[n] = true;

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        for (int v : rev_graph[u])
        {
            if (!can_reach_n[v])
            {
                can_reach_n[v] = true;
                q.push(v);
            }
        }
    }

    // Zmodyfikowany Bellman-Ford dla znalezienia najdłuższych ścieżek
    vector<long long> dist(n + 1, -INF);
    dist[1] = 0;

    for (int i = 0; i < n - 1; i++)
    {
        for (auto &[u, v, w] : edges)
        {
            if (reachable_from_1[u] && can_reach_n[v] &&
                dist[u] != -INF && dist[u] + w > dist[v])
            {
                dist[v] = dist[u] + w;
            }
        }
    }

    // Sprawdzenie dodatnich cykli
    bool has_positive_cycle = false;

    for (auto &[u, v, w] : edges)
    {
        if (reachable_from_1[u] && can_reach_n[v] &&
            dist[u] != -INF && dist[u] + w > dist[v])
        {
            has_positive_cycle = true;
            break;
        }
    }

    if (has_positive_cycle)
    {
        cout << -1 << endl;
    }
    else
    {
        cout << dist[n] << endl;
    }

    return 0;
}