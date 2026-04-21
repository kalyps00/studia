#include <bits/stdc++.h>
using namespace std;

#define ll long long
struct Pair
{
    int to;
    int cost;

    Pair(int x, int ct)
    {
        to = x;
        cost = ct;
    }
};
struct GreaterPair
{
    bool operator()(const Pair &a, const Pair &b) const
    {
        if (a.cost != b.cost)
            return a.cost > b.cost;
        return a.to > b.to;
    }
};
class Heap
{
private:
    vector<Pair> array;
    int size;

    void heapify(int i);
    bool lessPair(const Pair &a, const Pair &b) const;
    int findIndex(const Pair &p) const;

public:
    Heap() : size(0) {}
    Pair extractMin();
    bool empty();
    void pop();
    int insert(Pair);
};

bool Heap::lessPair(const Pair &a, const Pair &b) const
{
    if (a.cost != b.cost)
        return a.cost < b.cost;
    return a.to < b.to;
}

int Heap::findIndex(const Pair &p) const
{
    for (int idx = 0; idx < size; idx++)
    {
        if (array[idx].to == p.to && array[idx].cost == p.cost)
            return idx;
    }
    return -1;
}

void Heap::heapify(int i)
{
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < size && lessPair(array[left], array[smallest]))
        smallest = left;

    if (right < size && lessPair(array[right], array[smallest]))
        smallest = right;

    if (smallest != i)
    {
        swap(array[i], array[smallest]);
        heapify(smallest);
    }
}

Pair Heap::extractMin()
{
    if (empty())
        return Pair(-1, -1);
    return array[0];
}

bool Heap::empty()
{
    return size == 0;
}

void Heap::pop()
{
    if (empty())
        return;
    array[0] = array[size - 1];
    array.pop_back();
    size--;
    if (!empty())
        heapify(0);
}

int Heap::insert(Pair key)
{
    array.push_back(key);
    size++;
    int i = size - 1;

    while (i != 0 && lessPair(array[i], array[(i - 1) / 2]))
    {
        swap(array[i], array[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
    return i;
}

int n, m, k;
vector<int> dests;
vector<vector<Pair>> adj;

void solve()
{
    vector<int> dist(n + 1, INT_MAX);
    Heap minHeap;

    minHeap.insert(Pair(1, 0));
    dist[1] = 0;
    while (!minHeap.empty())
    {
        Pair p = minHeap.extractMin();
        minHeap.pop();
        if (p.cost != dist[p.to])
        {
            continue;
        }
        for (Pair nb : adj[p.to])
        {
            int to = nb.to;
            ll cost = nb.cost;
            if (dist[to] > dist[p.to] + cost)
            {
                dist[to] = dist[p.to] + cost;
                minHeap.insert(Pair(to, dist[to]));
            }
        }
    }
    ll result = 0;
    for (int i : dests)
    {
        if (dist[i] != INT_MAX)
        {
            result += 2 * dist[i];
        }
        else
        {
            cout << "NIE";
            return;
        }
    }
    cout << result;
    return;
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m >> k;
    adj.resize(n + 1);

    for (int i = 0; i < m; i++)
    {
        int a, b;
        ll d;
        cin >> a >> b >> d;
        adj[a].push_back(Pair(b, d));
        adj[b].push_back(Pair(a, d));
    }
    for (int i = 0; i < k; i++)
    {
        int d;
        cin >> d;
        dests.push_back(d);
    }
    solve();
}