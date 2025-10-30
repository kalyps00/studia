#include <bits/stdc++.h>
using namespace std;

struct node
{
    long long sum;
    long long lazy_add;
    long long lazy_set; // -1 means “no pending set”
};

void build(vector<node> &tree, int idx, int val)
{
    tree[idx].sum = val;
    for (idx /= 2; idx > 0; idx /= 2)
        tree[idx].sum = tree[2 * idx].sum + tree[2 * idx + 1].sum;
}

void push(vector<node> &tree, int node, int bound_left, int bound_right)
{
    int mid = (bound_left + bound_right) / 2;
    int left = node * 2;
    int right = node * 2 + 1;

    // 1) Propagate pending SET
    if (tree[node].lazy_set != -1)
    {
        long long v = tree[node].lazy_set;
        // update this node’s sum
        tree[node].sum = (bound_right - bound_left + 1) * v;
        // if not leaf, propagate to children
        if (right < (int)tree.size())
        {
            // left child covers [bound_left..mid]
            tree[left].lazy_set = v;
            tree[left].lazy_add = 0;
            tree[left].sum = (mid - bound_left + 1) * v;
            // right child covers [mid+1..bound_right]
            tree[right].lazy_set = v;
            tree[right].lazy_add = 0;
            tree[right].sum = (bound_right - mid) * v;
        }
        tree[node].lazy_set = -1;
        // leave lazy_add as is (it will be applied below if nonzero)
    }

    // 2) Propagate pending ADD
    if (tree[node].lazy_add != 0)
    {
        long long v = tree[node].lazy_add;
        // update this node’s sum
        tree[node].sum += (bound_right - bound_left + 1) * v;
        // if not leaf, propagate to children
        if (right < (int)tree.size())
        {
            // left child
            tree[left].lazy_add += v;
            // right child
            tree[right].lazy_add += v;
        }
        tree[node].lazy_add = 0;
    }
}

void range_add(vector<node> &tree,
               int bound_left, int bound_right,
               int range_left, int range_right,
               int node, long long val)
{
    push(tree, node, bound_left, bound_right);
    if (bound_left > range_right || bound_right < range_left)
        return;
    if (bound_left >= range_left && bound_right <= range_right)
    {
        tree[node].lazy_add += val;
        push(tree, node, bound_left, bound_right);
        return;
    }
    int mid = (bound_left + bound_right) / 2;
    range_add(tree, bound_left, mid, range_left, range_right, node * 2, val);
    range_add(tree, mid + 1, bound_right, range_left, range_right, node * 2 + 1, val);
    tree[node].sum = tree[node * 2].sum + tree[node * 2 + 1].sum;
}

void range_set(vector<node> &tree,
               int bound_left, int bound_right,
               int range_left, int range_right,
               int node, long long val)
{
    push(tree, node, bound_left, bound_right);
    if (bound_left > range_right || bound_right < range_left)
        return;
    if (bound_left >= range_left && bound_right <= range_right)
    {
        tree[node].lazy_set = val;
        tree[node].lazy_add = 0;
        push(tree, node, bound_left, bound_right);
        return;
    }
    int mid = (bound_left + bound_right) / 2;
    range_set(tree, bound_left, mid, range_left, range_right, node * 2, val);
    range_set(tree, mid + 1, bound_right, range_left, range_right, node * 2 + 1, val);
    tree[node].sum = tree[node * 2].sum + tree[node * 2 + 1].sum;
}

long long range_sum(vector<node> &tree,
                    int bound_left, int bound_right,
                    int range_left, int range_right,
                    int node)
{
    push(tree, node, bound_left, bound_right);
    if (bound_left >= range_left && bound_right <= range_right)
        return tree[node].sum;
    int mid = (bound_left + bound_right) / 2;
    long long ans = 0;
    if (range_left <= mid)
        ans += range_sum(tree, bound_left, mid, range_left, range_right, node * 2);
    if (range_right > mid)
        ans += range_sum(tree, mid + 1, bound_right, range_left, range_right, node * 2 + 1);
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    int start = 1;
    while (start < n)
        start <<= 1;

    vector<node> tree(2 * start);
    // init lazy_set = -1
    for (int i = 1; i < 2 * start; i++)
    {
        tree[i].lazy_set = -1;
        tree[i].lazy_add = 0;
        tree[i].sum = 0;
    }

    // read initial array
    for (int i = 0, a; i < n; i++)
    {
        cin >> a;
        build(tree, start + i, a);
    }

    // process queries
    while (q--)
    {
        int type, x, y;
        cin >> type >> x >> y;
        if (type == 1)
        {
            long long v;
            cin >> v;
            range_add(tree, 0, start - 1, x - 1, y - 1, 1, v);
        }
        else if (type == 2)
        {
            long long v;
            cin >> v;
            range_set(tree, 0, start - 1, x - 1, y - 1, 1, v);
        }
        else
        {
            cout << range_sum(tree, 0, start - 1, x - 1, y - 1, 1) << "\n";
        }
    }

    return 0;
}
