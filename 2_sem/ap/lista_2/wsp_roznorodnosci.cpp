#include <bits/stdc++.h>
using namespace std;

int find(int x, vector<int> &rep)
{
    if (rep[x] != x)
        rep[x] = find(rep[x], rep);
    return rep[x];
}

void unionn(int a, int b, vector<int> &rep, vector<int> &spojne_rozmiar, vector<tuple<int, int, int>> &min_max_edge)
{
    int rep_a = find(a, rep);
    int rep_b = find(b, rep);
    if (rep_a != rep_b)
    {
        if (spojne_rozmiar[rep_a] < spojne_rozmiar[rep_b])
            swap(rep_a, rep_b);
        rep[rep_b] = rep_a;
        spojne_rozmiar[rep_a] += spojne_rozmiar[rep_b];
        min_max_edge[rep_a] = make_tuple(min(get<0>(min_max_edge[rep_a]), get<0>(min_max_edge[rep_b])),
                                         max(get<1>(min_max_edge[rep_a]), get<1>(min_max_edge[rep_b])),
                                         (get<2>(min_max_edge[rep_a]) + get<2>(min_max_edge[rep_b]) + 1));
    }
    else
    {
        get<2>(min_max_edge[rep_a])++;
    }
}

long long wsp(const tuple<int, int, int> &t)
{
    return (long long)(get<1>(t) - get<0>(t)) * get<2>(t);
}

int main()
{
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    vector<int> rep(n);
    vector<int> spojne_rozmiar(n, 1);
    vector<tuple<int, int, int>> min_max_edge(n);

    for (int i = 0; i < n; i++)
    {
        rep[i] = i;
        min_max_edge[i] = make_tuple(i, i, 0);
    }

    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        unionn(a, b, rep, spojne_rozmiar, min_max_edge);
        cout << wsp(min_max_edge[find(a, rep)]) << "\n";
    }

    return 0;
}
