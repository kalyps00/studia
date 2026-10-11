#include <bits/stdc++.h>
using namespace std;
void solve()
{
    int n;
    cin >> n;
    vector<pair<int, int>> a(n);
    for (int i = 0; i < n; i++)
    {
        cin >> a[i].first;
    }
    for (int i = 0; i < n; i++)
    {
        cin >> a[i].second;
    }
    int result = 0;
    pair<int, int> max1 = {INT_MIN, INT_MIN};
    int max_idx = -1;
    for (int i = 0; i < n; i++)
    {
        if (min(a[i].first, a[i].second) > min(max1.first, max1.second))
        {
            max1 = a[i];
            max_idx = i;
        }
    }
    result += max1.first + max1.second;
    for (int i = 0; i < n; i++)
    {
        if (i == max_idx)
            continue;
        if (a[i].first > a[i].second)
            result += a[i].first;
        else
            result += a[i].second;
    }
    cout << result << '\n';
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}