#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;
void findAllPaths(vector<vector<int>> &graph, int n)
{
    int dp[n][1 << n];
    memset(dp, 0, sizeof dp);
    dp[0][1] = 1;
    for (int i = 2; i < (1 << n); i++)
    {
        if ((i & (1)) == 0)
            continue;

        if (i & (1 << (n - 1)) && (i != ((1 << n) - 1)))
            continue;

        for (int end = 0; end < n; end++)
        {
            if (!(i & (1 << end)))
                continue;

            int temp = i - (1 << end);
            for (auto sd : graph[end])
            {
                if (!(i & (1 << sd)))
                    continue;
                else
                {
                    dp[end][i] = ((dp[end][i] % MOD) + (dp[sd][temp] % MOD)) % MOD;
                }
            }
        }
    }
    cout << dp[n - 1][(1 << n) - 1];
}
int main()
{
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(0);
    int n, m;
    cin >> n >> m;
    vector<vector<int>> graph(n);

    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        graph[b].push_back(a);
    }
    findAllPaths(graph, n);
}