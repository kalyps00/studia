#include <iostream>
using namespace std;
typedef long long ll;
#define MOD 1000000000
long long fpow(ll a, ll b)
{
    if (b == 0)
        return 1;
    ll res = 1;
    while (b)
    {
        if (b % 2 == 1)
            res = res * a % MOD;
        a = a * a % MOD;
        b /= 2;
    }
    return res;
}
int main()
{
    ll a, b;
    cin >> a >> b;
    cout << fpow(a, b);
}