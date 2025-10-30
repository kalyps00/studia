#include <bits/stdc++.h>
using namespace std;

const int MAXN = 60000;
int M;
int tree[4 * (MAXN + 5)];
int lazy[4 * (MAXN + 5)];

void build(int node, int start, int end)
{
    lazy[node] = 0;
    if (start == end)
    {
        tree[node] = M;
    }
    else
    {
        int mid = (start + end) / 2;
        build(2 * node, start, mid);
        build(2 * node + 1, mid + 1, end);
        tree[node] = min(tree[2 * node], tree[2 * node + 1]);
    }
}

void push(int node, int start, int end)
{
    if (lazy[node] != 0)
    {
        tree[node] -= lazy[node];
        if (start != end)
        {
            lazy[2 * node] += lazy[node];
            lazy[2 * node + 1] += lazy[node];
        }
        lazy[node] = 0;
    }
}

int query(int node, int start, int end, int l, int r)
{
    push(node, start, end);
    if (r < start || end < l)
        return INT_MAX;
    if (l <= start && end <= r)
        return tree[node];
    int mid = (start + end) / 2;
    return min(query(2 * node, start, mid, l, r), query(2 * node + 1, mid + 1, end, l, r));
}

void update(int node, int start, int end, int l, int r, int val)
{
    push(node, start, end);
    if (r < start || end < l)
        return;
    if (l <= start && end <= r)
    {
        lazy[node] += val;
        push(node, start, end);
        return;
    }
    int mid = (start + end) >> 1;
    update(2 * node, start, mid, l, r, val);
    update(2 * node + 1, mid + 1, end, l, r, val);
    tree[node] = min(tree[2 * node], tree[2 * node + 1]);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, Q;
    cin >> N >> M >> Q;

    if (N > 1)
        build(1, 1, N - 1);

    for (int i = 0; i < Q; i++)
    {
        int P, K, L;
        cin >> P >> K >> L;
        int l = P, r = K - 1;

        if (l > r || N == 1)
        {
            cout << "N\n";
            continue;
        }

        int curr_min = query(1, 1, N - 1, l, r);
        if (curr_min >= L)
        {
            cout << "T\n";
            update(1, 1, N - 1, l, r, L);
        }
        else
        {
            cout << "N\n";
        }
    }
    return 0;
}