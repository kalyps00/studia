#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> graph_adjacencies;
vector<int> incoming_edges_count;
vector<int> outgoing_edges_count;
vector<int> constructed_path;
vector<queue<int>> current_edges_per_node;

void build_eulerian_path(int current_node)
{
    while (!current_edges_per_node[current_node].empty())
    {
        int next_node = current_edges_per_node[current_node].front();
        current_edges_per_node[current_node].pop();
        build_eulerian_path(next_node);
    }
    constructed_path.push_back(current_node);
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int num_nodes, num_edges_count;
    cin >> num_nodes >> num_edges_count;
    graph_adjacencies.resize(num_nodes + 1);
    incoming_edges_count.resize(num_nodes + 1, 0);
    outgoing_edges_count.resize(num_nodes + 1, 0);
    current_edges_per_node.resize(num_nodes + 1);

    for (int i = 0; i < num_edges_count; i++)
    {
        int from_node, to_node;
        cin >> from_node >> to_node;
        graph_adjacencies[from_node].push_back(to_node);
        outgoing_edges_count[from_node]++;
        incoming_edges_count[to_node]++;
    }
    bool conditions_met = true;
    int designated_start_node = 1, designated_end_node = num_nodes;
    if (outgoing_edges_count[designated_start_node] - incoming_edges_count[designated_start_node] != 1)
        conditions_met = false;
    if (incoming_edges_count[designated_end_node] - outgoing_edges_count[designated_end_node] != 1)
        conditions_met = false;
    for (int node_val = 1; node_val <= num_nodes; node_val++)
    {
        if (node_val == designated_start_node || node_val == designated_end_node)
            continue;
        if (incoming_edges_count[node_val] != outgoing_edges_count[node_val])
            conditions_met = false;
    }
    if (!conditions_met)
    {
        cout << "IMPOSSIBLE";
        return 0;
    }
    vector<bool> node_has_been_visited(num_nodes + 1, false);
    queue<int> nodes_to_visit_q;
    if (num_nodes > 0)
    {
        nodes_to_visit_q.push(designated_start_node);
        node_has_been_visited[designated_start_node] = true;
    }

    while (!nodes_to_visit_q.empty())
    {
        int u_node = nodes_to_visit_q.front();
        nodes_to_visit_q.pop();
        for (int v_node : graph_adjacencies[u_node])
        {
            if (!node_has_been_visited[v_node])
            {
                node_has_been_visited[v_node] = true;
                nodes_to_visit_q.push(v_node);
            }
        }
    }
    if (num_nodes > 0 && !node_has_been_visited[designated_end_node] && num_edges_count > 0)
    {
        cout << "IMPOSSIBLE";
        return 0;
    }
    for (int i = 1; i <= num_nodes; ++i)
    {
        if (outgoing_edges_count[i] > 0 && !node_has_been_visited[i])
        {
        }
    }

    for (int u_val = 1; u_val <= num_nodes; u_val++)
    {
        for (int v_val : graph_adjacencies[u_val])
            current_edges_per_node[u_val].push(v_val);
    }

    if (num_nodes > 0)
    {
        build_eulerian_path(designated_start_node);
    }
    else if (num_edges_count > 0)
    {
        cout << "IMPOSSIBLE";
        return 0;
    }

    reverse(constructed_path.begin(), constructed_path.end());

    if (num_edges_count == 0)
    {
        if (num_nodes >= 1 && designated_start_node == designated_end_node)
        {
            if (constructed_path.size() == 1 && constructed_path.front() == designated_start_node)
            {
                cout << constructed_path.front();
            }
            else
            {
                if (num_nodes == 1 && designated_start_node == 1 && designated_end_node == 1)
                {
                    cout << "1";
                }
                else
                {
                    cout << "IMPOSSIBLE";
                }
            }
        }
        else if (num_nodes == 0 && num_edges_count == 0)
        {
            cout << "IMPOSSIBLE";
        }
        else
        {
            cout << "IMPOSSIBLE";
        }
    }
    else if (constructed_path.size() != num_edges_count + 1 || constructed_path.front() != designated_start_node || constructed_path.back() != designated_end_node)
    {
        cout << "IMPOSSIBLE";
    }
    else
    {
        for (size_t i = 0; i < constructed_path.size(); ++i)
        {
            cout << constructed_path[i] << (i == constructed_path.size() - 1 ? "" : " ");
        }
    }
}