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
    int t;
    cin >> t;
    Point p1, p2, p3;
    while (t--)
    {
        cin >> p1.x >> p1.y >> p2.x >> p2.y >> p3.x >> p3.y;
        long long det = (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
        if (det > 0)
            cout << "LEFT\n";
        else if (det < 0)
            cout << "RIGHT\n";
        else
            cout << "TOUCH\n";
    }
}