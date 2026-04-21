#include <cstdio>
#include <cstdint>

char g[2005][2005];
int q[4000005], h, t, R, C, towns;
uint8_t m[256];

int main()
{
    m['B'] = 12;
    m['C'] = 9;
    m['D'] = 3;
    m['E'] = 6;
    m['F'] = 15;
    if (scanf("%d %d\n", &R, &C) < 2)
        return 0;
    for (int i = 1; i <= R; i++)
        fgets(g[i] + 1, 2005, stdin);

    for (int i = 1; i <= R; i++)
    {
        for (int j = 1; j <= C; j++)
        {
            if (m[(uint8_t)g[i][j]])
            {
                towns++;
                q[t++] = (i << 12) | j;
                while (h < t)
                {
                    int c = q[h++], x = c >> 12, y = c & 4095;
                    uint8_t cur = m[(uint8_t)g[x][y]];
                    g[x][y] = 0; // Mark visited

                    if ((cur & 1) && (m[(uint8_t)g[x - 1][y]] & 4))
                    {
                        q[t++] = (x - 1) << 12 | y;
                        g[x - 1][y] = 'A';
                    }
                    if ((cur & 2) && (m[(uint8_t)g[x][y + 1]] & 8))
                    {
                        q[t++] = x << 12 | (y + 1);
                        g[x][y + 1] = 'A';
                    }
                    if ((cur & 4) && (m[(uint8_t)g[x + 1][y]] & 1))
                    {
                        q[t++] = (x + 1) << 12 | y;
                        g[x + 1][y] = 'A';
                    }
                    if ((cur & 8) && (m[(uint8_t)g[x][y - 1]] & 2))
                    {
                        q[t++] = x << 12 | (y - 1);
                        g[x][y - 1] = 'A';
                    }
                }
            }
        }
    }
    printf("%d\n", towns);
    return 0;
}