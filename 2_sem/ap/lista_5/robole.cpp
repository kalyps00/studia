#include <bits/stdc++.h>
using namespace std;
int solve(vector<vector<int>> &machines, vector<int> &dp, int n)
{
    dp[0] = 0;
    int maks = 1 << n;
    for (int mask = 0; mask < maks; mask++)
    {
        int k_pracownik = __builtin_popcount(mask);
        for (int j = 0; j < n; j++)
        {
            if (!(mask & (1 << j))) // if machine j is not occupied
            {
                int new_mask = mask | 1 << j; // adding machine j to mask
                dp[new_mask] = max(dp[new_mask], dp[mask] + machines[k_pracownik][j]);
            }
        }
    }
    return dp[maks - 1];
}
int main()
{
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(0);
    int n;
    cin >> n;
    vector<vector<int>> machines(n, vector<int>(n));
    vector<int> dp(1 << n, -1); // 2^n
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> machines[i][j];
        }
    }
    cout << solve(machines, dp, n);
}