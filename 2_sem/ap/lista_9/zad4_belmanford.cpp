#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    vector<tuple<int, int, int>> edges;

    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        edges.push_back({u, v, w});
    }

    // Inicjalizacja odległości - wszystkie na 0
    // (możemy sobie na to pozwolić, bo szukamy tylko ujemnego cyklu)
    vector<long long> dist(n + 1, 0);
    vector<int> prev(n + 1, -1); // Poprzednik w ścieżce

    // Wierzchołek, który należy do ujemnego cyklu
    int negative_cycle_vertex = -1;

    // Bellman-Ford: n iteracji relaksacji krawędzi
    // Standardowo wystarczy n-1 iteracji, ale wykonujemy n iteracji,
    // aby wykryć ujemny cykl
    for (int i = 0; i < n; i++)
    {
        negative_cycle_vertex = -1;

        for (auto &[u, v, w] : edges)
        {
            if (dist[u] + w < dist[v])
            {
                dist[v] = dist[u] + w;
                prev[v] = u;
                negative_cycle_vertex = v;
            }
        }
    }

    // Jeśli po n iteracjach nadal można relaksować krawędzie,
    // to istnieje ujemny cykl
    if (negative_cycle_vertex == -1)
    {
        cout << "NO" << endl;
        return 0;
    }

    cout << "YES" << endl;

    // Znajdowanie wierzchołka należącego do cyklu
    // Cofamy się n razy, aby na pewno trafić do cyklu
    for (int i = 0; i < n; i++)
    {
        negative_cycle_vertex = prev[negative_cycle_vertex];
    }

    // Rekonstruujemy cykl
    vector<int> cycle;
    int current = negative_cycle_vertex;

    do
    {
        cycle.push_back(current);
        current = prev[current];
    } while (current != negative_cycle_vertex);

    // Odwracamy cykl, aby wypisać wierzchołki w kolejności przechodzenia
    reverse(cycle.begin(), cycle.end());

    // Dodajemy pierwszy wierzchołek na końcu, aby zamknąć cykl
    cycle.push_back(cycle[0]);

    // Wypisujemy cykl
    for (size_t i = 0; i < cycle.size() - 1; i++)
    {
        cout << cycle[i] << " ";
    }
    cout << cycle[cycle.size() - 1] << endl;

    return 0;
}