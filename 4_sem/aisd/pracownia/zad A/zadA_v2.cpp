#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 2005;
const int MAX_M = 2005;
char grid[MAX_N][MAX_M];
bool visited[2005][2005];
int down_shift = 6;
uint16_t templates[6] = {0b000000000000, 0b101100000000, 0b000000000000, 0b000000100110, 0b101100100110, 0b101100100110};

void bfs(int start_x, int start_y, int n, int m)
{
    queue<int> q;
    visited[start_x][start_y] = true;
    q.push((start_x << 11) | start_y);

    while (!q.empty())
    {
        int curr = q.front();
        q.pop();
        int y = curr & 2047;
        int x = curr >> 11;
        char curr_c = grid[x][y];
        uint16_t curr_temp = templates[curr_c - 'A'];
        if (y - 1 >= 0 && grid[x][y - 1] != 'A')
        {
            char lc = grid[x][y - 1];
            uint16_t left_template = templates[lc - 'A'];
            if (!visited[x][y - 1] && (left_template & (1 << (curr_c - 'A'))) != 0)
            {
                visited[x][y - 1] = true;
                q.push((x << 11) | (y - 1));
            }
        }
        if (x - 1 >= 0 && grid[x - 1][y] != 'A')
        {
            char uc = grid[x - 1][y];
            uint16_t up_template = templates[uc - 'A'];
            if (!visited[x - 1][y] && (up_template & (1 << (curr_c - 'A' + down_shift))) != 0)
            {
                visited[x - 1][y] = true;
                q.push(((x - 1) << 11) | y);
            }
        }
        if (y + 1 < m && grid[x][y + 1] != 'A')
        {
            char rc = grid[x][y + 1];
            if (!visited[x][y + 1] && (curr_temp & (1 << (rc - 'A'))) != 0)
            {
                visited[x][y + 1] = true;
                q.push((x << 11) | (y + 1));
            }
        }
        if (x + 1 < n && grid[x + 1][y] != 'A')
        {
            char dc = grid[x + 1][y];
            if (!visited[x + 1][y] && (curr_temp & (1 << (dc - 'A' + down_shift))) != 0)
            {
                visited[x + 1][y] = true;
                q.push(((x + 1) << 11) | y);
            }
        }
    }
}
int main()
{
    int n, m;

    int islands = 0;

    scanf("%d %d", &n, &m);
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;

    for (int i = 0; i < n; i++)
    {
        fgets(grid[i], MAX_M, stdin);
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (grid[i][j] != 'A' && !visited[i][j])
            {
                islands++;
                bfs(i, j, n, m);
            }
        }
    }
    cout << islands;
}