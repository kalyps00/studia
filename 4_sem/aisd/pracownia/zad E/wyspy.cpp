#include <bits/stdc++.h>

using namespace std;

struct Node
{
    int h;
    int idx;
};

struct Query
{
    int t;
    int idx;
};

int find(int x, vector<int> &parent)
{
    while (parent[x] != x)
    {
        parent[x] = parent[parent[x]];
        x = parent[x];
    }
    return x;
}

bool unon(int a, int b, vector<int> &parent, vector<int> &sizes)
{
    a = find(a, parent);
    b = find(b, parent);
    if (a == b)
    {
        return false;
    }
    if (sizes[a] < sizes[b])
    {
        swap(a, b);
    }
    parent[b] = a;
    sizes[a] += sizes[b];
    return true;
}

void try_union(int a, int b, vector<unsigned char> &active, vector<int> &parent,
               vector<int> &sizes, int &components)
{
    if (active[b] && unon(a, b, parent, sizes))
    {
        components--;
    }
}

bool cmp_node(const Node &a, const Node &b)
{
    return a.h > b.h;
}

bool cmp_query(const Query &a, const Query &b)
{
    return a.t > b.t;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;

    const int total = n * m;
    vector<Node> cells;
    cells.reserve(total);

    for (int r = 0; r < n; r++)
    {
        for (int c = 0; c < m; c++)
        {
            int h;
            cin >> h;
            cells.push_back({h, r * m + c});
        }
    }

    int T;
    cin >> T;
    vector<Query> queries(T);
    for (int i = 0; i < T; i++)
    {
        int t;
        cin >> t;
        queries[i] = {t, i};
    }

    sort(cells.begin(), cells.end(), cmp_node);

    vector<Query> order = queries;
    sort(order.begin(), order.end(), cmp_query);

    vector<int> parent(total, -1), sizes(total, 1), answers(T, 0);
    vector<unsigned char> active(total, 0);
    int components = 0;
    size_t ptr = 0;

    for (auto &q : order)
    {
        while (ptr < cells.size() && cells[ptr].h > q.t)
        {
            int idx = cells[ptr].idx;
            active[idx] = 1;
            parent[idx] = idx;
            sizes[idx] = 1;
            components++;

            int r = idx / m;
            int c = idx % m;

            if (r > 0)
            {
                try_union(idx, idx - m, active, parent, sizes, components);
            }
            if (r + 1 < n)
            {
                try_union(idx, idx + m, active, parent, sizes, components);
            }
            if (c > 0)
            {
                try_union(idx, idx - 1, active, parent, sizes, components);
            }
            if (c + 1 < m)
            {
                try_union(idx, idx + 1, active, parent, sizes, components);
            }

            ptr++;
        }
        answers[q.idx] = components;
    }

    for (int i = 0; i < T; i++)
    {
        if (i)
        {
            cout << ' ';
        }
        cout << answers[i];
    }
    cout << '\n';

    return 0;
}
