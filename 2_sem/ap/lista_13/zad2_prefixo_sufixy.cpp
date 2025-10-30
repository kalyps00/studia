#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
#define MOD 694202137
int main()
{
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(0);
    string t;
    cin >> t;
    vector<int> prefixo_sufixy(t.length());
    prefixo_sufixy[0] = 0;
    for (int i = 1; i < t.length(); i++)
    {
        int j = prefixo_sufixy[i - 1];
        while (j > 0 && t[i] != t[j])
            j = prefixo_sufixy[j - 1];
        if (t[i] == t[j])
            j++;
        prefixo_sufixy[i] = j;
    }

    vector<int> result;
    int k = prefixo_sufixy[t.length() - 1];
    while (k > 0)
    {
        result.push_back(k);
        k = prefixo_sufixy[k - 1];
    }
    sort(result.begin(), result.end());

    for (int x : result)
        cout << x << " ";
}