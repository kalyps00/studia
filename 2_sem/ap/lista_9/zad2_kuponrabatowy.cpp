#include <bits/stdc++.h>
using namespace std;

struct edge
{
    int v;
    long long w;
    int used;

    bool operator>(const edge &other) const
    {
        return w > other.w;
    }
};

void dijkstra_with_coupon(int start, int end, vector<vector<edge>> &graph, vector<vector<long long>> &dist)
{
    priority_queue<edge, vector<edge>, greater<edge>> pq;

    pq.push({start, 0, 0});
    dist[start][0] = 0;

    while (!pq.empty())
    {
        int u = pq.top().v;
        long long d = pq.top().w;
        int used = pq.top().used;
        pq.pop();

        // Jeśli ten stan jest przestarzały, pomijamy
        if (d > dist[u][used])
        {
            continue;
        }

        for (const auto &e : graph[u])
        {
            int v = e.v;
            long long w = e.w;

            // Jeśli kupon nie został jeszcze użyty
            if (used == 0)
            {
                // Opcja 1: Nie używamy kuponu na tej krawędzi
                if (dist[u][0] + w < dist[v][0])
                {
                    dist[v][0] = dist[u][0] + w;
                    pq.push({v, dist[v][0], 0});
                }

                // Opcja 2: Używamy kupon na tej krawędzi
                long long discounted_w = w / 2; // Zaokrąglenie w dół
                if (dist[u][0] + discounted_w < dist[v][1])
                {
                    dist[v][1] = dist[u][0] + discounted_w;
                    pq.push({v, dist[v][1], 1});
                }
            }
            // Jeśli kupon został już użyty
            else
            {
                if (dist[u][1] + w < dist[v][1])
                {
                    dist[v][1] = dist[u][1] + w;
                    pq.push({v, dist[v][1], 1});
                }
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

    vector<vector<long long>> dist(n + 1, vector<long long>(2, LLONG_MAX));

    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back({v, w, 0});
    }

    dijkstra_with_coupon(1, n, graph, dist);
    cout << dist[n][1] << endl;

    return 0;
}