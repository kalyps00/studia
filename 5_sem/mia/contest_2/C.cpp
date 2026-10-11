#include <bits/stdc++.h>
using namespace std;
void solve()
{
    int n;
    cin >> n;
    unordered_map<int, int> mp;
    for (int i = 0; i < n; i++)
    {
        int a;
        cin >> a;
        mp[a]++;
    }
    vector<int> v;
    for (auto it : mp)
    {
        v.push_back(it.second);
    }
    sort(v.begin(), v.end());
    int max_result = 0;
    int removed = 0;
    for (int i = 0; i < v.size(); i++)
    {
        int current = v[i];
        int remaining = v.size() - i;
        max_result = max(max_result, current * remaining);
    }
    cout << n - max_result << '\n';
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