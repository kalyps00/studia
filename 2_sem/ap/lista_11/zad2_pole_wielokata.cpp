#include <bits/stdc++.h>
using namespace std;
struct Point
{
    long long x, y;
};
int main()
{
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(0);
    int n;
    cin >> n;
    vector<Point> points(n);
    long long area = 0;
    for (int i = 0; i < n; ++i)
    {
        cin >> points[i].x >> points[i].y;
    }
    for (int i = 1; i < n - 1; ++i)
    {
        area += (points[i].x - points[0].x) * (points[i + 1].y - points[0].y) -
                (points[i].y - points[0].y) * (points[i + 1].x - points[0].x);
    }
    long double result = fabsl(area) / 2.0L;
    cout << fixed << setprecision(1) << result << '\n';

    return 0;
}
