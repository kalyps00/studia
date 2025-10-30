#include <bits/stdc++.h>
using namespace std;
struct Node
{
    long long sum;
    long long max_prefix;
};
void update(vector<Node> &tree, int node, long long val)
{
    tree[node].sum = val;
    tree[node].max_prefix = max(val, 0LL);
    node /= 2;
    while (node > 0)
    {
        Node left = tree[node * 2];
        Node right = tree[node * 2 + 1];
        tree[node].sum = left.sum + right.sum;
        tree[node].max_prefix = max(left.max_prefix, left.sum + right.max_prefix);
        node /= 2;
    }
}
Node answer(vector<Node> &tree, int bound_left, int bound_right, int range_left, int range_right, int node)
{
    if (bound_left == range_left && bound_right == range_right)
        return tree[node];
    int mid = (bound_left + bound_right) / 2;
    if (range_right <= mid) // left
        return answer(tree, bound_left, mid, range_left, range_right, node * 2);
    else if (range_left > mid) // right
        return answer(tree, mid + 1, bound_right, range_left, range_right, node * 2 + 1);
    else
    { // split
        Node left = answer(tree, bound_left, mid, range_left, mid, node * 2);
        Node right = answer(tree, mid + 1, bound_right, mid + 1, range_right, node * 2 + 1);
        return {left.sum + right.sum, max(left.max_prefix, left.sum + right.max_prefix)};
    }
}
int main()
{
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(0);
    int n, q;
    cin >> n >> q;
    int start = 1;
    while (start < n)
        start *= 2;
    vector<Node> tree(2 * start, {0, 0});
    for (int i = 0; i < n; i++)
    {
        int a;
        cin >> a;
        update(tree, start + i, a);
    }
    while (q--)
    {
        int type;
        cin >> type;
        if (type == 1)
        {
            int k, v;
            cin >> k >> v;
            update(tree, start + k - 1, v);
        }
        else
        {
            int x, y;
            cin >> x >> y;
            cout << answer(tree, 0, start - 1, x - 1, y - 1, 1).max_prefix << '\n';
        }
    }
}