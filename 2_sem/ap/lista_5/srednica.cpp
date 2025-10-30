#include <bits/stdc++.h>
using namespace std;
void find_diameter(vector<vector<int>> &tree, vector<pair<int, int>> &dp, int p = -1, int node = 0)
{
    dp[node].first = 0;
    dp[node].second = 0;
    int max1 = 0, max2 = 0;
    for (int child : tree[node])
    {
        if (child == p)
            continue;
        find_diameter(tree, dp, node, child);
        dp[node].first = max(dp[node].first, dp[child].first);

        int height = dp[child].second + 1;

        if (height > max1)
        {
            max2 = max1;
            max1 = height;
        }
        else if (height > max2)
        {
            max2 = height;
        }
        dp[node].first = max(dp[node].first, max1 + max2);
        dp[node].second = max1;
    }
}
int main()
{
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(0);
    int n;
    cin >> n;
    vector<vector<int>> tree(n);
    for (int i = 0; i < n - 1; i++)
    {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        tree[a].push_back(b);
        tree[b].push_back(a);
    }
    vector<pair<int, int>> dp(n, {0, 0});
    find_diameter(tree, dp);
    cout << dp[0].first << '\n';
}