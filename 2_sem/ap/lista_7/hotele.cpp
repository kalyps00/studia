#include <bits/stdc++.h>
using namespace std;
void update(vector<int> &tree, int node, int val)
{
    tree[node] = val;
    node /= 2;
    while (node > 0)
    {
        tree[node] = max(tree[node * 2], tree[node * 2 + 1]);
        node /= 2;
    }
}
int answer(vector<int> &tree, int bound_left, int bound_right, int node, int val)
{
    if (bound_left == bound_right)
    {
        update(tree, node, tree[node] - val);
        return bound_left + 1;
    }
    int mid = (bound_left + bound_right) / 2;
    if (tree[node * 2] >= val) // left
        return answer(tree, bound_left, mid, node * 2, val);
    else // right
        return answer(tree, mid + 1, bound_right, node * 2 + 1, val);
}
int main()
{
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(0);
    int n, q;
    cin >> n >> q;
    int start = 1;
    while (start <= n)
        start *= 2;
    vector<int> tree(2 * start, 0);
    for (int i = 0; i < n; i++)
    {
        int t;
        cin >> t;
        update(tree, start + i, t);
    }
    while (q--)
    {
        int group_size;
        cin >> group_size;
        if (group_size > tree[1])
        {
            cout << 0 << ' ';
            continue;
        }
        cout << answer(tree, 0, start - 1, 1, group_size) << ' ';
    }
}