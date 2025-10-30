#include <bits/stdc++.h>
using namespace std;
int s;
struct node
{
    int size;
    int val = -1;
};
void update(vector<node> &tree, int node, struct node val)
{
    tree[node] = val;
    node /= 2;
    while (node > 0)
    {
        tree[node].size = tree[node * 2].size + tree[node * 2 + 1].size;
        node /= 2;
    }
}
int remove(vector<node> &tree, int bound_left, int bound_right, int node, int to_remove)
{
    tree[node].size--;
    if (bound_left == bound_right)
    {
        int res = tree[node].val;
        tree[node] = {0, -1};
        return res;
    }

    int mid = (bound_left + bound_right) / 2;
    int left_size = tree[2 * node].size;

    if (to_remove < left_size)
    {
        return remove(tree, bound_left, mid, 2 * node, to_remove);
    }
    else
    {
        return remove(tree, mid + 1, bound_right, 2 * node + 1, to_remove - left_size);
    }
}

int main()
{
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(0);
    int n;
    cin >> n;
    int start = 1;
    while (start <= n)
        start *= 2;
    s = start;
    vector<node> tree(2 * start, {0, 0});
    for (int i = 0; i < n; i++)
    {
        int t;
        cin >> t;
        update(tree, start + i, {1, t});
    }
    while (n--)
    {
        int pos;
        cin >> pos;
        pos--;
        cout << remove(tree, 0, start - 1, 1, pos) << ' ';
    }
}