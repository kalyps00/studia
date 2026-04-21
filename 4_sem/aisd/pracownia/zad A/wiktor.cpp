// Wiktor Lewicki 353554
#include <bits/stdc++.h>
using namespace std;

const int N = 2e3 + 5;
uint8_t in[N][N];
bitset<N * N> rep;

struct que
{
    pair<uint16_t, uint16_t> order[N * N];
    uint32_t pos, last;
    que() : pos(0), last(0) {}

    inline uint8_t empty()
    {
        return pos >= last;
    }
    inline pair<uint16_t, uint16_t> get_and_pop()
    {
        ++pos;
        return order[pos - 1];
    }
    inline void insert(pair<int, int> a)
    {
        order[last++] = a;
    }
};
que order;
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    uint32_t n, m, ans = 0;
    cin >> n >> m;
    for (uint32_t i = 0; i <= n + 1; ++i)
    {
        in[i][0] = in[i][m + 1] = 'A';
    }
    for (uint32_t j = 0; j <= m + 1; ++j)
    {
        in[0][j] = in[n + 1][j] = 'A';
    }
    for (uint32_t i = 1; i <= n; ++i)
    {
        string s;
        cin >> s;
        for (uint32_t j = 0; j < m; ++j)
        {
            in[i][j + 1] = s[j];
        }
        in[i][m + 1] = 'A';
    }
    for (uint32_t i = 1; i <= n; ++i)
    {
        for (uint32_t j = 1; j <= m; ++j)
        {
            if (rep[i * n + j] || in[i][j] == 'A')
                continue;
            ++ans;
            order.insert({i, j});
            rep[i * n + j] = true;
            while (!order.empty())
            {
                auto [x1, y1] = order.get_and_pop();
                uint32_t x = x1, y = y1;
                if ((in[x][y] == 'B' || in[x][y] == 'C' || in[x][y] == 'F') && in[x][y - 1] >= 'D' && !rep[x * n + y - 1])
                {
                    rep[x * n + y - 1] = true;
                    order.insert({x, y - 1});
                }
                if ((in[x][y + 1] == 'B' || in[x][y + 1] == 'C' || in[x][y + 1] == 'F') && in[x][y] >= 'D' && !rep[x * n + y + 1])
                {
                    rep[x * n + y + 1] = true;
                    order.insert({x, y + 1});
                }
                if ((in[x][y] == 'C' || in[x][y] == 'D' || in[x][y] == 'F') && (in[x - 1][y] == 'B' || in[x - 1][y] == 'E' || in[x - 1][y] == 'F') && !rep[(x - 1) * n + y])
                {
                    rep[(x - 1) * n + y] = true;
                    order.insert({x - 1, y});
                }
                if ((in[x + 1][y] == 'C' || in[x + 1][y] == 'D' || in[x + 1][y] == 'F') && (in[x][y] == 'B' || in[x][y] == 'E' || in[x][y] == 'F') && !rep[(x + 1) * n + y])
                {
                    rep[(x + 1) * n + y] = true;
                    order.insert({x + 1, y});
                }
            }
        }
    }
    cout << ans << "\n";
    return 0;
}
