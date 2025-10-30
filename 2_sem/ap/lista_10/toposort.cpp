#include <bits/stdc++.h>
using namespace std;

int main()
{
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> graph(n + 1);
    vector<int> incoming_edges(n + 1, 0);

    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        incoming_edges[v]++;
    }
    priority_queue<int, vector<int>, greater<int>> available_vertices;

    // wszystkie bez krawedzie wchodzacej
    for (int i = 1; i <= n; i++)
    {
        if (incoming_edges[i] == 0)
        {
            available_vertices.push(i);
        }
    }

    vector<int> result;
    while (!available_vertices.empty())
    {
        int current = available_vertices.top();
        available_vertices.pop();
        result.push_back(current);

        // usuwamy wychodzace krawedzie
        for (int neighbor : graph[current])
        {
            incoming_edges[neighbor]--;
            // dodajemy nowe bez krawedzi wchodzacej
            if (incoming_edges[neighbor] == 0)
            {
                available_vertices.push(neighbor);
            }
        }
    }
    // cykl
    if (result.size() < n)
    {
        cout << "IMPOSSIBLE" << endl;
    }
    else
    {
        for (int i = 0; i < n; i++)
        {
            cout << result[i] << " ";
        }
        cout << endl;
    }

    return 0;
}