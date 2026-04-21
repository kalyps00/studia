#include <bits/stdc++.h>
using namespace std;
int dp[2][1000007];

int main()
{
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(0);
    int n, max_diff = 0;
    cin >> n;
    for (int i = 0; i < 1000007; i++)
        dp[0][i] = dp[1][i] = -1;
    dp[0][0] = 0; // both towers not built so diff is 0
    for (int i = 1; i < n + 1; i++)
    {
        int idx = i % 2;
        int block;
        cin >> block;
        for (int j = 0; j < max_diff + block; j++)
        {
            dp[idx][j] = -1;
        }

        for (int diff = 0; diff <= max_diff; diff++)
        {
            if (dp[1 - idx][diff] != -1)
            {
                // we dont take
                dp[idx][diff] = max(dp[idx][diff], dp[1 - idx][diff]);
                // to higher tower
                dp[idx][diff + block] = max(dp[idx][diff + block], dp[1 - idx][diff] + block);
                // to lower tower
                if (block <= diff)
                    dp[idx][diff - block] = max(dp[idx][diff - block], dp[1 - idx][diff]);
                else
                    dp[idx][block - diff] = max(dp[idx][block - diff], dp[1 - idx][diff] - diff + block);
            }
        }
        max_diff += block;
    }
    if (dp[n % 2][0] > 0)
    {
        cout << "TAK\n";
        cout << dp[n % 2][0];
    }
    else
    {
        cout << "NIE\n";
        for (int i = 1; i < 1000007; i++)
        {
            if (dp[n % 2][i] != -1 && dp[n % 2][i] > i)
            {
                cout << i;
                break;
            }
        }
    }
}