#include <bits/stdc++.h>
using namespace std;

struct GraphEdgeData
{
    int target_vertex;
    int id_edge;
};

vector<vector<GraphEdgeData>> adjacency_list_data;
vector<bool> edge_is_processed_flag;
vector<int> resulting_path_nodes;

void construct_path(int current_vertex_val)
{
    while (!adjacency_list_data[current_vertex_val].empty())
    {
        GraphEdgeData edge = adjacency_list_data[current_vertex_val].back();
        adjacency_list_data[current_vertex_val].pop_back();

        int neighbor_vertex_val = edge.target_vertex;
        int edge_unique_id = edge.id_edge;

        if (!edge_is_processed_flag[edge_unique_id])
        {
            edge_is_processed_flag[edge_unique_id] = true;
            construct_path(neighbor_vertex_val);
        }
    }
    resulting_path_nodes.push_back(current_vertex_val);
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int total_nodes, total_edges;
    cin >> total_nodes >> total_edges;
    adjacency_list_data.resize(total_nodes + 1);
    edge_is_processed_flag.resize(total_edges, false);

    for (int i = 0; i < total_edges; ++i)
    {
        int vertex_a, vertex_b;
        cin >> vertex_a >> vertex_b;
        adjacency_list_data[vertex_a].push_back({vertex_b, i});
        adjacency_list_data[vertex_b].push_back({vertex_a, i});
    }

    for (int v_idx = 1; v_idx <= total_nodes; ++v_idx)
    {
        if (adjacency_list_data[v_idx].size() % 2 != 0)
        {
            cout << "IMPOSSIBLE";
            return 0;
        }
    }

    vector<bool> visited_nodes_bfs(total_nodes + 1, false);
    queue<int> processing_queue;
    if (total_nodes > 0)
    { // Ensure there's at least one node to start BFS
        processing_queue.push(1);
        visited_nodes_bfs[1] = true;
    }

    while (!processing_queue.empty())
    {
        int current_q_vertex = processing_queue.front();
        processing_queue.pop();
        for (const auto &edge_item : adjacency_list_data[current_q_vertex])
        {
            int adjacent_v = edge_item.target_vertex;
            if (!visited_nodes_bfs[adjacent_v])
            {
                visited_nodes_bfs[adjacent_v] = true;
                processing_queue.push(adjacent_v);
            }
        }
    }

    for (int v_idx = 1; v_idx <= total_nodes; ++v_idx)
    {
        if (!adjacency_list_data[v_idx].empty() && !visited_nodes_bfs[v_idx])
        {
            cout << "IMPOSSIBLE";
            return 0;
        }
    }

    if (total_nodes > 0)
    { // Only start DFS if there are nodes
        construct_path(1);
    }
    else if (total_edges > 0)
    { // Edges but no nodes is impossible
        cout << "IMPOSSIBLE";
        return 0;
    }

    reverse(resulting_path_nodes.begin(), resulting_path_nodes.end());

    if (total_edges == 0)
    {
        if (total_nodes >= 1)
        {
            if (resulting_path_nodes.size() != 1 || resulting_path_nodes.front() != 1)
            {
                cout << "IMPOSSIBLE";
                return 0;
            }
        }
        else
        {                         // total_nodes == 0 && total_edges == 0
            cout << "IMPOSSIBLE"; // Or based on specific problem spec for N=0, M=0
            return 0;
        }
    }
    else
    { // total_edges > 0
        if (resulting_path_nodes.size() != total_edges + 1 ||
            resulting_path_nodes.front() != 1 ||
            resulting_path_nodes.back() != 1)
        {
            cout << "IMPOSSIBLE";
            return 0;
        }
    }

    for (size_t i = 0; i < resulting_path_nodes.size(); ++i)
    {
        cout << resulting_path_nodes[i] << (i == resulting_path_nodes.size() - 1 ? "" : " ");
    }

    return 0;
}