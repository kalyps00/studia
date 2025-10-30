#include <bits/stdc++.h>
using namespace std;
int solve(vector<vector<int>> &tree, vector<vector<int>> &dp, int parent = -1, int node = 0)
{
    int sum = 0;
    // without parent
    for (auto n : tree[node])
    {
        if (n == parent)
            continue;
        solve(tree, dp, node, n);
        sum += max(dp[n][0], dp[n][1]);
    }
    dp[node][0] = sum;
    // with parent
    for (auto n : tree[node])
    {
        if (n == parent)
            continue;
        // 1 new + value when not matched + rest of the child
        int possible_best = 1 + dp[n][0] + (sum - max(dp[n][0], dp[n][1]));
        dp[node][1] = max(dp[node][1], possible_best);
    }
    // ans
    return max(dp[node][0], dp[node][1]);
}
int main()
{
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(0);
    int n;
    cin >> n;
    vector<vector<int>> tree(n);
    vector<vector<int>> dp(n, vector<int>(2, 0));

    for (int i = 0; i < n - 1; i++)
    {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        tree[a].push_back(b);
        tree[b].push_back(a);
    }
    cout << solve(tree, dp);
}