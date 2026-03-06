#include <cstdio>
#include <cstdint>
#include <queue>
#include <iostream>
using namespace std;
char grid[2007][2007];
uint8_t masks[100];
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    masks['B'] = 0b1100;
    masks['C'] = 0b1001;
    masks['D'] = 0b0011;
    masks['E'] = 0b0110;
    masks['F'] = 0b1111;
    int n, m;
    cin >> n >> m;
    for (int i = 1; i < n + 1; i++)
    {
        for (int j = 1; j < m + 1; j++)
        {
            cin >> grid[i][j];
        }
    }
    int towns = 0;
    queue<int> q;

    for (int i = 1; i < n + 1; i++)
    {
        for (int j = 1; j < m + 1; j++)
        {
            if (masks[(uint8_t)grid[i][j]] > 0)
            {
                towns++;
                q.push(i << 16 | j);

                while (!q.empty())
                {
                    int x_y = q.front();
                    q.pop();
                    int x = x_y >> 16;
                    int y = x_y & 0xFFFF;

                    uint8_t curr_mask = masks[(uint8_t)grid[x][y]];
                    if (curr_mask == 0)
                        continue;

                    grid[x][y] = 0;

                    // UP
                    if ((curr_mask & 1) && (masks[(uint8_t)grid[x - 1][y]] & 0b0100))
                        q.push((x - 1) << 16 | y);

                    // RIGHT
                    if ((curr_mask & 2) && (masks[(uint8_t)grid[x][y + 1]] & 0b1000))
                        q.push(x << 16 | (y + 1));

                    // DOWN
                    if ((curr_mask & 4) && (masks[(uint8_t)grid[x + 1][y]] & 0b0001))
                        q.push((x + 1) << 16 | y);

                    // LEFT
                    if ((curr_mask & 8) && (masks[(uint8_t)grid[x][y - 1]] & 0b0010))
                        q.push(x << 16 | (y - 1));
                }
            }
        }
    }
    cout << towns;
}