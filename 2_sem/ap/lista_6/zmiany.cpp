#include <bits/stdc++.h>
using namespace std;
long long answer(vector<long long> &tree, int i)
{
    long long result = 0;
    while (i > 0)
    {
        result += tree[i];
        i /= 2;
    }
    return result;
}
void update(vector<long long> &tree, int node, int bound_left, int bound_right, int range_left, int range_right, int val)
{
    if (bound_left == range_left && bound_right == range_right)
    {
        tree[node] += val;
        return;
    }
    int mid = (bound_left + bound_right) / 2;
    if (range_right <= mid) // left
    {
        update(tree, 2 * node, bound_left, mid, range_left, range_right, val);
    }
    else if (range_left > mid) // right
    {
        update(tree, 2 * node + 1, mid + 1, bound_right, range_left, range_right, val);
    }
    else // split
    {
        update(tree, 2 * node, bound_left, mid, range_left, mid, val);
        update(tree, 2 * node + 1, mid + 1, bound_right, mid + 1, range_right, val);
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
    vector<long long> tree(2 * start, 0);
    for (int i = 0; i < n; i++)
    {
        cin >> tree[i + start];
    }
    while (q--)
    {
        int type;
        cin >> type;
        if (type == 1)
        {
            int pocz, koniec, val;
            cin >> pocz >> koniec >> val;
            update(tree, 1, 0, start - 1, pocz - 1, koniec - 1, val);
        }
        else
        {
            int k;
            cin >> k;
            cout << answer(tree, k - 1 + start) << "\n";
        }
    }
}