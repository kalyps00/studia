#include <iostream>
using namespace std;

int main()
{
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    int t;
    cin >> t;
    int n;
    for (int tests = 0; tests < t; tests++)
    {
        cin >> n;
        int res = 0;
        int pairs = 0;
        for (int i = 0; i < n; i++)
        {
            int a;
            cin >> a;
            if (a == -1)
                pairs++;
            else if (a == 0)
                res += 1;
        }
        res += (pairs % 2) * 2;
        cout << res << '\n';
    }
    return 0;
}