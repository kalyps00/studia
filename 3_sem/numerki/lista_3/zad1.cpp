#include <bits/stdc++.h>
using namespace std;
double a(double x)
{
    return pow(x, 3) + sqrt(pow(x, 6) + 2025.0);
}
double my_a_for_less_than_zero(double x)
{
    return (2025.0) / (sqrt(pow(x, 6) + 2025.0) - pow(x, 3));
}
double b(double x)
{
    return (atan(x) - x) / (x * x * x);
}
double my_b(double x)
{
    double fx = fabs(x);
    if (fx < 1e-3)
    {
        double x2 = x * x;
        double x4 = x2 * x2;
        double x6 = x4 * x2;
        return (-1.0 / 3.0) + (x2 / 5) - (x4 / 7) + (x6 / 9);
    }
    else
    {
        return b(x);
    }
}
int main()
{
    cout << fixed << setprecision(20);
    double x = -10e4;
    if (x < 0)
    {
        cout << "x: " << x << " my_a(x): " << my_a_for_less_than_zero(x) << "  unstable a(x):  " << a(x) << endl;
    }
    else
    {
        cout << "x: " << x << " a(x): " << a(x) << endl;
    }
    x = 10e-8;
    cout << "x: " << x << " my_b(x): " << my_b(x) << "  unstable b(x):  " << b(x) << endl;
}