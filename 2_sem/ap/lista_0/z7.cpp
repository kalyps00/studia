#include <iostream>
#include <vector>
using namespace std;
void dfs(int node, vector<vector<int>> &graph, vector<bool> &visited)
{
    visited[node] = true;
    for (auto x : graph[node])
    {
        if (!visited[x])
        {
            dfs(x, graph, visited);
        }
    }
}
int main()
{
    int wierzcholki, krawedzie;
    cin >> wierzcholki >> krawedzie;
    vector<vector<int>> graph(wierzcholki);
    for (int i = 0; i < krawedzie; i++)
    {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    vector<bool> visited(wierzcholki, false);
    int ans = -1;
    for (int i = 0; i < wierzcholki; i++)
    {
        if (!visited[i])
        {
            ans++;
            dfs(i, graph, visited);
        }
    }
    cout << ans;
    return 0;
}