#include <bits/stdc++.h>
using namespace std;
struct node
{
    int min;
    int lazy;
};
int main()
{
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(0);
    int n, q;
    cin >> n >> q;
    vector<vector<int>> graph(n);
    for (int i = 0; i < n - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        u--;
        v--; // 0-indexing
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    vector<int> depth(n, 0);
    while (q--)
    {
        int u, v;
        cin >> u >> v;
    }
}