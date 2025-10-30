#include <bits/stdc++.h>
using namespace std;

int find(int x, vector<int> &rep, vector<int> &czy_parzysty)
{
    if (rep[x] != x)
    {
        int old_parent = rep[x];
        rep[x] = find(rep[x], rep, czy_parzysty);
        czy_parzysty[x] ^= czy_parzysty[old_parent];
    }
    return rep[x];
}
bool unionn(int a, int b, int p, vector<int> &rep, vector<int> &spojne_rozmiar, vector<int> &czy_parzysty)
{
    int rep_a = find(a, rep, czy_parzysty);
    int rep_b = find(b, rep, czy_parzysty);
    if (rep_a == rep_b)
    {
        if ((czy_parzysty[a] ^ czy_parzysty[b]) != p)
            return false;
        return true;
    }
    if (spojne_rozmiar[rep_a] < spojne_rozmiar[rep_b])
        swap(rep_a, rep_b);
    rep[rep_b] = rep_a;
    spojne_rozmiar[rep_a] += spojne_rozmiar[rep_b];
    czy_parzysty[rep_b] = (czy_parzysty[a] ^ czy_parzysty[b] ^ p);
    return true;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m;
    cin >> n;
    vector<int> czy_parzysty(n, 0);
    cin >> m;
    vector<int> rep(n);
    vector<int> spojne_rozmiar(n, 1);
    for (int i = 0; i < n; i++)
    {
        rep[i] = i;
    }
    for (int i = 0; i < m; i++)
    {
        int a, b, p;
        cin >> a >> b >> p;
        a--;
        b--;
        if (!unionn(a, b, p, rep, spojne_rozmiar, czy_parzysty))
        {
            cout << i;
            return 0;
        }
    }
    cout << m;
    return 0;
}
