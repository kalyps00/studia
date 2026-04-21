#include <bits/stdc++.h>
using namespace std;

int down_shift = 6;
uint16_t templates[6] = {0b000000000000, 0b101100000000, 0b000000000000, 0b000000100110, 0b101100100110, 0b101100100110};

void bfs(int start_x, int start_y, int n, int m, vector<string> &grid, vector<bool> &visited)
{
    queue<int> q;
    visited[start_x * m + start_y] = true;
    q.push(start_x * m + start_y);

    while (!q.empty())
    {
        int curr = q.front();
        q.pop();
        int y = curr % m;
        int x = curr / m;
        char curr_c = grid[x][y];
        uint16_t curr_temp = templates[curr_c - 'A'];
        if (y - 1 >= 0 && grid[x][y - 1] != 'A')
        {
            char lc = grid[x][y - 1];
            uint16_t left_template = templates[lc - 'A'];
            int left_node_id = (x)*m + y - 1;
            if (!visited[left_node_id] && (left_template & (1 << (curr_c - 'A'))) != 0)
            {
                visited[left_node_id] = true;
                q.push(left_node_id);
            }
        }
        if (x - 1 >= 0 && grid[x - 1][y] != 'A')
        {
            char uc = grid[x - 1][y];
            uint16_t up_template = templates[uc - 'A'];
            int up_node_id = ((x - 1) * m + y);
            if (!visited[up_node_id] && (up_template & (1 << (curr_c - 'A' + down_shift))) != 0)
            {
                visited[up_node_id] = true;
                q.push(up_node_id);
            }
        }
        if (y + 1 < m && grid[x][y + 1] != 'A')
        {
            char rc = grid[x][y + 1];
            int right_node_id = (x)*m + y + 1;
            if (!visited[right_node_id] && (curr_temp & (1 << (rc - 'A'))) != 0)
            {
                visited[right_node_id] = true;
                q.push(right_node_id);
            }
        }
        if (x + 1 < n && grid[x + 1][y] != 'A')
        {
            char dc = grid[x + 1][y];
            int down_node_id = (x + 1) * m + y;
            if (!visited[down_node_id] && (curr_temp & (1 << (dc - 'A' + down_shift))) != 0)
            {
                visited[down_node_id] = true;
                q.push(down_node_id);
            }
        }
    }
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, m;
    vector<string> grid;
    int islands = 0;
    vector<bool> visited;
    cin >> n >> m;
    grid.resize(n);
    visited.resize(n * m);
    for (int i = 0; i < n; i++)
    {
        cin >> grid[i];
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (grid[i][j] != 'A' && !visited[i * m + j])
            {
                islands++;
                bfs(i, j, n, m, grid, visited);
            }
        }
    }
    cout << islands;
}