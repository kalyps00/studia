#include <bits/stdc++.h>
using namespace std;

int main()
{
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(0);
    long long q;
    int n;
    cin >> q >> n;
    map<pair<long long, long long>, bool> visible_points;

    while (n--)
    {
        long long x, y;
        cin >> x >> y;
        long long dx = x - q, dy = y;
        long long g = gcd(abs(dx), abs(dy));
        dx /= g;
        dy /= g;
        if (dx < 0)
        {
            dx = -dx;
            dy = -dy;
        }
        visible_points[{dx, dy}] = true;
    }
    cout << visible_points.size() << '\n';

    return 0;
}