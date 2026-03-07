#include <cstdio>
#include <cstdint>
char grid[2007][2007];
uint32_t queue[2007 * 2007], head, tail;
uint32_t masks['F' + 10];

int main()
{
    masks['B'] = 0b1100;
    masks['C'] = 0b1001;
    masks['D'] = 0b0011;
    masks['E'] = 0b0110;
    masks['F'] = 0b1111;
    int n, m, towns = 0;
    scanf("%d %d\n", &n, &m);
    for (int i = 1; i < n + 1; i++)
    {
        fgets(grid[i] + 1, m + 2, stdin);
    }
    for (int i = 1; i < n + 1; i++)
    {
        for (int j = 1; j < m + 1; j++)
        {
            if (masks[grid[i][j]])
            {
                towns++;
                head = tail = 0;
                queue[tail++] = (i << 16) | j;
                while (head < tail)
                {
                    int x_y = queue[head++];
                    int x = x_y >> 16, y = x_y & 0xFFFF;
                    uint32_t curr_mask = masks[grid[x][y]];
                    if (curr_mask == 0)
                        continue;

                    grid[x][y] = 0;

                    // UP
                    if ((curr_mask & 0b0001) && (masks[grid[x - 1][y]] & 0b0100))
                        queue[tail++] = ((x - 1) << 16) | y;
                    // RIGHT
                    if ((curr_mask & 0b0010) && (masks[grid[x][y + 1]] & 0b1000))
                        queue[tail++] = (x << 16) | (y + 1);
                    // DOWN
                    if ((curr_mask & 0b0100) && (masks[grid[x + 1][y]] & 0b0001))
                        queue[tail++] = ((x + 1) << 16) | y;
                    // LEFT
                    if ((curr_mask & 0b1000) && (masks[grid[x][y - 1]] & 0b0010))
                        queue[tail++] = (x << 16) | (y - 1);
                }
            }
        }
    }
    printf("%d\n", towns);
}