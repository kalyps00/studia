#include <bits/stdc++.h>
using namespace std;
int find(int x, vector<int> &rep)
{
    if (rep[x] != x)
        rep[x] = find(rep[x], rep);
    return rep[x];
}
void unionn(int a, int b, vector<int> &rep, vector<int> &spojne_rozmiar, int &ile_spojnych, int &max_size)
{
    int rep_a = find(a, rep);
    int rep_b = find(b, rep);
    if (rep_a != rep_b)
    {
        if (spojne_rozmiar[rep_a] < spojne_rozmiar[rep_b])
            swap(rep_a, rep_b);
        rep[rep_b] = rep_a;
        spojne_rozmiar[rep_a] += spojne_rozmiar[rep_b];
        max_size = max(max_size, spojne_rozmiar[rep_a]);
        ile_spojnych--;
    }
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
    int ile_spojnych = n, max_size = 1;
    for (int i = 0; i < n; i++)
    {
        rep[i] = i;
    }
    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        unionn(a, b, rep, spojne_rozmiar, ile_spojnych, max_size);
        cout << ile_spojnych << ' ' << max_size << '\n';
    }
}