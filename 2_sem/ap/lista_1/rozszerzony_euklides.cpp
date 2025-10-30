#include <bits/stdc++.h>
using namespace std;
int exgcd(int a, int b, int &k, int &l)
{
    if (b == 0)
    {
        k = 1;
        l = 0;
        return a;
    }
    int k1, l1;
    int d = exgcd(b, a % b, k1, l1);
    k = l1;
    l = k1 - l1 * (a / b);
    return d;
}
int main()
{
    int n, k, l;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int a, b, d;
        cin >> a >> b;
        d = exgcd(a, b, k, l);
        cout << k << " " << l << " " << d << '\n';
    }
}