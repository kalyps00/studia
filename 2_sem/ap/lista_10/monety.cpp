#include <bits/stdc++.h>
using namespace std;

void dfs1(int v, const vector<vector<int>> &graph, vector<bool> &visited, stack<int> &order)
{
    visited[v] = true;
    for (int u : graph[v])
        if (!visited[u])
            dfs1(u, graph, visited, order);
    order.push(v);
}

void dfs2(int v, const vector<vector<int>> &rev_graph, vector<bool> &visited, vector<int> &component, int scc_id, vector<int> &node_to_scc)
{
    visited[v] = true;
    component.push_back(v);
    node_to_scc[v] = scc_id;
    for (int u : rev_graph[v])
        if (!visited[u])
            dfs2(u, rev_graph, visited, component, scc_id, node_to_scc);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<long long> coins(n + 1);
    for (int i = 1; i <= n; ++i)
    {
        cin >> coins[i];
    }

    vector<vector<int>> graph(n + 1), rev_graph(n + 1);
    for (int i = 0; i < m; ++i)
    {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        rev_graph[v].push_back(u);
    }
    vector<bool> visited(n + 1, false);
    stack<int> order;
    for (int i = 1; i <= n; ++i)
        if (!visited[i])
            dfs1(i, graph, visited, order);

    fill(visited.begin(), visited.end(), false);
    vector<int> node_to_scc(n + 1, -1);
    vector<vector<int>> sccs;
    int scc_count = 0;

    while (!order.empty())
    {
        int v = order.top();
        order.pop();
        if (!visited[v])
        {
            vector<int> component;
            dfs2(v, rev_graph, visited, component, scc_count, node_to_scc);
            sccs.push_back(component);
            ++scc_count;
        }
    }

    vector<long long> scc_value(scc_count, 0);
    for (int i = 1; i <= n; ++i)
    {
        scc_value[node_to_scc[i]] += coins[i];
    }
    vector<vector<int>> dag(scc_count);
    vector<int> indegree(scc_count, 0);
    for (int u = 1; u <= n; ++u)
    {
        for (int v : graph[u])
        {
            int su = node_to_scc[u], sv = node_to_scc[v];
            if (su != sv)
            {
                dag[su].push_back(sv);
                indegree[sv]++;
            }
        }
    }

    priority_queue<int, vector<int>, greater<int>> pq;
    for (int i = 0; i < scc_count; ++i)
        if (indegree[i] == 0)
            pq.push(i);

    vector<long long> dp = scc_value;
    while (!pq.empty())
    {
        int u = pq.top();
        pq.pop();
        for (int v : dag[u])
        {
            if (dp[v] < dp[u] + scc_value[v])
                dp[v] = dp[u] + scc_value[v];
            if (--indegree[v] == 0)
                pq.push(v);
        }
    }

    cout << *max_element(dp.begin(), dp.end()) << "\n";
    return 0;
}
