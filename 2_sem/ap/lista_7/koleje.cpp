#include <bits/stdc++.h>
using namespace std;
struct node
{
    int min;
    int lazy;
};
void push(vector<node> &tree, int node)
{
    if (tree[node].lazy != 0)
    {
        tree[node].min -= tree[node].lazy;
        if (node * 2 < tree.size())
        {
            tree[node * 2].lazy += tree[node].lazy;
            tree[node * 2 + 1].lazy += tree[node].lazy;
        }
        tree[node].lazy = 0;
    }
}

void update(vector<node> &tree, int bound_left, int bound_right, int range_left, int range_right, int node, int seats)
{

    if (range_right < bound_left || bound_right < range_left)
    {
        push(tree, node);
        return;
    }
    if (range_left <= bound_left && bound_right <= range_right)
    {
        tree[node].lazy += seats;
        push(tree, node);
        return;
    }
    push(tree, node);
    int mid = (bound_left + bound_right) / 2;
    update(tree, bound_left, mid,
           range_left, range_right,
           node * 2, seats);
    update(tree, mid + 1, bound_right,
           range_left, range_right,
           node * 2 + 1, seats);

    tree[node].min = min(tree[node * 2].min, tree[node * 2 + 1].min);
}
int find_min(vector<node> &tree, int bound_left, int bound_right, int range_left, int range_right, int node, int seats)
{
    push(tree, node);
    if (range_right < bound_left || bound_right < range_left) // rozlaczne
        return INT_MAX;
    if (range_left <= bound_left && bound_right <= range_right) // pokrywa sie
        return tree[node].min;
    int mid = (bound_left + bound_right) / 2;
    return min(
        find_min(tree, bound_left, mid,
                 range_left, range_right,
                 node * 2, seats),
        find_min(tree, mid + 1, bound_right,
                 range_left, range_right,
                 node * 2 + 1, seats));
}

int answer(vector<node> &tree, int bound_left, int bound_right, int range_left, int range_right, int node, int seats)
{
    int min_seats = find_min(tree, bound_left, bound_right, range_left, range_right, node, seats);
    if (min_seats < seats)
        return 0;
    update(tree, bound_left, bound_right, range_left, range_right, node, seats);
    return 1;
}

int main()
{
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(0);
    int n, m, q;
    cin >> n >> m >> q;
    int start = 1;
    while (start <= n)
        start <<= 1;
    vector<node> tree(2 * start, {m, 0});

    while (q--)
    {
        int start_range, end_range, seats;
        cin >> start_range >> end_range >> seats;
        if (answer(tree, 0, start - 1, start_range - 1, end_range - 2, 1, seats))
            cout << "T" << '\n';
        else
            cout << "N" << '\n';
    }
}