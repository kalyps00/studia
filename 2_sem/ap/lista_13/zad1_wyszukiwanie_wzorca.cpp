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
    string t, p, sklejka;
    cin >> t >> p;
    sklejka = p + "#" + t;
    vector<int> prefixo_sufixy(sklejka.length());
    prefixo_sufixy[0] = 0;
    int n = p.length();
    int ans = 0;
    for (int i = 1; i < sklejka.length(); i++)
    {
        int j = prefixo_sufixy[i - 1];            // znaczaca litera
        while (j > 0 && sklejka[i] != sklejka[j]) // cofamy sie na poprzedni znaczaca literea
            j = prefixo_sufixy[j - 1];
        if (sklejka[i] == sklejka[j])
            j++;
        prefixo_sufixy[i] = j;
        if (prefixo_sufixy[i] == n)
            ans++;
    }
    cout << ans;
}