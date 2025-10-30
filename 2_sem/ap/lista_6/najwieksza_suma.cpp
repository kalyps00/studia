#include <bits/stdc++.h>
using namespace std;
struct Node
{
    long long sum;
    long long max_prefix;
    long long max_suffix;
    long long max_subarray;
};

void update(vector<Node> &tree, int node, long long val)
{
    tree[node] = {val, max(val, 0LL), max(val, 0LL), max(val, 0LL)};
    node /= 2;
    while (node > 0)
    {
        Node left = tree[node * 2];
        Node right = tree[node * 2 + 1];
        tree[node].sum = left.sum + right.sum;
        tree[node].max_prefix = max(left.max_prefix, left.sum + right.max_prefix);
        tree[node].max_suffix = max(right.max_suffix, right.sum + left.max_suffix);
        tree[node].max_subarray = max({left.max_subarray, right.max_subarray, left.max_suffix + right.max_prefix});
        node /= 2;
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
    vector<Node> tree(2 * start, {0, 0, 0, 0});
    for (int i = 0; i < n; i++)
    {
        int a;
        cin >> a;
        update(tree, start + i, a);
    }
    while (q--)
    {
        int k, x;
        cin >> k >> x;
        update(tree, start + k - 1, x);
        cout << tree[1].max_subarray << "\n";
    }
}