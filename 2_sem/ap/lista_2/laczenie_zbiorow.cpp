#include <bits/stdc++.h>
using namespace std;

void merge(unordered_set<int> &set_big, unordered_set<int> &set_small)
{
    if (set_big.size() < set_small.size())
        swap(set_big, set_small);
    set_big.insert(set_small.begin(), set_big.end());
}
void dfs(int start, int parent, vector<vector<int>> &tree, vector<int> &kolor_wierz, vector<unordered_set<int>> &kolory, vector<int> &ans)
{
    int big_size = -1, bignode = -1;
    for (int node : tree[start])
    {
        if (node == parent)
            continue;

        dfs(node, start, tree, kolor_wierz, kolory, ans);
        if (kolory[node].size() > big_size)
        {
            big_size = kolory[node].size();
            bignode = node;
        }
        // merge(kolory[start], temp);
    }
    if (big_size != -1)
        swap(kolory[start], kolory[bignode]);

    for (auto node : tree[start])
    {
        if (node == bignode || node == parent)
            continue;
        merge(kolory[start], kolory[node]);
    }
    kolory[start].insert(kolor_wierz[start]);
    ans[start] = kolory[start].size();
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    vector<vector<int>> tree(n);
    vector<int> kolor_wierz(n);
    vector<unordered_set<int>> kolory(n);
    vector<int> ans(n);

    for (int i = 0; i < n; i++)
    {
        cin >> kolor_wierz[i];
        kolory[i].insert(kolor_wierz[i]);
    }

    for (int i = 0; i < n - 1; i++)
    {
        int a, b;
        cin >> a >> b;
        a--, b--;
        tree[a].push_back(b);
        tree[b].push_back(a);
    }

    dfs(0, -1, tree, kolor_wierz, kolory, ans);

    for (int x : ans)
    {
        cout << x << ' ';
    }
    cout << '\n';

    return 0;
}
