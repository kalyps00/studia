#include <bits/stdc++.h>
using namespace std;
void solve()
{
    int n, s;
    cin >> n >> s;
    int med_pos = ceil(n / 2.0);
    cout << s / (n - med_pos + 1) << "\n";
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