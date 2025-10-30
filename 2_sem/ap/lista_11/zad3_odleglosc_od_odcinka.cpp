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
    int q;
    cin >> q;
    while (q--)
    {
        Point p1, p2, q;
        cin >> p1.x >> p1.y >> p2.x >> p2.y >> q.x >> q.y;
        long double Ax = p2.x - p1.x;
        long double Ay = p2.y - p1.y;
        long double Bx = q.x - p1.x;
        long double By = q.y - p1.y;
        long double det = fabsl(Ax * By - Ay * Bx);
        cout << fixed << setprecision(9) << det / sqrt(Ax * Ax + Ay * Ay) << '\n';
    }
}