#include <iostream>
#include <queue>
#include <vector>
using namespace std;
void bfs(int node, vector<vector<int>> graph, vector<int> &ans, vector<int> &visited)
{
    visited[node] = 1;
    queue<int> que;
    que.push(node);
    ans[node] = 0;
    while (!empty(que))
    {
        int newnode = que.front();
        que.pop();
        for (auto x : graph[newnode])
        {
            if (!visited[x])
            {
                visited[x] = 1;
                ans[x] = ans[newnode] + 1;
                que.push(x);
            }
        }
    }
}
int main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> graph(n);
    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    vector<int> ans(n, -1), visited(n, 0);

    bfs(0, graph, ans, visited);
    for (int i = 1; i < n; i++)
    {
        cout << ans[i] << " ";
    }
}