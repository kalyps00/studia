#include <bits/stdc++.h>
using namespace std;

struct Edge
{
    int id;
    int weight;
};

struct HeapNode
{
    int id;
    int dist;
};
class Heap
{
public:
    Heap() : arr(1) {}

    bool empty()
    {
        return size == 0;
    }
    void push(HeapNode n)
    {
        if (size + 1 >= (int)arr.size())
            arr.push_back(n);
        else
            arr[size + 1] = n;
        ++size;
        push_up(size);
    }
    HeapNode top()
    {
        HeapNode res = arr[1];
        size--;
        if (size > 0)
            push_down(1);
        return res;
    }

private:
    int size = 0;
    vector<HeapNode> arr;
    void push_up(int n)
    {
        HeapNode temp = arr[n];
        while (n > 1)
        {
            int parent = n / 2;
            if (arr[parent].dist <= temp.dist)
                break;
            arr[n] = arr[parent];
            n = parent;
        }
        arr[n] = temp;
    }
    void push_down(int n)
    {
        HeapNode temp = arr[size + 1];
        int last_index = size / 2;
        while (n <= last_index)
        {
            int next = n * 2;
            int right = n * 2 + 1;
            if (right <= size && arr[right].dist < arr[next].dist)
            {
                next = right;
            }
            if (temp.dist <= arr[next].dist)
                break;
            arr[n] = arr[next];
            n = next;
        }
        arr[n] = temp;
    }
};
int main()
{
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(0);
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<Edge>> graph(n + 1);
    // graph
    for (int i = 0; i < m; i++)
    { // TODO: get edges first then build graph to save memory by not letting vector resize itself multiple times
        int a, b, dist;
        cin >> a >> b >> dist;
        graph[a].push_back({b, dist});
        graph[b].push_back({a, dist});
    }
    graph.shrink_to_fit();
    vector<bool> destination(n + 1, false);
    // destinations
    for (int i = 0; i < k; i++)
    {
        int dest;
        cin >> dest;
        destination[dest] = true;
    }
    // solution
    vector<int> dist(n + 1, INT_MAX);
    dist[1] = 0;
    Heap heap;
    heap.push({1, 0});
    long long result = 0;
    int visited_destinations = 0;
    while (!heap.empty())
    {
        auto [current_id, distance_to_current] = heap.top();
        if (distance_to_current > dist[current_id])
            continue;
        if (destination[current_id])
        {
            result += 2LL * distance_to_current;
            destination[current_id] = false;
            visited_destinations++;
        }
        for (const Edge &neighbour : graph[current_id])
        {
            int new_dist = distance_to_current + neighbour.weight;
            if (new_dist < dist[neighbour.id])
            {
                dist[neighbour.id] = new_dist;
                heap.push({neighbour.id, dist[neighbour.id]});
            }
        }
    }
    if (visited_destinations == k)
        cout << result;
    else
        cout << "NIE";
}