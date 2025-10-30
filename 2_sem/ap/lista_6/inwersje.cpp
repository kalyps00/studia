#include <bits/stdc++.h>
using namespace std;

void update(vector<int> &tree, int s, int x)
{
    int i = s + x;
    while (i > 0)
    {
        tree[i]++;
        i /= 2;
    }
}

long long policz(vector<int> &tree, int nr, int zpocz, int zkon, int ppocz, int pkon)
{
    // Jeśli przedziały są identyczne, zwracamy wynik
    if (zpocz == ppocz && zkon == pkon)
        return tree[nr];

    int s = (zpocz + zkon) / 2;

    // Jeśli przedział p należy całkowicie do lewej części
    if (pkon <= s)
        return policz(tree, 2 * nr, zpocz, s, ppocz, pkon);

    // Jeśli przedział p należy całkowicie do prawej części
    else if (ppocz > s)
        return policz(tree, 2 * nr + 1, s + 1, zkon, ppocz, pkon);

    // Jeśli przedział p przecina obie części
    else
    {
        long long lewo = policz(tree, 2 * nr, zpocz, s, ppocz, s);
        long long prawo = policz(tree, 2 * nr + 1, s + 1, zkon, s + 1, pkon);
        return lewo + prawo;
    }
}

long long calc_inversions(vector<int> &tree, int s, int x)
{
    if (x == s - 1)
        return 0;

    return policz(tree, 1, 0, s - 1, x + 1, s - 1);
}

int main()
{
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(0);
    int n;
    cin >> n;
    vector<int> a(n);
    int max_val = 0;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
        max_val = max(max_val, a[i]);
    }

    int start = 1;
    while (start <= max_val)
        start *= 2;

    vector<int> tree(2 * start, 0);
    long long inversions = 0;

    for (int i = 0; i < n; i++)
    {
        inversions += calc_inversions(tree, start, a[i]);
        update(tree, start, a[i]);
    }

    cout << inversions << '\n';
    return 0;
}