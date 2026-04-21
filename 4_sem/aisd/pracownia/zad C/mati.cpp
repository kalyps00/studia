#include <iostream>
#include <vector>

const int max_n = 100001;
long long inf = 1e10;

struct Edge
{
    int neigh;
    int dist;
};
std::vector<Edge> nghbrs[max_n];

long long dist[max_n];
int heap[max_n];
int position[max_n];
int heap_size = 0;

void heap_swap(int k, int j)
{
    int temp = heap[k];
    heap[k] = heap[j];
    heap[j] = temp;
    position[heap[k]] = k;
    position[heap[j]] = j;
}

void push_up(int pos)
{
    int k = pos;
    int j = k + 1;
    while (k != j)
    {
        j = k;
        if (j > 1 && dist[heap[j / 2]] > dist[heap[k]])
        {
            k /= 2;
            heap_swap(k, j);
        }
    }
}

void push_down(int pos)
{
    int k = pos;
    int j = k + 1;
    while (k != j)
    {
        j = k;
        if (2 * j <= heap_size && dist[heap[2 * j]] < dist[heap[k]])
        {
            k = 2 * j;
        }
        if (2 * j + 1 <= heap_size && dist[heap[2 * j + 1]] < dist[heap[k]])
        {
            k = 2 * j + 1;
        }
        if (k != j)
        {
            heap_swap(k, j);
        }
    }
}

void push_heap(int v)
{
    heap_size += 1;
    heap[heap_size] = v;
    position[v] = heap_size;
    push_up(heap_size);
}

int pop_heap()
{
    int v = heap[1];
    position[v] = 0;
    heap[1] = heap[heap_size];
    heap_size -= 1;
    if (heap_size > 0)
    {
        position[heap[1]] = 1;
        push_down(1);
    }
    return v;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, m, k;
    std::cin >> n >> m >> k;

    for (int i = 0; i <= n; i++)
    {
        dist[i] = inf;
        position[i] = 0;
    }

    for (int i = 0; i < m; i++)
    {
        int a, b, d;
        std::cin >> a >> b >> d;
        nghbrs[a].push_back({b, d});
        nghbrs[b].push_back({a, d});
    }
    dist[1] = 0;
    push_heap(1);

    while (heap_size > 0)
    {
        int c = pop_heap();
        for (Edge e : nghbrs[c])
        {
            int nig = e.neigh;
            int d = e.dist;

            if (dist[nig] > dist[c] + d)
            {
                dist[nig] = dist[c] + d;
                if (position[nig] == 0)
                {
                    push_heap(nig);
                }
                else
                {
                    push_up(position[nig]);
                }
            }
        }
    }
    bool doable = true;
    long long cost = 0;
    for (int i = 0; i < k; i++)
    {
        int d;
        std::cin >> d;
        if (dist[d] == inf)
        {
            doable = false;
            break;
        }
        else
        {
            cost += 2 * dist[d];
        }
    }
    if (doable)
    {
        std::cout << cost << "\n";
    }
    else
    {
        std::cout << "NIE\n";
    }
    return 0;
}