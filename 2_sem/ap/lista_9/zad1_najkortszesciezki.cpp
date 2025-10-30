#include <bits/stdc++.h>
using namespace std;

struct edge
{
    int v;
    long long w;
    bool operator>(const edge &other) const
    {
        return w > other.w;
    }
};

void dijkstra(int start, vector<vector<edge>> &graph, vector<long long> &dist)
{

    priority_queue<edge, vector<edge>, greater<edge>> pq;

    pq.push({start, 0});
    dist[start] = 0;

    while (!pq.empty())
    {
        int u = pq.top().v;
        long long dist_u = pq.top().w;
        pq.pop();

        // Jeśli wyciągnięta odległość jest większa niż aktualna, pomijamy
        if (dist_u > dist[u])
        {
            continue;
        }
        for (auto &e : graph[u])
        {
            int v = e.v;
            long long w = e.w;

            // Jeśli znaleźliśmy krótszą drogę do wierzchołka v
            if (dist[u] + w < dist[v])
            {
                dist[v] = dist[u] + w;
                pq.push({v, dist[v]});
            }
        }
    }
}

int main()
{
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    vector<vector<edge>> graph(n + 1);
    vector<long long> dist(n + 1, LLONG_MAX);

    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
    }

    dijkstra(1, graph, dist);

    for (int i = 1; i <= n; i++)
    {
        cout << dist[i] << " ";
    }

    return 0;
}