#include <iostream>
#include <vector>
using namespace std;
int dfs(int node, const vector<vector<int>> &g, vector<int> &ans)
{
    int val = 0;
    for (auto child : g[node])
    {
        val += dfs(child, g, ans) + 1;
    }
    ans[node] = val;
    return val;
}
int main()
{
    int n;
    cin >> n;
    vector<vector<int>> g(n);

    for (int i = 1; i < n; i++)
    {
        int a;
        cin >> a;
        g[a - 1].push_back(i);
    }
    vector<int> ans(n, 0);
    dfs(0, g, ans);
    for (auto x : ans)
    {
        cout << x << " ";
    }
}