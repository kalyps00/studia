#include <bits/stdc++.h>
using namespace std;

void dfs1(int v, vector<vector<int>> &graph, vector<bool> &visited, stack<int> &order_stack)
{
    visited[v] = true;
    for (int u : graph[v])
    {
        if (!visited[u])
            dfs1(u, graph, visited, order_stack);
    }
    order_stack.push(v);
}

void dfs2(int v, vector<vector<int>> &reverse_graph, vector<bool> &visited, vector<int> &component)
{
    visited[v] = true;
    component.push_back(v);
    for (int u : reverse_graph[v])
    {
        if (!visited[u])
            dfs2(u, reverse_graph, visited, component);
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> graph(n + 1), reverse_graph(n + 1);
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        reverse_graph[v].push_back(u);
    }

    vector<bool> visited(n + 1, false);
    stack<int> order_stack;
    for (int i = 1; i <= n; i++)
    {
        if (!visited[i])
            dfs1(i, graph, visited, order_stack);
    }

    fill(visited.begin(), visited.end(), false);
    vector<vector<int>> components;

    while (!order_stack.empty())
    {
        int v = order_stack.top();
        order_stack.pop();
        if (!visited[v])
        {
            vector<int> component;
            dfs2(v, reverse_graph, visited, component);
            sort(component.begin(), component.end());
            components.push_back(component);
        }
    }
    // sortujemy skladowe spojne po pierwszym elemencie
    sort(components.begin(), components.end(), [](const vector<int> &a, const vector<int> &b)
         { return a[0] < b[0]; });

    vector<int> final_ids(n + 1);
    for (int id = 0; id < components.size(); ++id)
    {
        for (int u : components[id])
        {
            final_ids[u] = id + 1;
        }
    }

    cout << components.size() << "\n";
    for (int i = 1; i <= n; i++)
    {
        cout << final_ids[i] << " ";
    }

    return 0;
}
